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
	
int main(int argc, char* argv[])
{		
	std::string host("0.0.0.0");
	int port = 8080;
	std::string device("/dev/video0");
	
	ServiceContext deviceCtx;
	deviceCtx.m_port = port;
	deviceCtx.m_rtspport = "554";
	deviceCtx.m_device = device;
	deviceCtx.m_rtspurl = "unicast";
	deviceCtx.m_user    = "admin";
	deviceCtx.m_password= "admin";
	
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
