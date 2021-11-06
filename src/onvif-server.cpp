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
#include "V4l2Output.h"
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
	std::string outdevice = "/dev/video10";
	std::string username;

	std::string rtspport = "8554";
	int httpport = 8080;
	ServiceContext deviceCtx;
	std::map<std::string, V4l2Capture*> deviceList;

	int c = 0;
	while ((c = getopt (argc, argv, "h" "u:p:" "H:R:" "i:o:")) != -1)
	{
		switch (c)
		{
			case 'H':	httpport      = atoi(optarg); break;
			case 'R':	rtspport      = optarg; break;

			case 'u':	username  = optarg; break;
			case 'p':	deviceCtx.m_userList[username] = User(optarg,tt__UserLevel__Administrator); break;
			
			case 'i':	deviceList[optarg] = NULL; break;
			
			case 'o':	outdevice = optarg; break;
			
			case 'h':
				std::cout << argv[0] << " [-H http port] [-R rtsp port] [-u username] [-p password] [-i v4l2 input device] [-o v4l2 output device]" << std::endl;
				exit(0);
			break;
		}
	}
	if (deviceList.empty()) {
		deviceList["/dev/video0"] = NULL;
	}

	std::cout << "Http:" << httpport << " rtsp:" << rtspport << std::endl;
		
	std::string rtspurl;
	rtspurl = "rtsp://" + deviceCtx.getLocalIp() + ":" + rtspport + "/";
	for (auto & device : deviceList) {
		std::string url = basename(device.first.c_str());
		deviceCtx.m_devices.insert(std::pair<std::string,std::string>(device.first, rtspurl + url));
	}
	deviceCtx.m_port          = httpport;
	deviceCtx.m_rtspport      = atoi(rtspport.c_str());
	deviceCtx.m_outdevice     = outdevice;
	const time_t timestamp = time(NULL);
	struct tm * localtm = localtime(&timestamp);
	deviceCtx.m_timezone     = localtm->tm_zone;
	deviceCtx.m_isdst        = localtm->tm_isdst;

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

			wsdconf conf(url.c_str()
							,"\"http://www.onvif.org/ver10/network/wsdl\":NetworkVideoTransmitter"
							, deviceCtx.getScopesString().c_str()
							, soap_wsa_rand_uuid(soap));

			std::thread wsdd( [&conf] { 
				wsd_server(conf); 
			});

			// start RTSP
			V4l2RTSPServer rtspServer(deviceCtx.m_rtspport);

			for (auto & device : deviceList) {
				std::list<unsigned int> videoformatList = {V4L2_PIX_FMT_H264, V4L2_PIX_FMT_MJPEG, V4L2_PIX_FMT_JPEG, 0 };
				V4l2Output* out = NULL;
				V4L2DeviceParameters inParam(device.first.c_str(), videoformatList, 0, 0, 0);
				StreamReplicator* videoReplicator = rtspServer.CreateVideoReplicator(
								inParam,
								5, true, true,
								"", IOTYPE_MMAP, out);

				if (videoReplicator)
				{
					std::string url = basename(device.first.c_str());
					std::cout << "add RTSP session url:" << url << std::endl;
					rtspServer.AddUnicastSession(url, videoReplicator, NULL);
				} else {
					std::cout << "Fails to create Source for device:" << device.first << std::endl;
				}
			}

			char rtspstop = 0; 
			std::thread rtsp( [&rtspServer,&rtspstop] {
				rtspServer.eventLoop(&rtspstop); 
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
