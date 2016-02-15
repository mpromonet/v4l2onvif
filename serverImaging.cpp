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

#include <linux/videodev2.h>

#include "soapImagingBindingService.h"
#include "onvif_impl.h"

int ImagingBindingService::GetServiceCapabilities(_timg__GetServiceCapabilities *timg__GetServiceCapabilities, _timg__GetServiceCapabilitiesResponse *timg__GetServiceCapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	timg__GetServiceCapabilitiesResponse->Capabilities = ctx->getImagingServiceCapabilities(this->soap);		
	return SOAP_OK;
}

int ImagingBindingService::GetImagingSettings(_timg__GetImagingSettings *timg__GetImagingSettings, _timg__GetImagingSettingsResponse *timg__GetImagingSettingsResponse)  
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	auto it = ctx->m_devices.find(timg__GetImagingSettings->VideoSourceToken);
	if (it != ctx->m_devices.end())
	{
		timg__GetImagingSettingsResponse->ImagingSettings = soap_new_tt__ImagingSettings20(this->soap);
		float brightness = ctx->getCtrlValue(it->first, V4L2_CID_BRIGHTNESS);
		timg__GetImagingSettingsResponse->ImagingSettings->Brightness = soap_new_ptr(this->soap, brightness);
		float contrast = ctx->getCtrlValue(it->first, V4L2_CID_CONTRAST);
		timg__GetImagingSettingsResponse->ImagingSettings->Contrast = soap_new_ptr(this->soap, contrast);
		float saturation = ctx->getCtrlValue(it->first, V4L2_CID_SATURATION);
		timg__GetImagingSettingsResponse->ImagingSettings->ColorSaturation = soap_new_ptr(this->soap, saturation);
		float sharpness = ctx->getCtrlValue(it->first, V4L2_CID_SHARPNESS);
		timg__GetImagingSettingsResponse->ImagingSettings->Sharpness = soap_new_ptr(this->soap, sharpness);
	}
	
	return SOAP_OK;
}

int ImagingBindingService::SetImagingSettings(_timg__SetImagingSettings *timg__SetImagingSettings, _timg__SetImagingSettingsResponse *timg__SetImagingSettingsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	auto it = ctx->m_devices.find(timg__SetImagingSettings->VideoSourceToken);
	if (it != ctx->m_devices.end())
	{	
		if (timg__SetImagingSettings->ImagingSettings->Brightness)
		{
			int brightness = *timg__SetImagingSettings->ImagingSettings->Brightness;
			ctx->setCtrlValue(it->first, V4L2_CID_BRIGHTNESS, brightness);
		}
		if (timg__SetImagingSettings->ImagingSettings->Contrast)
		{
			int contrast = *timg__SetImagingSettings->ImagingSettings->Contrast;
			ctx->setCtrlValue(it->first, V4L2_CID_CONTRAST, contrast);
		}
		if (timg__SetImagingSettings->ImagingSettings->ColorSaturation)
		{
			int saturation = *timg__SetImagingSettings->ImagingSettings->ColorSaturation;
			ctx->setCtrlValue(it->first, V4L2_CID_SATURATION, saturation);
		}
		if (timg__SetImagingSettings->ImagingSettings->Sharpness)
		{
			int sharpness = *timg__SetImagingSettings->ImagingSettings->Sharpness;
			ctx->setCtrlValue(it->first, V4L2_CID_SHARPNESS, sharpness);
		}
	}
	return SOAP_OK;
}

int ImagingBindingService::GetOptions(_timg__GetOptions *timg__GetOptions, _timg__GetOptionsResponse *timg__GetOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	auto it = ctx->m_devices.find(timg__GetOptions->VideoSourceToken);
	if (it != ctx->m_devices.end())
	{
		timg__GetOptionsResponse->ImagingOptions = soap_new_tt__ImagingOptions20(this->soap);
		std::pair<int,int> brightnessRange = ctx->getCtrlRange(it->first, V4L2_CID_BRIGHTNESS);
		timg__GetOptionsResponse->ImagingOptions->Brightness = soap_new_req_tt__FloatRange(this->soap, brightnessRange.first, brightnessRange.second);
		std::pair<int,int> contrastRange = ctx->getCtrlRange(it->first, V4L2_CID_CONTRAST);
		timg__GetOptionsResponse->ImagingOptions->Contrast = soap_new_req_tt__FloatRange(this->soap, contrastRange.first, contrastRange.second);
		std::pair<int,int> saturationRange = ctx->getCtrlRange(it->first, V4L2_CID_SATURATION);
		timg__GetOptionsResponse->ImagingOptions->ColorSaturation = soap_new_req_tt__FloatRange(this->soap, saturationRange.first, saturationRange.second);
		std::pair<int,int> sharpnessRange = ctx->getCtrlRange(it->first, V4L2_CID_SHARPNESS);
		timg__GetOptionsResponse->ImagingOptions->Sharpness = soap_new_req_tt__FloatRange(this->soap, sharpnessRange.first, sharpnessRange.second);
	}
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
	timg__GetStatusResponse->Status = soap_new_tt__ImagingStatus20(this->soap);
	timg__GetStatusResponse->Status->FocusStatus20 = soap_new_tt__FocusStatus20(this->soap);
	return SOAP_OK;
}

int ImagingBindingService::GetMoveOptions(_timg__GetMoveOptions *timg__GetMoveOptions, _timg__GetMoveOptionsResponse *timg__GetMoveOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

