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

std::string getServerIpFromClientIp(int clientip)
{
	std::string serverip;
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
						serverip = host;
						break;
					}
				}
			}
		}
	}
	freeifaddrs(ifaddr);
	return serverip;
}
	
int getFormat(const std::string &device, int& width, int& height, int& format)
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

int getCtrlValue(const std::string &device, int idctrl)
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

std::pair<int,int> getCtrlRange(const std::string &device, int idctrl)
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

tt__VideoEncoderConfiguration* getVideoEncoderCfg(struct soap* soap, const std::string & device)
{
	tt__VideoEncoderConfiguration* cfg = soap_new_tt__VideoEncoderConfiguration(soap);
	int width;
	int height;
	int format;	
	if (getFormat(device, width, height, format))
	{		
		if (format == V4L2_PIX_FMT_H264)
		{			
			cfg->Encoding = tt__VideoEncoding__H264;
			cfg->Resolution = soap_new_req_tt__VideoResolution(soap, width, height);
			cfg->H264 = soap_new_tt__H264Configuration(soap);
			cfg->H264->H264Profile = getH264Profile(getCtrlValue (device, V4L2_CID_MPEG_VIDEO_H264_PROFILE));
			cfg->Multicast = soap_new_tt__MulticastConfiguration(soap);
			cfg->Multicast->Address = soap_new_tt__IPAddress(soap);
			cfg->SessionTimeout = "PT10S";
		}
	}
	return cfg;
}

tt__VideoEncoderConfigurationOptions* getVideoEncoderCfgOptions(struct soap* soap, const std::string & device)
{
	tt__VideoEncoderConfigurationOptions* cfg = soap_new_tt__VideoEncoderConfigurationOptions(soap);
	int width;
	int height;
	int format;	
	if (getFormat(device, width, height, format))
	{		
		cfg->QualityRange = soap_new_req_tt__IntRange(soap, 0, 100);
		if (format == V4L2_PIX_FMT_H264)
		{			
			cfg->H264 = soap_new_tt__H264Options(soap);
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
					for (int w = frmsize.stepwise.min_width; w < frmsize.stepwise.max_width ; w+=frmsize.stepwise.step_width)
					{
						for (int h = frmsize.stepwise.min_height; w < frmsize.stepwise.max_heigth ; w+=frmsize.stepwise.step_height)
						{
							cfg->H264->ResolutionsAvailable.push_back(soap_new_req_tt__VideoResolution(soap, w, h));
						}
					}
				}
			}
		}
	}
	return cfg;
}

tt__VideoSourceConfiguration* getVideoSourceCfg(struct soap* soap, const std::string &token)
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

tt__RecordingJobConfiguration* getRecordingJobConfiguration(struct soap* soap, const std::string & recordtoken, const std::string & sourcetoken)
{
	tt__RecordingJobConfiguration* cfg = soap_new_tt__RecordingJobConfiguration(soap);
	cfg->RecordingToken = recordtoken;	
	cfg->Source.push_back(soap_new_tt__RecordingJobSource(soap));
	cfg->Source.back()->SourceToken = soap_new_tt__SourceReference(soap);
	cfg->Source.back()->SourceToken->Token = sourcetoken;
	return cfg;
}

tt__RecordingConfiguration* getRecordingCfg(struct soap* soap)
{
	tt__RecordingConfiguration* cfg = soap_new_tt__RecordingConfiguration(soap);
	cfg->Source = soap_new_tt__RecordingSourceInformation(soap);
	cfg->Source->SourceId = "sourceid";
	cfg->Source->Location = "here";
	cfg->MaximumRetentionTime = "PT24H";
	return cfg;
}

tt__TrackConfiguration* getTracksCfg(struct soap* soap)
{
	tt__TrackConfiguration* cfg = soap_new_tt__TrackConfiguration(soap);
	cfg->TrackType = tt__TrackType__Video;
	cfg->Description = "trackdescription";
	return cfg;
}

tds__DeviceServiceCapabilities* getDeviceServiceCapabilities(struct soap* soap)
{
	tds__DeviceServiceCapabilities *capabilities = soap_new_tds__DeviceServiceCapabilities(soap);
	capabilities->Network = soap_new_tds__NetworkCapabilities(soap);
	capabilities->Security = soap_new_tds__SecurityCapabilities(soap);
	capabilities->System = soap_new_tds__SystemCapabilities(soap);
	return capabilities;
}

trt__Capabilities* getMediaServiceCapabilities(struct soap* soap)
{
	trt__Capabilities *capabilities = soap_new_trt__Capabilities(soap);
	capabilities->ProfileCapabilities = soap_new_trt__ProfileCapabilities(soap);
	capabilities->ProfileCapabilities->MaximumNumberOfProfiles =  soap_new_ptr(soap, 10);
	capabilities->StreamingCapabilities = soap_new_trt__StreamingCapabilities(soap);
	capabilities->StreamingCapabilities->RTPMulticast =  soap_new_ptr(soap, false);
	return capabilities;
}

timg__Capabilities* getImagingServiceCapabilities(struct soap* soap)
{
	timg__Capabilities *capabilities = soap_new_timg__Capabilities(soap);
	return capabilities;
}

trc__Capabilities* getRecordingServiceCapabilities(struct soap* soap)
{
	trc__Capabilities *capabilities = soap_new_trc__Capabilities(soap);
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
