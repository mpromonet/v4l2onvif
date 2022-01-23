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
 serverDeviceIO.cpp
 
 deviceio.wsdl server
----------------------------------------------------------------------------- */

#include "soapDeviceIOBindingService.h"
#include "onvif_impl.h"

int DeviceIOBindingService::GetServiceCapabilities(_tmd__GetServiceCapabilities *tmd__GetServiceCapabilities, _tmd__GetServiceCapabilitiesResponse &tmd__GetServiceCapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	tmd__GetServiceCapabilitiesResponse.Capabilities = ctx->getDeviceIOServiceCapabilities(this->soap);	
	return SOAP_OK;
}


int DeviceIOBindingService::GetRelayOutputOptions(_tmd__GetRelayOutputOptions *tmd__GetRelayOutputOptions, _tmd__GetRelayOutputOptionsResponse &tmd__GetRelayOutputOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::GetAudioSources(tmd__Get *tmd__GetAudioSources, tmd__GetResponse &tmd__GetAudioSourcesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::GetAudioOutputs(tmd__Get *tmd__GetAudioOutputs, tmd__GetResponse &tmd__GetAudioOutputsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::GetVideoSources(tmd__Get *tmd__GetVideoSources, tmd__GetResponse &tmd__GetVideoSourcesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	for (auto it: ctx->m_devices) 
	{
		tmd__GetVideoSourcesResponse.Token.push_back(it.first);
	}
	
	return SOAP_OK;
}


int DeviceIOBindingService::GetVideoOutputs(_tmd__GetVideoOutputs *tmd__GetVideoOutputs, _tmd__GetVideoOutputsResponse &tmd__GetVideoOutputsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	tmd__GetVideoOutputsResponse.VideoOutputs.push_back(soap_new_tt__VideoOutput(this->soap));
	tmd__GetVideoOutputsResponse.VideoOutputs.back()->token = ctx->m_outdevice;	
	
	return SOAP_OK;
}


int DeviceIOBindingService::GetVideoSourceConfiguration(_tmd__GetVideoSourceConfiguration *tmd__GetVideoSourceConfiguration, _tmd__GetVideoSourceConfigurationResponse &tmd__GetVideoSourceConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	auto it = ctx->m_devices.find(tmd__GetVideoSourceConfiguration->VideoSourceToken);
	if (it != ctx->m_devices.end())
	{
		tmd__GetVideoSourceConfigurationResponse.VideoSourceConfiguration = ctx->getVideoSourceCfg(this->soap, it->first);
	}
	
	return SOAP_OK;
}


int DeviceIOBindingService::GetVideoOutputConfiguration(_tmd__GetVideoOutputConfiguration *tmd__GetVideoOutputConfiguration, _tmd__GetVideoOutputConfigurationResponse &tmd__GetVideoOutputConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::GetAudioSourceConfiguration(_tmd__GetAudioSourceConfiguration *tmd__GetAudioSourceConfiguration, _tmd__GetAudioSourceConfigurationResponse &tmd__GetAudioSourceConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::GetAudioOutputConfiguration(_tmd__GetAudioOutputConfiguration *tmd__GetAudioOutputConfiguration, _tmd__GetAudioOutputConfigurationResponse &tmd__GetAudioOutputConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::SetVideoSourceConfiguration(_tmd__SetVideoSourceConfiguration *tmd__SetVideoSourceConfiguration, _tmd__SetVideoSourceConfigurationResponse &tmd__SetVideoSourceConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::SetVideoOutputConfiguration(_tmd__SetVideoOutputConfiguration *tmd__SetVideoOutputConfiguration, _tmd__SetVideoOutputConfigurationResponse &tmd__SetVideoOutputConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::SetAudioSourceConfiguration(_tmd__SetAudioSourceConfiguration *tmd__SetAudioSourceConfiguration, _tmd__SetAudioSourceConfigurationResponse &tmd__SetAudioSourceConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::SetAudioOutputConfiguration(_tmd__SetAudioOutputConfiguration *tmd__SetAudioOutputConfiguration, _tmd__SetAudioOutputConfigurationResponse &tmd__SetAudioOutputConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::GetVideoSourceConfigurationOptions(_tmd__GetVideoSourceConfigurationOptions *tmd__GetVideoSourceConfigurationOptions, _tmd__GetVideoSourceConfigurationOptionsResponse &tmd__GetVideoSourceConfigurationOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::GetVideoOutputConfigurationOptions(_tmd__GetVideoOutputConfigurationOptions *tmd__GetVideoOutputConfigurationOptions, _tmd__GetVideoOutputConfigurationOptionsResponse &tmd__GetVideoOutputConfigurationOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::GetAudioSourceConfigurationOptions(_tmd__GetAudioSourceConfigurationOptions *tmd__GetAudioSourceConfigurationOptions, _tmd__GetAudioSourceConfigurationOptionsResponse &tmd__GetAudioSourceConfigurationOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::GetAudioOutputConfigurationOptions(_tmd__GetAudioOutputConfigurationOptions *tmd__GetAudioOutputConfigurationOptions, _tmd__GetAudioOutputConfigurationOptionsResponse &tmd__GetAudioOutputConfigurationOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::GetRelayOutputs(_tds__GetRelayOutputs *tds__GetRelayOutputs, _tds__GetRelayOutputsResponse &tds__GetRelayOutputsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::SetRelayOutputSettings(_tmd__SetRelayOutputSettings *tmd__SetRelayOutputSettings, _tmd__SetRelayOutputSettingsResponse &tmd__SetRelayOutputSettingsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::SetRelayOutputState(_tds__SetRelayOutputState *tds__SetRelayOutputState, _tds__SetRelayOutputStateResponse &tds__SetRelayOutputStateResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::GetDigitalInputs(_tmd__GetDigitalInputs *tmd__GetDigitalInputs, _tmd__GetDigitalInputsResponse &tmd__GetDigitalInputsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::GetDigitalInputConfigurationOptions(_tmd__GetDigitalInputConfigurationOptions *tmd__GetDigitalInputConfigurationOptions, _tmd__GetDigitalInputConfigurationOptionsResponse &tmd__GetDigitalInputConfigurationOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::SetDigitalInputConfigurations(_tmd__SetDigitalInputConfigurations *tmd__SetDigitalInputConfigurations, _tmd__SetDigitalInputConfigurationsResponse &tmd__SetDigitalInputConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::GetSerialPorts(_tmd__GetSerialPorts *tmd__GetSerialPorts, _tmd__GetSerialPortsResponse &tmd__GetSerialPortsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::GetSerialPortConfiguration(_tmd__GetSerialPortConfiguration *tmd__GetSerialPortConfiguration, _tmd__GetSerialPortConfigurationResponse &tmd__GetSerialPortConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::SetSerialPortConfiguration(_tmd__SetSerialPortConfiguration *tmd__SetSerialPortConfiguration, _tmd__SetSerialPortConfigurationResponse &tmd__SetSerialPortConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::GetSerialPortConfigurationOptions(_tmd__GetSerialPortConfigurationOptions *tmd__GetSerialPortConfigurationOptions, _tmd__GetSerialPortConfigurationOptionsResponse &tmd__GetSerialPortConfigurationOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


int DeviceIOBindingService::SendReceiveSerialCommand(_tmd__SendReceiveSerialCommand *tmd__SendReceiveSerialCommand, _tmd__SendReceiveSerialCommandResponse &tmd__SendReceiveSerialCommandResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}
