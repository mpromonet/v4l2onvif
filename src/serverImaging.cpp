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
 serverImaging.cpp
 
 imaging.wsdl server
----------------------------------------------------------------------------- */

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
		if ( errno == 0 )
		{
			timg__GetImagingSettingsResponse->ImagingSettings->Brightness = soap_new_ptr(this->soap, brightness);
		}
	
		float contrast = ctx->getCtrlValue(it->first, V4L2_CID_CONTRAST);
		if ( errno == 0 )
		{
			timg__GetImagingSettingsResponse->ImagingSettings->Contrast = soap_new_ptr(this->soap, contrast);
		}

		float saturation = ctx->getCtrlValue(it->first, V4L2_CID_SATURATION);
		if ( errno == 0 )
		{
			timg__GetImagingSettingsResponse->ImagingSettings->ColorSaturation = soap_new_ptr(this->soap, saturation);
		}

		float sharpness = ctx->getCtrlValue(it->first, V4L2_CID_SHARPNESS);
		if ( errno == 0 )
		{
			timg__GetImagingSettingsResponse->ImagingSettings->Sharpness = soap_new_ptr(this->soap, sharpness);
		}

		int backlightCompensation = ctx->getCtrlValue(it->first, V4L2_CID_BACKLIGHT_COMPENSATION);
		if ( errno == 0 )
		{
			timg__GetImagingSettingsResponse->ImagingSettings->BacklightCompensation = soap_new_tt__BacklightCompensation20(this->soap);
			timg__GetImagingSettingsResponse->ImagingSettings->BacklightCompensation->Mode = backlightCompensation ? tt__BacklightCompensationMode__ON : tt__BacklightCompensationMode__OFF;
		}

		int wideDynamicRange = ctx->getCtrlValue(it->first, V4L2_CID_WIDE_DYNAMIC_RANGE);
		if ( errno == 0 )
		{
			timg__GetImagingSettingsResponse->ImagingSettings->WideDynamicRange = soap_new_tt__WideDynamicRange20(this->soap);
			timg__GetImagingSettingsResponse->ImagingSettings->WideDynamicRange->Mode = wideDynamicRange ? tt__WideDynamicMode__ON : tt__WideDynamicMode__OFF;
		}
		
		int exposure = ctx->getCtrlValue(it->first, V4L2_CID_EXPOSURE_AUTO);		
		if ( errno == 0 )
		{
			timg__GetImagingSettingsResponse->ImagingSettings->Exposure = soap_new_tt__Exposure20(this->soap);
			timg__GetImagingSettingsResponse->ImagingSettings->Exposure->Mode = (exposure == V4L2_EXPOSURE_AUTO) ? tt__ExposureMode__AUTO : tt__ExposureMode__MANUAL;
			float exposureTime = ctx->getCtrlValue(it->first, V4L2_CID_EXPOSURE_ABSOLUTE);
			timg__GetImagingSettingsResponse->ImagingSettings->Exposure->ExposureTime = soap_new_ptr(this->soap, exposureTime);
		}
				
		int whiteBalance = ctx->getCtrlValue(it->first, V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE);		
		if ( errno == 0 )
		{
			timg__GetImagingSettingsResponse->ImagingSettings->WhiteBalance = soap_new_tt__WhiteBalance20(this->soap);
			timg__GetImagingSettingsResponse->ImagingSettings->WhiteBalance->Mode = (whiteBalance == V4L2_WHITE_BALANCE_AUTO) ? tt__WhiteBalanceMode__AUTO : tt__WhiteBalanceMode__MANUAL;
			float redBalance = ctx->getCtrlValue(it->first, V4L2_CID_RED_BALANCE);		
			timg__GetImagingSettingsResponse->ImagingSettings->WhiteBalance->CrGain = soap_new_ptr(this->soap, redBalance);
			float blueBalance = ctx->getCtrlValue(it->first, V4L2_CID_BLUE_BALANCE);		
			timg__GetImagingSettingsResponse->ImagingSettings->WhiteBalance->CbGain = soap_new_ptr(this->soap, blueBalance);
		}
		

		int autofocusMode = ctx->getCtrlValue(it->first, V4L2_CID_FOCUS_AUTO);
		if ( errno == 0 )
		{
			timg__GetImagingSettingsResponse->ImagingSettings->Focus = soap_new_tt__FocusConfiguration20(this->soap);
			timg__GetImagingSettingsResponse->ImagingSettings->Focus->AutoFocusMode = autofocusMode ? tt__AutoFocusMode__AUTO : tt__AutoFocusMode__MANUAL;
		}
		 
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
		if (timg__SetImagingSettings->ImagingSettings->BacklightCompensation)
		{
			int backlightCompensation = (timg__SetImagingSettings->ImagingSettings->BacklightCompensation->Mode == tt__BacklightCompensationMode__ON);
			ctx->setCtrlValue(it->first, V4L2_CID_BACKLIGHT_COMPENSATION, backlightCompensation);
		}
		if (timg__SetImagingSettings->ImagingSettings->WideDynamicRange)
		{
			int wideDynamicMode = (timg__SetImagingSettings->ImagingSettings->WideDynamicRange->Mode == tt__WideDynamicMode__ON);
			ctx->setCtrlValue(it->first, V4L2_CID_WIDE_DYNAMIC_RANGE, wideDynamicMode);
		}
		if (timg__SetImagingSettings->ImagingSettings->Exposure)
		{
			int exposure = timg__SetImagingSettings->ImagingSettings->Exposure->Mode;
			ctx->setCtrlValue(it->first, V4L2_CID_EXPOSURE_AUTO, (exposure == tt__ExposureMode__AUTO) ? V4L2_EXPOSURE_AUTO : V4L2_EXPOSURE_MANUAL);
			if (timg__SetImagingSettings->ImagingSettings->Exposure->ExposureTime)
			{
				int exposureTime = *timg__SetImagingSettings->ImagingSettings->Exposure->ExposureTime;
				ctx->setCtrlValue(it->first, V4L2_CID_EXPOSURE_ABSOLUTE, exposureTime);
			}
		}
		if (timg__SetImagingSettings->ImagingSettings->WhiteBalance)
		{
			int whiteBalance = timg__SetImagingSettings->ImagingSettings->WhiteBalance->Mode;
			ctx->setCtrlValue(it->first, V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE, (whiteBalance == tt__WhiteBalanceMode__AUTO) ? V4L2_WHITE_BALANCE_AUTO : V4L2_WHITE_BALANCE_MANUAL);
			if (timg__SetImagingSettings->ImagingSettings->WhiteBalance->CrGain)
			{
				int redBalance = *timg__SetImagingSettings->ImagingSettings->WhiteBalance->CrGain;
				ctx->setCtrlValue(it->first, V4L2_CID_RED_BALANCE, redBalance);
			}
			if (timg__SetImagingSettings->ImagingSettings->WhiteBalance->CbGain)
			{
				int blueBalance = *timg__SetImagingSettings->ImagingSettings->WhiteBalance->CbGain;
				ctx->setCtrlValue(it->first, V4L2_CID_BLUE_BALANCE, blueBalance);
			}
		}
		if (timg__SetImagingSettings->ImagingSettings->Focus)
		{
			int autofocusMode = (timg__SetImagingSettings->ImagingSettings->Focus->AutoFocusMode == tt__AutoFocusMode__AUTO);
			ctx->setCtrlValue(it->first, V4L2_CID_FOCUS_AUTO, autofocusMode);
		}
	}
	return SOAP_OK;
}

int ImagingBindingService::GetOptions(_timg__GetOptions *timg__GetOptions, _timg__GetOptionsResponse *timg__GetOptionsResponse) 
{
	int ret = SOAP_FAULT;
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
		
		timg__GetOptionsResponse->ImagingOptions->Exposure = soap_new_tt__ExposureOptions20(this->soap);
		timg__GetOptionsResponse->ImagingOptions->Exposure->Mode.push_back(tt__ExposureMode__AUTO);
		timg__GetOptionsResponse->ImagingOptions->Exposure->Mode.push_back(tt__ExposureMode__MANUAL);
		std::pair<int, int> exposureRange = ctx->getCtrlRange(it->first, V4L2_CID_EXPOSURE_ABSOLUTE);
		timg__GetOptionsResponse->ImagingOptions->Exposure->ExposureTime = soap_new_req_tt__FloatRange(this->soap, exposureRange.first, exposureRange.second);
		
		timg__GetOptionsResponse->ImagingOptions->WhiteBalance = soap_new_tt__WhiteBalanceOptions20(this->soap);
		timg__GetOptionsResponse->ImagingOptions->WhiteBalance->Mode.push_back(tt__WhiteBalanceMode__AUTO);
		timg__GetOptionsResponse->ImagingOptions->WhiteBalance->Mode.push_back(tt__WhiteBalanceMode__MANUAL);
		std::pair<int, int> redbalanceRange = ctx->getCtrlRange(it->first, V4L2_CID_RED_BALANCE);
		timg__GetOptionsResponse->ImagingOptions->WhiteBalance->YrGain = soap_new_req_tt__FloatRange(this->soap, redbalanceRange.first, redbalanceRange.second);
		std::pair<int, int> bluebalanceRange = ctx->getCtrlRange(it->first, V4L2_CID_BLUE_BALANCE);
		timg__GetOptionsResponse->ImagingOptions->WhiteBalance->YbGain = soap_new_req_tt__FloatRange(this->soap, bluebalanceRange.first, bluebalanceRange.second);
		
		timg__GetOptionsResponse->ImagingOptions->Focus = soap_new_tt__FocusOptions20(this->soap);
		timg__GetOptionsResponse->ImagingOptions->Focus->AutoFocusModes.push_back(tt__AutoFocusMode__AUTO);
		timg__GetOptionsResponse->ImagingOptions->Focus->AutoFocusModes.push_back(tt__AutoFocusMode__MANUAL);		

		ret = SOAP_OK;
	}
	return ret;
}

int ImagingBindingService::Move(_timg__Move *timg__Move, _timg__MoveResponse *timg__MoveResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	auto it = ctx->m_devices.find(timg__Move->VideoSourceToken);
	if (it != ctx->m_devices.end())
	{	
		if (timg__Move->Focus)
		{
			if (timg__Move->Focus->Absolute)
			{
				int position = timg__Move->Focus->Absolute->Position;
				ctx->setCtrlValue(it->first, V4L2_CID_FOCUS_ABSOLUTE, position);
			}
			if (timg__Move->Focus->Relative)
			{
				int position = timg__Move->Focus->Relative->Distance;
				ctx->setCtrlValue(it->first, V4L2_CID_FOCUS_RELATIVE, position);
			}
		}
	}
	
	return SOAP_OK;
}

int ImagingBindingService::Stop(_timg__Stop *timg__Stop, _timg__StopResponse *timg__StopResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	auto it = ctx->m_devices.find(timg__Stop->VideoSourceToken);
	if (it != ctx->m_devices.end())
	{	
		ctx->setCtrlValue(it->first, V4L2_CID_AUTO_FOCUS_STOP, 0);
	}
	return SOAP_OK;
}

int ImagingBindingService::GetStatus(_timg__GetStatus *timg__GetStatus, _timg__GetStatusResponse *timg__GetStatusResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	auto it = ctx->m_devices.find(timg__GetStatus->VideoSourceToken);
	if (it != ctx->m_devices.end())
	{	
		timg__GetStatusResponse->Status = soap_new_tt__ImagingStatus20(this->soap);
		timg__GetStatusResponse->Status->FocusStatus20 = soap_new_tt__FocusStatus20(this->soap);
		
		timg__GetStatusResponse->Status->FocusStatus20->Position = ctx->getCtrlValue(it->first, V4L2_CID_FOCUS_ABSOLUTE);
		int status = ctx->getCtrlValue(it->first,V4L2_CID_AUTO_FOCUS_STATUS);
		tt__MoveStatus moveStatus = tt__MoveStatus__UNKNOWN;
		switch (status)
		{
			case V4L2_AUTO_FOCUS_STATUS_IDLE: moveStatus = tt__MoveStatus__IDLE  ; break;
			case V4L2_AUTO_FOCUS_STATUS_BUSY: moveStatus = tt__MoveStatus__MOVING; break;
		}
		timg__GetStatusResponse->Status->FocusStatus20->MoveStatus = moveStatus;
	}
	
	return SOAP_OK;
}

int ImagingBindingService::GetMoveOptions(_timg__GetMoveOptions *timg__GetMoveOptions, _timg__GetMoveOptionsResponse *timg__GetMoveOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	auto it = ctx->m_devices.find(timg__GetMoveOptions->VideoSourceToken);
	if (it != ctx->m_devices.end())
	{	
		timg__GetMoveOptionsResponse->MoveOptions = soap_new_tt__MoveOptions20(this->soap);
		
		std::pair<int,int> absRange = ctx->getCtrlRange(it->first, V4L2_CID_FOCUS_ABSOLUTE);
		if (errno == 0)
		{
			timg__GetMoveOptionsResponse->MoveOptions->Absolute = soap_new_tt__AbsoluteFocusOptions(this->soap);
			float min = absRange.first;
			float max = absRange.second;
			timg__GetMoveOptionsResponse->MoveOptions->Absolute->Position = soap_new_req_tt__FloatRange(this->soap, min, max);
		}
		
		std::pair<int,int> relRange = ctx->getCtrlRange(it->first, V4L2_CID_FOCUS_RELATIVE);
		if (errno == 0)
		{
			timg__GetMoveOptionsResponse->MoveOptions->Relative = soap_new_tt__RelativeFocusOptions20(this->soap);
			float min = relRange.first;
			float max = relRange.second;
			timg__GetMoveOptionsResponse->MoveOptions->Relative->Distance = soap_new_req_tt__FloatRange(this->soap, min, max);
		}
	}
	
	return SOAP_OK;
}

int ImagingBindingService::GetPresets(_timg__GetPresets *timg__GetPresets, _timg__GetPresetsResponse *timg__GetPresetsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ImagingBindingService::GetCurrentPreset(_timg__GetCurrentPreset *timg__GetCurrentPreset, _timg__GetCurrentPresetResponse *timg__GetCurrentPresetResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ImagingBindingService::SetCurrentPreset(_timg__SetCurrentPreset *timg__SetCurrentPreset, _timg__SetCurrentPresetResponse *timg__SetCurrentPresetResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

