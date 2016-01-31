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

#include <thread>

#include "DeviceBinding.nsmap"
#include "soapDeviceBindingService.h"
#include "soapMediaBindingService.h"
#include "soapRecordingBindingService.h"
#include "soapReplayBindingService.h"

#include "wsseapi.h"

int http_get(struct soap *soap)
{
	int retCode = 404;
	FILE *fd = fopen((const char*)soap->user, "rb"); 
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

int main(int argc, char* argv[])
{	
	MediaBindingService mediaService;
	mediaService.user = (void*)"media.wsdl";
	mediaService.fget = http_get; 
	std::thread mediaThread(&MediaBindingService::run, &mediaService, 8081);	

	RecordingBindingService recordingService;
	recordingService.user = (void*)"recording.wsdl";
	recordingService.fget = http_get; 	
	std::thread recordingThread(&RecordingBindingService::run, &recordingService, 8082);	

	ReplayBindingService replayService;
	replayService.user = (void*)"recording.wsdl";
	replayService.fget = http_get; 	
	std::thread replayThread(&ReplayBindingService::run, &replayService, 8083);	
	
	DeviceBindingService deviceService;
	deviceService.user = (void*)"devicemgmt.wsdl";
	deviceService.fget = http_get; 
	soap_wsse_verify_auto(&deviceService, SOAP_SMD_NONE, NULL, 0);
	if (deviceService.run(8080) != SOAP_OK)
	{
		deviceService.soap_stream_fault(std::cerr);
	}
	
	replayThread.join();
	recordingThread.join();
	mediaThread.join();
	
	return 0;
}
