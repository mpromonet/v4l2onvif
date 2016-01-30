/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** client.cpp
** 
** devicemgmt.wsdl client
**
** -------------------------------------------------------------------------*/

#include "DeviceBinding.nsmap"
#include "soapDeviceBindingProxy.h"
#include "soapMediaBindingProxy.h"

int main(int argc, char* argv[])
{
	std::string url = "http://127.0.0.1:8080";
	if (argc > 1)
	{
		url.assign(argv[1]);
	}
        DeviceBindingProxy deviceProxy(url.c_str());
	
	_tds__GetDeviceInformation         tds__GetDeviceInformation;
	_tds__GetDeviceInformationResponse tds__GetDeviceInformationResponse;
	if (deviceProxy.GetDeviceInformation(&tds__GetDeviceInformation, tds__GetDeviceInformationResponse) == SOAP_OK)
	{
		std::cout << tds__GetDeviceInformationResponse.Manufacturer << std::endl;
	}
	else
	{
		deviceProxy.soap_stream_fault(std::cerr);
	}


        MediaBindingProxy mediaProxy("http://127.0.0.1:9090");
	
	_trt__GetStreamUri         trt__GetStreamUri;
	_trt__GetStreamUriResponse trt__GetStreamUriResponse;
	if (mediaProxy.GetStreamUri(&trt__GetStreamUri, trt__GetStreamUriResponse) == SOAP_OK)
	{
		std::cout << trt__GetStreamUriResponse.MediaUri->Uri << std::endl;
	}
	else
	{
		mediaProxy.soap_stream_fault(std::cerr);
	}
	
        return 0;
}


