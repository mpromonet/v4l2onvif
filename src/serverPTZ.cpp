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
 serverPTZ.cpp
 
 ptz.wsdl server
----------------------------------------------------------------------------- */

#include <linux/videodev2.h>

#include "soapPTZBindingService.h"
#include "onvif_impl.h"

/// Web service operation 'GetServiceCapabilities' (returns SOAP_OK or error code)
int PTZBindingService::GetServiceCapabilities(_tptz__GetServiceCapabilities *tptz__GetServiceCapabilities, _tptz__GetServiceCapabilitiesResponse *tptz__GetServiceCapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	tptz__GetServiceCapabilitiesResponse->Capabilities = ctx->getPTZServiceCapabilities(this->soap);
	return SOAP_OK;
}

/// Web service operation 'GetConfigurations' (returns SOAP_OK or error code)
int PTZBindingService::GetConfigurations(_tptz__GetConfigurations *tptz__GetConfigurations, _tptz__GetConfigurationsResponse *tptz__GetConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'GetPresets' (returns SOAP_OK or error code)
int PTZBindingService::GetPresets(_tptz__GetPresets *tptz__GetPresets, _tptz__GetPresetsResponse *tptz__GetPresetsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'SetPreset' (returns SOAP_OK or error code)
int PTZBindingService::SetPreset(_tptz__SetPreset *tptz__SetPreset, _tptz__SetPresetResponse *tptz__SetPresetResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'RemovePreset' (returns SOAP_OK or error code)
int PTZBindingService::RemovePreset(_tptz__RemovePreset *tptz__RemovePreset, _tptz__RemovePresetResponse *tptz__RemovePresetResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'GotoPreset' (returns SOAP_OK or error code)
int PTZBindingService::GotoPreset(_tptz__GotoPreset *tptz__GotoPreset, _tptz__GotoPresetResponse *tptz__GotoPresetResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'GetStatus' (returns SOAP_OK or error code)
int PTZBindingService::GetStatus(_tptz__GetStatus *tptz__GetStatus, _tptz__GetStatusResponse *tptz__GetStatusResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'GetConfiguration' (returns SOAP_OK or error code)
int PTZBindingService::GetConfiguration(_tptz__GetConfiguration *tptz__GetConfiguration, _tptz__GetConfigurationResponse *tptz__GetConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'GetNodes' (returns SOAP_OK or error code)
int PTZBindingService::GetNodes(_tptz__GetNodes *tptz__GetNodes, _tptz__GetNodesResponse *tptz__GetNodesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'GetNode' (returns SOAP_OK or error code)
int PTZBindingService::GetNode(_tptz__GetNode *tptz__GetNode, _tptz__GetNodeResponse *tptz__GetNodeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'SetConfiguration' (returns SOAP_OK or error code)
int PTZBindingService::SetConfiguration(_tptz__SetConfiguration *tptz__SetConfiguration, _tptz__SetConfigurationResponse *tptz__SetConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'GetConfigurationOptions' (returns SOAP_OK or error code)
int PTZBindingService::GetConfigurationOptions(_tptz__GetConfigurationOptions *tptz__GetConfigurationOptions, _tptz__GetConfigurationOptionsResponse *tptz__GetConfigurationOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'GotoHomePosition' (returns SOAP_OK or error code)
int PTZBindingService::GotoHomePosition(_tptz__GotoHomePosition *tptz__GotoHomePosition, _tptz__GotoHomePositionResponse *tptz__GotoHomePositionResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	int ret = SOAP_FAULT;		
	auto it = ctx->m_devices.find(tptz__GotoHomePosition->ProfileToken);
	if (it != ctx->m_devices.end())
	{	
		ctx->setCtrlValue(it->first, V4L2_CID_PAN_RESET, 1);
		ctx->setCtrlValue(it->first, V4L2_CID_TILT_RESET, 1);
		ret = SOAP_OK;	
	}
	
	return ret;
}

/// Web service operation 'SetHomePosition' (returns SOAP_OK or error code)
int PTZBindingService::SetHomePosition(_tptz__SetHomePosition *tptz__SetHomePosition, _tptz__SetHomePositionResponse *tptz__SetHomePositionResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'ContinuousMove' (returns SOAP_OK or error code)
int PTZBindingService::ContinuousMove(_tptz__ContinuousMove *tptz__ContinuousMove, _tptz__ContinuousMoveResponse *tptz__ContinuousMoveResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'RelativeMove' (returns SOAP_OK or error code)
int PTZBindingService::RelativeMove(_tptz__RelativeMove *tptz__RelativeMove, _tptz__RelativeMoveResponse *tptz__RelativeMoveResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	int ret = SOAP_FAULT;		
	auto it = ctx->m_devices.find(tptz__RelativeMove->ProfileToken);
	if (it != ctx->m_devices.end())
	{	
		ctx->setCtrlValue(it->first, V4L2_CID_PAN_RELATIVE , tptz__RelativeMove->Translation->PanTilt->x);
		ctx->setCtrlValue(it->first, V4L2_CID_TILT_RELATIVE, tptz__RelativeMove->Translation->PanTilt->y);
		ctx->setCtrlValue(it->first, V4L2_CID_ZOOM_RELATIVE, tptz__RelativeMove->Translation->Zoom->x);
		ret = SOAP_OK;	
	}
	
	return ret;
}

/// Web service operation 'SendAuxiliaryCommand' (returns SOAP_OK or error code)
int PTZBindingService::SendAuxiliaryCommand(_tptz__SendAuxiliaryCommand *tptz__SendAuxiliaryCommand, _tptz__SendAuxiliaryCommandResponse *tptz__SendAuxiliaryCommandResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'AbsoluteMove' (returns SOAP_OK or error code)
int PTZBindingService::AbsoluteMove(_tptz__AbsoluteMove *tptz__AbsoluteMove, _tptz__AbsoluteMoveResponse *tptz__AbsoluteMoveResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;

	int ret = SOAP_FAULT;		
	auto it = ctx->m_devices.find(tptz__AbsoluteMove->ProfileToken);
	if (it != ctx->m_devices.end())
	{	
		ctx->setCtrlValue(it->first, V4L2_CID_PAN_ABSOLUTE , tptz__AbsoluteMove->Position->PanTilt->x);
		ctx->setCtrlValue(it->first, V4L2_CID_TILT_ABSOLUTE, tptz__AbsoluteMove->Position->PanTilt->y);
		ctx->setCtrlValue(it->first, V4L2_CID_ZOOM_ABSOLUTE, tptz__AbsoluteMove->Position->Zoom->x);
		ret = SOAP_OK;	
	}
	
	return ret;
}

/// Web service operation 'Stop' (returns SOAP_OK or error code)
int PTZBindingService::Stop(_tptz__Stop *tptz__Stop, _tptz__StopResponse *tptz__StopResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'GetPresetTours' (returns SOAP_OK or error code)
int PTZBindingService::GetPresetTours(_tptz__GetPresetTours *tptz__GetPresetTours, _tptz__GetPresetToursResponse *tptz__GetPresetToursResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'GetPresetTour' (returns SOAP_OK or error code)
int PTZBindingService::GetPresetTour(_tptz__GetPresetTour *tptz__GetPresetTour, _tptz__GetPresetTourResponse *tptz__GetPresetTourResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'GetPresetTourOptions' (returns SOAP_OK or error code)
int PTZBindingService::GetPresetTourOptions(_tptz__GetPresetTourOptions *tptz__GetPresetTourOptions, _tptz__GetPresetTourOptionsResponse *tptz__GetPresetTourOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'CreatePresetTour' (returns SOAP_OK or error code)
int PTZBindingService::CreatePresetTour(_tptz__CreatePresetTour *tptz__CreatePresetTour, _tptz__CreatePresetTourResponse *tptz__CreatePresetTourResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'ModifyPresetTour' (returns SOAP_OK or error code)
int PTZBindingService::ModifyPresetTour(_tptz__ModifyPresetTour *tptz__ModifyPresetTour, _tptz__ModifyPresetTourResponse *tptz__ModifyPresetTourResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'OperatePresetTour' (returns SOAP_OK or error code)
int PTZBindingService::OperatePresetTour(_tptz__OperatePresetTour *tptz__OperatePresetTour, _tptz__OperatePresetTourResponse *tptz__OperatePresetTourResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'RemovePresetTour' (returns SOAP_OK or error code)
int PTZBindingService::RemovePresetTour(_tptz__RemovePresetTour *tptz__RemovePresetTour, _tptz__RemovePresetTourResponse *tptz__RemovePresetTourResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

/// Web service operation 'GetCompatibleConfigurations' (returns SOAP_OK or error code)
int PTZBindingService::GetCompatibleConfigurations(_tptz__GetCompatibleConfigurations *tptz__GetCompatibleConfigurations, _tptz__GetCompatibleConfigurationsResponse *tptz__GetCompatibleConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

