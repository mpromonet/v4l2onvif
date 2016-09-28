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
#include "soapSubscriptionManagerBindingService.h"


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

#define FOREACH_SERVICE(APPLY,soap) \
		APPLY(DeviceBindingService,soap)    \
		APPLY(DeviceIOBindingService,soap)  \
		\
		APPLY(MediaBindingService,soap)     \
		APPLY(ImagingBindingService,soap)   \
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
	std::string inpath    = "unicast";
	std::string outdevice = "/dev/video10";
	std::string outpath   = "rtsp://127.0.0.1:8554/unicast";
	std::string username;
	std::string password;	
	int port = 8080;
	int c = 0;
	while ((c = getopt (argc, argv, "h" "u:p:" "P:" "i:I:o:O:")) != -1)
	{
		switch (c)
		{
			case 'P':	port      = atoi(optarg); break;

			case 'u':	username  = optarg; break;
			case 'p':	password  = optarg; break;
			
			case 'i':	indevice  = optarg; break;
			case 'I':	inpath    = optarg; break;
			
			case 'o':	outdevice = optarg; break;
			case 'O':	outpath   = optarg; break;
			
			case 'h':
				std::cout << argv[0] << " [-u username] [-p password] [-i v4l2 input device] [-I rtsp server] [-o v4l2 output device] [-O rtsp client]" << std::endl;
				exit(0);
			break;
		}
	}
	std::cout << "Listening to " << port << std::endl;
		
	ServiceContext deviceCtx;
	deviceCtx.m_devices.insert(std::pair<std::string,std::string>(indevice, inpath));
	deviceCtx.m_port          = port;
	deviceCtx.m_user          = username;
	deviceCtx.m_password      = password;
	deviceCtx.m_outdevice     = outdevice;
	deviceCtx.Manufacturer    = "Manufacturer";
	deviceCtx.Model           = "Model";
	deviceCtx.FirmwareVersion = "FirmwareVersion";
	deviceCtx.SerialNumber    = "SerialNumber";
	deviceCtx.HardwareId      = "HardwareId";
	deviceCtx.m_scope.push_back("onvif://www.onvif.org/name/Name");
	deviceCtx.m_scope.push_back("onvif://www.onvif.org/location/Here");
	deviceCtx.m_scope.push_back("onvif://www.onvif.org/Profile/Streaming");
	deviceCtx.m_scope.push_back("onvif://www.onvif.org/Profile/G");
	
	struct soap *soap = soap_new();
	soap->user = (void*)&deviceCtx;
	soap->fget = http_get; 
	{			
		FOREACH_SERVICE(DECLARE_SERVICE,soap)

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
				FOREACH_SERVICE(DISPATCH_SERVICE,soap)
				else 
				{
					std::cout << "Unknown service" << std::endl;				
				}
					
			}
		}
	}
	
	soap_destroy(soap);
	soap_end(soap);
	soap_free(soap); 			
	
	return 0;
}
