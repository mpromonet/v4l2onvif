/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** server.cpp
** 
** server
**
** -------------------------------------------------------------------------*/

#include <net/if.h>
#include <ifaddrs.h>

#include <sys/ioctl.h>
#include <linux/videodev2.h>

#include "DeviceBinding.nsmap"
#include "soapDeviceBindingService.h"

#include "soapMediaBindingService.h"
#include "soapRecordingBindingService.h"
#include "soapReceiverBindingService.h"
#include "soapReplayBindingService.h"
#include "soapImagingBindingService.h"
#include "soapSearchBindingService.h"

#include "soapEventBindingService.h"
#include "soapPullPointSubscriptionBindingService.h"

#include "wsseapi.h"

#include "server.h"

int http_get(struct soap *soap)
{
	int retCode = 404;
	FILE *fd = fopen(soap->path + 1, "rb"); 
	if (fd != NULL)
	{
		if (!soap_tag_cmp(soap->path, "*.html"))
			soap->http_content = "text/html"; 
		if (!soap_tag_cmp(soap->path, "*.wsdl"))
			soap->http_content = "text/xml"; 
		soap_response(soap, SOAP_FILE);
		for (;;)
		{
			size_t r = fread(soap->tmpbuf, 1, sizeof(soap->tmpbuf), fd);
			if ( (r == 0) || (soap_send_raw(soap, soap->tmpbuf, r)) )
				break;
		}
		fclose(fd);
		soap_end_send(soap);
		retCode = SOAP_OK;
	}
	return retCode;
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

std::pair<int,int> ServiceContext::getCtrlRange(const std::string &device, int idctrl)
{
	std::pair<int,int> value;
	int fd = open(device.c_str(), O_RDWR | O_NONBLOCK, 0);
	
	struct v4l2_queryctrl queryctrl;
	memset(&queryctrl, 0, sizeof(queryctrl));
	queryctrl.id = idctrl;
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

tt__VideoEncoderConfiguration* ServiceContext::getVideoEncoderCfg(struct soap* soap, const std::string & token)
{
	tt__VideoEncoderConfiguration* cfg = soap_new_tt__VideoEncoderConfiguration(soap);
	int width;
	int height;
	int format;	
	if (getFormat(token, width, height, format))
	{		
		cfg->Resolution = soap_new_req_tt__VideoResolution(soap, width, height);
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
		if (format == V4L2_PIX_FMT_H264)
		{			
			cfg->H264 = soap_new_tt__H264Options(soap);
			
			int fd = open(token.c_str(), O_RDWR | O_NONBLOCK, 0);
			
			struct v4l2_frmsizeenum frmsize;
			memset(&frmsize,0,sizeof(frmsize));
			frmsize.pixel_format = V4L2_PIX_FMT_H264;
			frmsize.index = 0;
			for (frmsize.index = 0 ; (ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &frmsize) == 0) ; frmsize.index++)
			{
				if (frmsize.type == V4L2_FRMSIZE_TYPE_DISCRETE) 
				{				
					cfg->H264->ResolutionsAvailable.push_back(soap_new_req_tt__VideoResolution(soap, frmsize.discrete.width, frmsize.discrete.height));
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
							cfg->H264->ResolutionsAvailable.push_back(soap_new_req_tt__VideoResolution(soap, w, h));
						}
					}
				}
			}
			
			close(fd);
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

int main(int argc, char* argv[])
{		
	std::string device = "/dev/video0";
	std::string path    = "unicast";
	std::string username;
	std::string password;	
	int port = 8080;
	int c = 0;
	while ((c = getopt (argc, argv, "hu:p:d:r:")) != -1)
	{
		switch (c)
		{
			case 'u':	username = optarg; break;
			case 'p':	password = optarg; break;
			case 'd':	device = optarg; break;
			case 'r':	path = optarg; break;
			case 'h':
				std::cout << argv[0] << " [-u username] [-p password] [-d v4l2 device] [-r rtsp uri]" << std::endl;
				exit(0);
			break;
		}
	}
	std::cout << "Listening to " << port << std::endl;
		
	ServiceContext deviceCtx;
	deviceCtx.m_wsdlurl = "devicemgmt.wsdl";
	deviceCtx.m_port = port;
	deviceCtx.m_rtspport = "554";
	deviceCtx.m_user = username;
	deviceCtx.m_password = password;
	deviceCtx.m_devices.insert(std::pair<std::string,std::string>(device, path));
	
	struct soap *soap = soap_new();
	soap->user = (void*)&deviceCtx;
	soap->fget = http_get; 
	{			
		DeviceBindingService deviceService(soap);
		
		MediaBindingService mediaService(soap);
		RecordingBindingService recordingService(soap);
		ReceiverBindingService receiverService(soap);
		ReplayBindingService replayService(soap);
		ImagingBindingService imagingService(soap);
		SearchBindingService searchService(soap);
		
		EventBindingService eventService(soap);
		PullPointSubscriptionBindingService pullPointService(soap);

		
		if (!soap_valid_socket(soap_bind(soap, NULL, deviceCtx.m_port, 100))) 
		{
			soap_stream_fault(soap, std::cerr);
		}
		else
		{
			while (soap_accept(soap) != SOAP_OK) 
			{
				if (soap_begin_serve(soap))
				{
					soap_stream_fault(soap, std::cerr);
				}
				else if (deviceService.dispatch() != SOAP_NO_METHOD)
				{
					soap_send_fault(soap);
					soap_stream_fault(soap, std::cerr);
				}
				else if (recordingService.dispatch() != SOAP_NO_METHOD)
				{
					soap_send_fault(soap);
					soap_stream_fault(soap, std::cerr);
				}
				else if (receiverService.dispatch() != SOAP_NO_METHOD)
				{
					soap_send_fault(soap);
					soap_stream_fault(soap, std::cerr);
				}
				else if (replayService.dispatch() != SOAP_NO_METHOD)
				{
					soap_send_fault(soap);
					soap_stream_fault(soap, std::cerr);
				}
				else if (imagingService.dispatch() != SOAP_NO_METHOD)
				{
					soap_send_fault(soap);
					soap_stream_fault(soap, std::cerr);
				}
				else if (eventService.dispatch() != SOAP_NO_METHOD)
				{
					soap_send_fault(soap);
					soap_stream_fault(soap, std::cerr);
				}
				else if (pullPointService.dispatch() != SOAP_NO_METHOD)
				{
					soap_send_fault(soap);
					soap_stream_fault(soap, std::cerr);
				}
				else if (mediaService.dispatch() != SOAP_NO_METHOD)
				{
					soap_send_fault(soap);
					soap_stream_fault(soap, std::cerr);
				}
				else if (searchService.dispatch() != SOAP_NO_METHOD)
				{
					soap_send_fault(soap);
					soap_stream_fault(soap, std::cerr);
				}
			}
		}
	}
	
	soap_destroy(soap);
	soap_end(soap);
	soap_free(soap); 			
	
	return 0;
}
