/* --------------------------------------------------------------------------
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
 onvif_impl.cpp
 
 V4L2 implementation of ONVIF services
----------------------------------------------------------------------------- */

#include <net/if.h>
#include <ifaddrs.h>

#include <sys/ioctl.h>
#include <linux/videodev2.h>

#include "onvif_impl.h"

std::string ServiceContext::getLocalIp()
{
	std::string serverAddress;
	char hostname[HOST_NAME_MAX];
	if (gethostname(hostname, sizeof(hostname)) == 0)
	{
		struct addrinfo hints;
		struct addrinfo *result;
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_INET;
		if (getaddrinfo(hostname, NULL, &hints, &result) == 0)
		{
			if (result != NULL) 
			{
				struct sockaddr_in* addr = (struct sockaddr_in *) result->ai_addr;
				serverAddress.assign(inet_ntoa( addr->sin_addr ));
				freeaddrinfo(result); 
			}
		}
	}
	return serverAddress;
} 

std::string ServiceContext::getServerIpFromClientIp(int clientip)
{
	std::string serverAddress;
	char host[NI_MAXHOST];
	struct ifaddrs *ifaddr = NULL;
	if (getifaddrs(&ifaddr) == 0) 
	{
		for (struct ifaddrs* ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) 
		{
			if ( (ifa->ifa_netmask != NULL) && (ifa->ifa_netmask->sa_family == AF_INET) && (ifa->ifa_addr != NULL) && (ifa->ifa_addr->sa_family == AF_INET) )  
			{
				struct sockaddr_in* addr = (struct sockaddr_in*)ifa->ifa_addr;
				struct sockaddr_in* mask = (struct sockaddr_in*)ifa->ifa_netmask;
				if ( (addr->sin_addr.s_addr & mask->sin_addr.s_addr) == (clientip & mask->sin_addr.s_addr) )
				{
					if (getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, sizeof(host), NULL, 0, NI_NUMERICHOST) == 0)
					{
						serverAddress = host;
						break;
					}
				}
			}
		}
	}
	freeifaddrs(ifaddr);
	if (serverAddress.empty())
	{
		serverAddress = getLocalIp();
	}
	return serverAddress;
}
	
int ServiceContext::getFormat(const std::string &device, int& width, int& height, int& format)
{
	int ret = 0;
	int fd = open(device.c_str(), O_RDWR | O_NONBLOCK, 0);
	
	struct v4l2_format     fmt;
	memset(&fmt,0,sizeof(fmt));
	fmt.type  = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (0 == ioctl(fd,VIDIOC_G_FMT,&fmt))
	{
		width  = fmt.fmt.pix.width;
		height = fmt.fmt.pix.height;
		format = fmt.fmt.pix.pixelformat;
		ret = 1;
	}
	close(fd);	
	return ret;
}

int ServiceContext::getCtrlValue(const std::string &device, int idctrl)
{
	int value = 0;
	int fd = open(device.c_str(), O_RDWR | O_NONBLOCK, 0);
	
	struct v4l2_control control;
	memset(&control, 0, sizeof(control));
	control.id = idctrl;
	errno = 0;
	if (ioctl (fd, VIDIOC_G_CTRL, &control) == 0) 
	{
		value = control.value;
	} 	
	
	close(fd);	
	return value;
}

void ServiceContext::setCtrlValue(const std::string &device, int idctrl, int value)
{
	int fd = open(device.c_str(), O_RDWR | O_NONBLOCK, 0);
	
	struct v4l2_control control;
	memset(&control, 0, sizeof(control));
	control.id = idctrl;
	control.value = value;
	errno = 0;
	if (ioctl (fd, VIDIOC_S_CTRL, &control) == 0) 
	{
	} 	
	
	close(fd);	
}

void ServiceContext::getIdentification(const std::string &device, std::string & card, std::string & driver, std::string & bus)
{
	int fd = open(device.c_str(), O_RDWR | O_NONBLOCK, 0);
	v4l2_capability cap;
	memset(&cap,0,sizeof(cap));
	if (-1 != ioctl(fd,VIDIOC_QUERYCAP,&cap))
	{
		card   = (const char*)cap.card;
		driver = (const char*)cap.driver;
		bus    = (const char*)cap.bus_info;
	}
	close(fd);	
}

std::list<std::string> ServiceContext::getScopes() {
	std::list<std::string> scopes;
	char hostname[HOST_NAME_MAX];
	gethostname(hostname, sizeof(hostname));
	scopes.push_back("onvif://www.onvif.org/name/" + std::string(hostname));
	scopes.push_back("onvif://www.onvif.org/location/Here");
	scopes.push_back("onvif://www.onvif.org/Profile/Streaming");
	scopes.push_back("onvif://www.onvif.org/Profile/G");	
	return scopes;
}

std::pair<int,int> ServiceContext::getCtrlRange(const std::string &device, int idctrl)
{
	std::pair<int,int> value;
	int fd = open(device.c_str(), O_RDWR | O_NONBLOCK, 0);
	
	struct v4l2_queryctrl queryctrl;
	memset(&queryctrl, 0, sizeof(queryctrl));
	queryctrl.id = idctrl;
	errno = 0;
	if (ioctl (fd, VIDIOC_QUERYCTRL, &queryctrl) == 0) 
	{
		value.first = queryctrl.minimum;
		value.second = queryctrl.maximum;
   	} 	
	
	close(fd);	
	return value;
}

tt__H264Profile getH264Profile(int h264profile)
{
	tt__H264Profile profile = tt__H264Profile__Baseline;
	switch (h264profile)
	{
		case V4L2_MPEG_VIDEO_H264_PROFILE_MAIN: profile = tt__H264Profile__Main; break;
		case V4L2_MPEG_VIDEO_H264_PROFILE_EXTENDED: profile = tt__H264Profile__Extended; break;
		case V4L2_MPEG_VIDEO_H264_PROFILE_HIGH: profile = tt__H264Profile__High; break;
	}
	return profile;
}

tt__Profile* ServiceContext::getProfile(struct soap* soap, const std::string & token)
{
	tt__Profile* profile = soap_new_tt__Profile(soap);
	profile->Name = token;
	profile->token = token;
	profile->VideoSourceConfiguration = getVideoSourceCfg(soap, token);
	profile->VideoEncoderConfiguration = getVideoEncoderCfg(soap, token);
	return profile;
}

tt__VideoEncoderConfiguration* ServiceContext::getVideoEncoderCfg(struct soap* soap, const std::string & token)
{
	tt__VideoEncoderConfiguration* cfg = soap_new_tt__VideoEncoderConfiguration(soap);
	cfg->Name = token;
	cfg->token = token;
	int width;
	int height;
	int format;	
	if (getFormat(token, width, height, format))
	{		
		cfg->Resolution = soap_new_req_tt__VideoResolution(soap, width, height);
		cfg->RateControl = soap_new_req_tt__VideoRateControl(soap, 0, 0, 0);
		cfg->Multicast = soap_new_tt__MulticastConfiguration(soap);
		cfg->Multicast->Address = soap_new_tt__IPAddress(soap);
		cfg->SessionTimeout = "PT10S";
		if (format == V4L2_PIX_FMT_H264)
		{			
			cfg->Encoding = tt__VideoEncoding__H264;
			cfg->H264 = soap_new_tt__H264Configuration(soap);
			cfg->H264->H264Profile = getH264Profile(getCtrlValue (token, V4L2_CID_MPEG_VIDEO_H264_PROFILE));
		}
		else if (format == V4L2_PIX_FMT_JPEG)
		{
			cfg->Encoding = tt__VideoEncoding__JPEG;
		}
	}
	return cfg;
}

tt__VideoEncoderConfigurationOptions* ServiceContext::getVideoEncoderCfgOptions(struct soap* soap, const std::string & token)
{
	tt__VideoEncoderConfigurationOptions* cfg = soap_new_tt__VideoEncoderConfigurationOptions(soap);
	int width;
	int height;
	int format;	
	if (getFormat(token, width, height, format))
	{		
		cfg->QualityRange = soap_new_req_tt__IntRange(soap, 0, 100);
		std::vector<tt__VideoResolution*   > resolutions;
		int fd = open(token.c_str(), O_RDWR | O_NONBLOCK, 0);
		
		struct v4l2_frmsizeenum frmsize;
		memset(&frmsize,0,sizeof(frmsize));
		frmsize.pixel_format = format;
		frmsize.index = 0;
		for (frmsize.index = 0 ; (ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &frmsize) == 0) ; frmsize.index++)
		{
			if (frmsize.type == V4L2_FRMSIZE_TYPE_DISCRETE) 
			{				
				resolutions.push_back(soap_new_req_tt__VideoResolution(soap, frmsize.discrete.width, frmsize.discrete.height));
			}
			else
			{
				int nb = (frmsize.stepwise.max_width-frmsize.stepwise.min_width)/frmsize.stepwise.step_width;
				if (nb>4)
				{
					frmsize.stepwise.step_width *= (nb/4);
				}
				nb = (frmsize.stepwise.max_height-frmsize.stepwise.min_height)/frmsize.stepwise.step_height;
				if (nb>4)
				{
					frmsize.stepwise.step_height *= (nb/4);
				}
			
				for (int w = frmsize.stepwise.min_width; w <= frmsize.stepwise.max_width ; w+=frmsize.stepwise.step_width)
				{
					for (int h = frmsize.stepwise.min_height; h <= frmsize.stepwise.max_height ; h+=frmsize.stepwise.step_height)
					{
						resolutions.push_back(soap_new_req_tt__VideoResolution(soap, w, h));
					}
				}
			}
		}		
		close(fd);
		
		if (format == V4L2_PIX_FMT_H264)
		{			
			cfg->H264 = soap_new_tt__H264Options(soap);
			cfg->H264->ResolutionsAvailable = resolutions;		
		}
		else if (format == V4L2_PIX_FMT_JPEG)
		{
			cfg->JPEG = soap_new_tt__JpegOptions(soap);
			cfg->JPEG->ResolutionsAvailable = resolutions;		
		}		
	}
	return cfg;
}

tt__VideoSourceConfiguration* ServiceContext::getVideoSourceCfg(struct soap* soap, const std::string &token)
{
	tt__VideoSourceConfiguration* sourcecfg = soap_new_tt__VideoSourceConfiguration(soap);
	sourcecfg->token = token;
	sourcecfg->SourceToken = token;	
	int width = 0;
	int height = 0;
	int format = 0;	
	getFormat(token, width, height, format);
	sourcecfg->Bounds = soap_new_req_tt__IntRectangle(soap, 0, 0, width, height);
	return sourcecfg;
}

tt__VideoSourceConfigurationOptions* ServiceContext::getVideoSourceCfgOptions(struct soap* soap, const std::string & token)
{
	tt__VideoSourceConfigurationOptions* cfg = soap_new_tt__VideoSourceConfigurationOptions(soap);
	int width = 0;
	int height = 0;
	int format = 0;	
	getFormat(token, width, height, format);
	cfg->BoundsRange = soap_new_tt__IntRectangleRange(soap);
	cfg->BoundsRange->XRange = soap_new_req_tt__IntRange(soap, 0, width);
	cfg->BoundsRange->YRange = soap_new_req_tt__IntRange(soap, 0, height);
	cfg->BoundsRange->WidthRange = soap_new_req_tt__IntRange(soap, 0, width);
	cfg->BoundsRange->HeightRange = soap_new_req_tt__IntRange(soap, 0, height);
	cfg->VideoSourceTokensAvailable.push_back(token);
	return cfg;
}

tt__RecordingJobConfiguration* ServiceContext::getRecordingJobConfiguration(struct soap* soap, const std::string & token)
{
	tt__RecordingJobConfiguration* cfg = soap_new_tt__RecordingJobConfiguration(soap);
	cfg->RecordingToken = token;	
	cfg->Source.push_back(soap_new_tt__RecordingJobSource(soap));
	cfg->Source.back()->SourceToken = soap_new_tt__SourceReference(soap);
	cfg->Source.back()->SourceToken->Token = token;
	cfg->Source.back()->SourceToken->Type = "http://www.onvif.org/ver10/schema/Profile";
	return cfg;
}

tt__RecordingConfiguration* ServiceContext::getRecordingCfg(struct soap* soap)
{
	tt__RecordingConfiguration* cfg = soap_new_tt__RecordingConfiguration(soap);
	cfg->Source = soap_new_tt__RecordingSourceInformation(soap);
	cfg->Source->SourceId = "sourceid";
	cfg->Source->Location = "here";
	cfg->MaximumRetentionTime = "PT24H";
	return cfg;
}

tt__TrackConfiguration* ServiceContext::getTracksCfg(struct soap* soap)
{
	tt__TrackConfiguration* cfg = soap_new_tt__TrackConfiguration(soap);
	cfg->TrackType = tt__TrackType__Video;
	cfg->Description = "trackdescription";
	return cfg;
}

tds__StorageConfiguration* ServiceContext::getStorageCfg(struct soap* soap, const std::string & path)
{
	tds__StorageConfiguration* cfg = soap_new_tds__StorageConfiguration(soap);
	cfg->token = path;
	cfg->Data = soap_new_tds__StorageConfigurationData(soap);
	cfg->Data->LocalPath = soap_new_std__string(soap);
	cfg->Data->LocalPath->assign(path);
	return cfg;
}


tds__DeviceServiceCapabilities* ServiceContext::getDeviceServiceCapabilities(struct soap* soap)
{
	tds__DeviceServiceCapabilities *capabilities = soap_new_tds__DeviceServiceCapabilities(soap);
	capabilities->Network = soap_new_tds__NetworkCapabilities(soap);
	capabilities->Security = soap_new_tds__SecurityCapabilities(soap);
	capabilities->System = soap_new_tds__SystemCapabilities(soap);
	capabilities->System->StorageConfiguration = soap_new_ptr(soap, true);
	return capabilities;
}

trt__Capabilities* ServiceContext::getMediaServiceCapabilities(struct soap* soap)
{
	trt__Capabilities *capabilities = soap_new_trt__Capabilities(soap);
	capabilities->ProfileCapabilities = soap_new_trt__ProfileCapabilities(soap);
	capabilities->ProfileCapabilities->MaximumNumberOfProfiles =  soap_new_ptr(soap, 10);
	capabilities->StreamingCapabilities = soap_new_trt__StreamingCapabilities(soap);
	capabilities->StreamingCapabilities->RTPMulticast = soap_new_ptr(soap, false);
	return capabilities;
}

timg__Capabilities* ServiceContext::getImagingServiceCapabilities(struct soap* soap)
{
	timg__Capabilities *capabilities = soap_new_timg__Capabilities(soap);
	return capabilities;
}

trc__Capabilities* ServiceContext::getRecordingServiceCapabilities(struct soap* soap)
{
	trc__Capabilities *capabilities = soap_new_trc__Capabilities(soap);
	return capabilities;
}

tse__Capabilities*  ServiceContext::getSearchServiceCapabilities(struct soap* soap)
{
	tse__Capabilities *capabilities = soap_new_tse__Capabilities(soap);
	return capabilities;
}

trv__Capabilities*  ServiceContext::getReceiverServiceCapabilities(struct soap* soap)
{
	trv__Capabilities *capabilities = soap_new_trv__Capabilities(soap);
	return capabilities;
}

trp__Capabilities* ServiceContext::getReplayServiceCapabilities(struct soap* soap)
{
	trp__Capabilities *capabilities = soap_new_trp__Capabilities(soap);
	return capabilities;
}

tev__Capabilities* ServiceContext::getEventServiceCapabilities(struct soap* soap)
{
	tev__Capabilities *capabilities = soap_new_tev__Capabilities(soap);
	return capabilities;
}

tls__Capabilities* ServiceContext::getDisplayServiceCapabilities(struct soap* soap)
{
	tls__Capabilities *capabilities = soap_new_tls__Capabilities(soap);
	return capabilities;
}

tmd__Capabilities* ServiceContext::getDeviceIOServiceCapabilities(struct soap* soap)
{
	tmd__Capabilities *capabilities = soap_new_tmd__Capabilities(soap);
	return capabilities;
}

