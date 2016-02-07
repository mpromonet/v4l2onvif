/* ---------------------------------------------------------------------------
** this->soap software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** serverImaging.cpp
** 
** imaging.wsdl server
**
** -------------------------------------------------------------------------*/


#include "soapImagingBindingService.h"
#include "serviceContext.h"

int ImagingBindingService::GetServiceCapabilities(_timg__GetServiceCapabilities *timg__GetServiceCapabilities, _timg__GetServiceCapabilitiesResponse *timg__GetServiceCapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ImagingBindingService::GetImagingSettings(_timg__GetImagingSettings *timg__GetImagingSettings, _timg__GetImagingSettingsResponse *timg__GetImagingSettingsResponse)  
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ImagingBindingService::SetImagingSettings(_timg__SetImagingSettings *timg__SetImagingSettings, _timg__SetImagingSettingsResponse *timg__SetImagingSettingsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ImagingBindingService::GetOptions(_timg__GetOptions *timg__GetOptions, _timg__GetOptionsResponse *timg__GetOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ImagingBindingService::Move(_timg__Move *timg__Move, _timg__MoveResponse *timg__MoveResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ImagingBindingService::Stop(_timg__Stop *timg__Stop, _timg__StopResponse *timg__StopResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ImagingBindingService::GetStatus(_timg__GetStatus *timg__GetStatus, _timg__GetStatusResponse *timg__GetStatusResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ImagingBindingService::GetMoveOptions(_timg__GetMoveOptions *timg__GetMoveOptions, _timg__GetMoveOptionsResponse *timg__GetMoveOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

