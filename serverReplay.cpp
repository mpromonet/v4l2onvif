/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** serverReplay.cpp
** 
** replay.wsdl server
**
** -------------------------------------------------------------------------*/


#include "soapReplayBindingService.h"

int ReplayBindingService::GetServiceCapabilities(_trp__GetServiceCapabilities *trp__GetServiceCapabilities, _trp__GetServiceCapabilitiesResponse &trp__GetServiceCapabilitiesResponse) 
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ReplayBindingService::GetReplayUri(_trp__GetReplayUri *trp__GetReplayUri, _trp__GetReplayUriResponse &trp__GetReplayUriResponse) 
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	trp__GetReplayUriResponse.Uri = "rtsp://";
	trp__GetReplayUriResponse.Uri.append(this->host);
	trp__GetReplayUriResponse.Uri.append("/");
	if (trp__GetReplayUri != NULL)
	{
		trp__GetReplayUriResponse.Uri.append(trp__GetReplayUri->RecordingToken);
	}
	return SOAP_OK;
}

int ReplayBindingService::GetReplayConfiguration(_trp__GetReplayConfiguration *trp__GetReplayConfiguration, _trp__GetReplayConfigurationResponse &trp__GetReplayConfigurationResponse) 
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ReplayBindingService::SetReplayConfiguration(_trp__SetReplayConfiguration *trp__SetReplayConfiguration, _trp__SetReplayConfigurationResponse &trp__SetReplayConfigurationResponse) 
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return SOAP_OK;
}
