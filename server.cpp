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
#include <thread>

#include "DeviceBinding.nsmap"
#include "soapDeviceBindingService.h"
#include "soapMediaBindingService.h"
#include "soapRecordingBindingService.h"
#include "soapReplayBindingService.h"
#include "soapEventBindingService.h"
#include "soapPullPointSubscriptionBindingService.h"

#include "wsseapi.h"

#include "serviceContext.h"

int http_get(struct soap *soap)
{
	int retCode = 404;
	ServiceContext* ctx = (ServiceContext*)soap->user;
	FILE *fd = fopen(ctx->m_wsdlurl.c_str(), "rb"); 
	if (fd != NULL)
	{
		soap->http_content = "text/xml"; 
		soap_response(soap, SOAP_FILE);
		for (;;)
		{
			size_t r = fread(soap->tmpbuf, 1, sizeof(soap->tmpbuf), fd);
			if (!r)
				break;
			if (soap_send_raw(soap, soap->tmpbuf, r))
				break; // can't send, but little we can do about that
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
			if (ifa->ifa_addr != NULL)			
			{
				int family = ifa->ifa_addr->sa_family;
				struct sockaddr_in* addr = (struct sockaddr_in*)ifa->ifa_addr;
				struct sockaddr_in* mask = (struct sockaddr_in*)ifa->ifa_netmask;
				if (mask != NULL)
				{
					if ( (family == AF_INET) && ( (addr->sin_addr.s_addr & mask->sin_addr.s_addr) == (clientip & mask->sin_addr.s_addr)) )
					{
						if (getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, sizeof(host), NULL, 0, NI_NUMERICHOST) == 0)
						{
							serverip = host;
							std::cout << "serverip:" << host << std::endl;
							break;
						}
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
	
	ServiceContext mediaCtx("media.wsdl", host, 8081);
	MediaBindingService mediaService;
	mediaService.user = (void*)&mediaCtx;
	mediaService.fget = http_get; 
	std::thread mediaThread(&MediaBindingService::run, &mediaService, mediaCtx.m_port);	

	ServiceContext recordingCtx("recording.wsdl", host, 8082);
	RecordingBindingService recordingService;
	recordingService.user = (void*)&recordingCtx;
	recordingService.fget = http_get; 	
	std::thread recordingThread(&RecordingBindingService::run, &recordingService, recordingCtx.m_port);	

	ServiceContext replayCtx("replay.wsdl", host, 8083);
	ReplayBindingService replayService;
	replayService.user = (void*)&replayCtx;
	replayService.fget = http_get; 	
	std::thread replayThread(&ReplayBindingService::run, &replayService, replayCtx.m_port);	

	ServiceContext eventCtx("event.wsdl", host, 8084);
	EventBindingService eventService;
	eventService.user = (void*)&eventCtx;
	eventService.fget = http_get; 	
	std::thread eventThread(&EventBindingService::run, &eventService, eventCtx.m_port);	

	PullPointSubscriptionBindingService pullPointService;
	std::thread pullPointThread(&PullPointSubscriptionBindingService::run, &pullPointService, 8085);	

	ServiceContext deviceCtx("devicemgmt.wsdl", host, 8080);
	DeviceBindingService deviceService;
	deviceService.user = (void*)&deviceCtx;
	deviceService.fget = http_get; 
	soap_register_plugin(&deviceService, soap_wsse);
	if (deviceService.run(deviceCtx.m_port) != SOAP_OK)
	{
		deviceService.soap_stream_fault(std::cerr);
	}
		
	pullPointThread.join();
	eventThread.join();
	replayThread.join();
	recordingThread.join();
	mediaThread.join();
	
	return 0;
}
