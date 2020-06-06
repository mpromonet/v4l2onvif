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
 server.cpp
 
 onvif server
----------------------------------------------------------------------------- */

#include <sstream>
#include <thread>

#include "DeviceBinding.nsmap"
#include "soapDeviceBindingService.h"
#include "soapDeviceIOBindingService.h"

#include "soapMediaBindingService.h"
#include "soapImagingBindingService.h"

#include "soapReceiverBindingService.h"

#include "soapRecordingBindingService.h"
#include "soapReplayBindingService.h"
#include "soapSearchBindingService.h"

#include "soapPTZBindingService.h"

#include "soapDisplayBindingService.h"

#include "soapEventBindingService.h"
#include "soapPullPointSubscriptionBindingService.h"
#include "soapNotificationProducerBindingService.h"
#include "soapSubscriptionManagerBindingService.h"

// ws-discovery
#include "wsseapi.h"
#include "wsd-server.h"

// v4l2rstp
#include "logger.h"
#include "V4l2Capture.h"
#include "DeviceSourceFactory.h"
#include "V4l2RTSPServer.h"


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

#define FOREACH_SERVICE(APPLY,soap) \
		APPLY(DeviceBindingService,soap)    \
		APPLY(DeviceIOBindingService,soap)  \
		\
		APPLY(MediaBindingService,soap)     \
		APPLY(ImagingBindingService,soap)   \
                \
		APPLY(PTZBindingService,soap)   \
                \
		APPLY(RecordingBindingService,soap) \
		APPLY(ReplayBindingService,soap)    \
		APPLY(SearchBindingService,soap)    \
		\
		APPLY(ReceiverBindingService,soap)  \
		\
		APPLY(DisplayBindingService,soap)   \
		\
		APPLY(EventBindingService,soap)                 \
		APPLY(PullPointSubscriptionBindingService,soap) \
		APPLY(NotificationProducerBindingService,soap)  \
		APPLY(SubscriptionManagerBindingService,soap)  \
/**/

#define DECLARE_SERVICE(service,soap) service service ## _inst(soap);

#define DISPATCH_SERVICE(service,soap) \
				else if (service ## _inst.dispatch() != SOAP_NO_METHOD) {\
					soap_send_fault(soap); \
					soap_stream_fault(soap, std::cerr); \
				}


int main(int argc, char* argv[])
{		
	std::string indevice  = "/dev/video0";
	std::string outdevice = "/dev/video10";
	std::string username;
	std::string password;	
	std::string rtspport = "8554";
	int port = 8080;
	int c = 0;
	while ((c = getopt (argc, argv, "h" "u:p:" "P:" "i:o:")) != -1)
	{
		switch (c)
		{
			case 'P':	port      = atoi(optarg); break;

			case 'u':	username  = optarg; break;
			case 'p':	password  = optarg; break;
			
			case 'i':	indevice  = optarg; break;
			
			case 'o':	outdevice = optarg; break;
			
			case 'h':
				std::cout << argv[0] << " [-u username] [-p password] [-i v4l2 input device] [-o v4l2 output device]" << std::endl;
				exit(0);
			break;
		}
	}

	V4L2DeviceParameters param(indevice.c_str(), 0, 0, 0, 0);
	V4l2Capture* videoCapture = V4l2Capture::create(param, V4l2Access::IOTYPE_MMAP);

	std::cout << "Listening to " << port << std::endl;
		
	ServiceContext deviceCtx;
	std::string rtspurl;
	rtspurl = "rtsp://" + deviceCtx.getLocalIp() + ":" + rtspport + "/";
	deviceCtx.m_devices.insert(std::pair<std::string,std::string>(indevice, rtspurl));
	deviceCtx.m_port          = port;
	deviceCtx.m_userList[username] = User(password,tt__UserLevel__Administrator);
	deviceCtx.m_outdevice     = outdevice;
	

	// start WS server
	struct soap *soap = soap_new();
	soap->user = (void*)&deviceCtx;
	soap->fget = http_get; 
	soap->bind_flags |= SO_REUSEADDR;
	{			
		FOREACH_SERVICE(DECLARE_SERVICE,soap)

		if (!soap_valid_socket(soap_bind(soap, NULL, deviceCtx.m_port, 100))) 
		{
			soap_stream_fault(soap, std::cerr);
		}
		else
		{
			// start WS-Discovery
			std::ostringstream os;
			os << "http://" << deviceCtx.getLocalIp() << ":" << deviceCtx.m_port << "/onvif/device_service";
			std::string url(os.str());
			std::cout << "Published URL:" << url << std::endl;
			std::string scopes;
			for (std::string scope : deviceCtx.getScopes()) {
				scopes += scope + " ";
			}
			wsdconf conf(url.c_str()
							,"\"http://www.onvif.org/ver10/network/wsdl\":NetworkVideoTransmitter"
							, scopes.c_str()
							, soap_wsa_rand_uuid(soap)
							, 1 );
			std::thread wsdd( [&conf] { 
				wsd_server(conf); 
			});

			// start RTSP
			V4l2RTSPServer rtspserver(atoi(rtspport.c_str()));
			if (videoCapture) {
				StreamReplicator* videoReplicator = DeviceSourceFactory::createStreamReplicator(rtspserver.env(), videoCapture->getFormat(), new DeviceCaptureAccess<V4l2Capture>(videoCapture));
				if (videoReplicator)
				{
					rtspserver.addSession("", UnicastServerMediaSubsession::createNew(*rtspserver.env(), videoReplicator, V4l2RTSPServer::getVideoRtpFormat(videoCapture->getFormat())));			
				}
			}
			char rtspstop = 0; 
			std::thread rtsp( [&rtspserver,&rtspstop] {
				rtspserver.eventLoop(&rtspstop); 
			});		

			// SOAP services
			while (soap_accept(soap) != SOAP_OK) 
			{
				if (soap_begin_serve(soap))
				{
					soap_stream_fault(soap, std::cerr);
				}
				FOREACH_SERVICE(DISPATCH_SERVICE,soap)
				else 
				{
					std::cout << "Unknown service" << std::endl;				
				}				
			}
			rtspstop = 1;
			rtsp.join();

			conf.m_stop = true;
			wsdd.join();
		}
	}
	
	soap_destroy(soap);
	soap_end(soap);
	soap_free(soap); 			
	
	return 0;
}
