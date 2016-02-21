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

#include "DeviceBinding.nsmap"
#include "soapDeviceBindingService.h"
#include "soapDeviceIOBindingService.h"

#include "soapMediaBindingService.h"
#include "soapImagingBindingService.h"

#include "soapReceiverBindingService.h"

#include "soapRecordingBindingService.h"
#include "soapReplayBindingService.h"
#include "soapSearchBindingService.h"

#include "soapDisplayBindingService.h"

#include "soapEventBindingService.h"
#include "soapPullPointSubscriptionBindingService.h"
#include "soapNotificationProducerBindingService.h"

#include "wsseapi.h"

#include "onvif_impl.h"

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

int main(int argc, char* argv[])
{		
	std::string indevice  = "/dev/video0";
	std::string path      = "unicast";
	std::string outdevice = "/dev/video10";
	std::string username;
	std::string password;	
	int port = 8080;
	int c = 0;
	while ((c = getopt (argc, argv, "h" "u:p:" "i:I:o:O:")) != -1)
	{
		switch (c)
		{
			case 'u':	username = optarg; break;
			case 'p':	password = optarg; break;
			case 'i':	indevice = optarg; break;
			case 'I':	path     = optarg; break;
			case 'h':
				std::cout << argv[0] << " [-u username] [-p password] [-i v4l2 input device] [-I rtsp server] [-o v4l2 output device] [-O rtsp client]" << std::endl;
				exit(0);
			break;
		}
	}
	std::cout << "Listening to " << port << std::endl;
		
	ServiceContext deviceCtx;
	deviceCtx.m_devices.insert(std::pair<std::string,std::string>(indevice, path));
	deviceCtx.m_port          = port;
	deviceCtx.m_rtspport      = "554";
	deviceCtx.m_user          = username;
	deviceCtx.m_password      = password;
	deviceCtx.m_outdevice     = outdevice;
	deviceCtx.Manufacturer    = "Manufacturer";
	deviceCtx.Model           = "Model";
	deviceCtx.FirmwareVersion = "Model";
	
	struct soap *soap = soap_new();
	soap->user = (void*)&deviceCtx;
	soap->fget = http_get; 
	{			
		DeviceBindingService                deviceService(soap);
		DeviceIOBindingService              deviceIOService(soap);
		
		MediaBindingService                 mediaService(soap);
		ImagingBindingService               imagingService(soap);
		
		RecordingBindingService             recordingService(soap);
		ReplayBindingService                replayService(soap);
		SearchBindingService                searchService(soap);
		
		ReceiverBindingService              receiverService(soap);

		DisplayBindingService               displayService(soap);
		
		EventBindingService                 eventService(soap);
		PullPointSubscriptionBindingService pullPointService(soap);
		NotificationProducerBindingService  notificationProducerService(soap);

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
				else if (displayService.dispatch() != SOAP_NO_METHOD)
				{
					soap_send_fault(soap);
					soap_stream_fault(soap, std::cerr);
				}
				else if (deviceIOService.dispatch() != SOAP_NO_METHOD)
				{
					soap_send_fault(soap);
					soap_stream_fault(soap, std::cerr);
				}		
				else if (notificationProducerService.dispatch() != SOAP_NO_METHOD)
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
