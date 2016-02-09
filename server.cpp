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
#include <libv4l2.h>

#include "DeviceBinding.nsmap"
#include "soapDeviceBindingService.h"
#include "soapMediaBindingService.h"
#include "soapRecordingBindingService.h"
#include "soapReceiverBindingService.h"
#include "soapReplayBindingService.h"
#include "soapImagingBindingService.h"
#include "soapEventBindingService.h"
#include "soapPullPointSubscriptionBindingService.h"

#include "wsseapi.h"

#include "serviceContext.h"

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
	
int getFormat(const char* device, int& width, int& height, int& format)
{
	int ret = 0;
	int fd = v4l2_open(device, O_RDWR | O_NONBLOCK, 0);
	
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
	v4l2_close(fd);	
	return ret;
}
	
tt__VideoEncoderConfiguration* getVideoEncoderCfg(struct soap* soap, const char* device)
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
			cfg->H264->H264Profile = tt__H264Profile__Baseline;
		}
	}
	return cfg;
}

int main(int argc, char* argv[])
{		
	std::string device = "/dev/video0";
	std::string url    = "unicast";
	if (argc > 1)
	{
		device.assign(argv[1]);
	}
	if (argc > 2)
	{
		url.assign(argv[2]);
	}
	
	ServiceContext deviceCtx;
	deviceCtx.m_port = 8080;
	deviceCtx.m_rtspport = "554";
	deviceCtx.m_user = "admin";
	deviceCtx.m_password = "admin";
	deviceCtx.m_devices.insert(std::pair<std::string,std::string>(device, url));
	
	struct soap *soap = soap_new();
	soap->user = (void*)&deviceCtx;
	soap->fget = http_get; 
	{	
		MediaBindingService mediaService(soap);
		RecordingBindingService recordingService(soap);
		ReceiverBindingService receiverService(soap);
		ReplayBindingService replayService(soap);
		ImagingBindingService imagingService(soap);
		EventBindingService eventService(soap);
		PullPointSubscriptionBindingService pullPointService(soap);

		DeviceBindingService deviceService(soap);
		soap_register_plugin(deviceService.soap, soap_wsse);		
		
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
			}
		}
	}
	
	soap_destroy(soap);
	soap_end(soap);
	soap_free(soap); 			
	
	return 0;
}
