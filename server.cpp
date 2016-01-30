/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** server.cpp
** 
** devicemgmt.wsdl server
**
** -------------------------------------------------------------------------*/

#include <thread>

#include "DeviceBinding.nsmap"
#include "soapDeviceBindingService.h"
#include "soapMediaBindingService.h"

int DeviceBindingService::GetServices(_tds__GetServices *tds__GetServices, _tds__GetServicesResponse &tds__GetServicesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetServiceCapabilities(_tds__GetServiceCapabilities *tds__GetServiceCapabilities, _tds__GetServiceCapabilitiesResponse &tds__GetServiceCapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetDeviceInformation(_tds__GetDeviceInformation *tds__GetDeviceInformation, _tds__GetDeviceInformationResponse &tds__GetDeviceInformationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	tds__GetDeviceInformationResponse.Manufacturer = "Manufacturer";
	return SOAP_OK;
}

int DeviceBindingService::SetSystemDateAndTime(_tds__SetSystemDateAndTime *tds__SetSystemDateAndTime, _tds__SetSystemDateAndTimeResponse &tds__SetSystemDateAndTimeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetSystemDateAndTime(_tds__GetSystemDateAndTime *tds__GetSystemDateAndTime, _tds__GetSystemDateAndTimeResponse &tds__GetSystemDateAndTimeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetSystemFactoryDefault(_tds__SetSystemFactoryDefault *tds__SetSystemFactoryDefault, _tds__SetSystemFactoryDefaultResponse &tds__SetSystemFactoryDefaultResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::UpgradeSystemFirmware(_tds__UpgradeSystemFirmware *tds__UpgradeSystemFirmware, _tds__UpgradeSystemFirmwareResponse &tds__UpgradeSystemFirmwareResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SystemReboot(_tds__SystemReboot *tds__SystemReboot, _tds__SystemRebootResponse &tds__SystemRebootResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::RestoreSystem(_tds__RestoreSystem *tds__RestoreSystem, _tds__RestoreSystemResponse &tds__RestoreSystemResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetSystemBackup(_tds__GetSystemBackup *tds__GetSystemBackup, _tds__GetSystemBackupResponse &tds__GetSystemBackupResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetSystemLog(_tds__GetSystemLog *tds__GetSystemLog, _tds__GetSystemLogResponse &tds__GetSystemLogResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetSystemSupportInformation(_tds__GetSystemSupportInformation *tds__GetSystemSupportInformation, _tds__GetSystemSupportInformationResponse &tds__GetSystemSupportInformationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetScopes(_tds__GetScopes *tds__GetScopes, _tds__GetScopesResponse &tds__GetScopesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetScopes(_tds__SetScopes *tds__SetScopes, _tds__SetScopesResponse &tds__SetScopesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::AddScopes(_tds__AddScopes *tds__AddScopes, _tds__AddScopesResponse &tds__AddScopesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::RemoveScopes(_tds__RemoveScopes *tds__RemoveScopes, _tds__RemoveScopesResponse &tds__RemoveScopesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetDiscoveryMode(_tds__GetDiscoveryMode *tds__GetDiscoveryMode, _tds__GetDiscoveryModeResponse &tds__GetDiscoveryModeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetDiscoveryMode(_tds__SetDiscoveryMode *tds__SetDiscoveryMode, _tds__SetDiscoveryModeResponse &tds__SetDiscoveryModeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetRemoteDiscoveryMode(_tds__GetRemoteDiscoveryMode *tds__GetRemoteDiscoveryMode, _tds__GetRemoteDiscoveryModeResponse &tds__GetRemoteDiscoveryModeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetRemoteDiscoveryMode(_tds__SetRemoteDiscoveryMode *tds__SetRemoteDiscoveryMode, _tds__SetRemoteDiscoveryModeResponse &tds__SetRemoteDiscoveryModeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetDPAddresses(_tds__GetDPAddresses *tds__GetDPAddresses, _tds__GetDPAddressesResponse &tds__GetDPAddressesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetEndpointReference(_tds__GetEndpointReference *tds__GetEndpointReference, _tds__GetEndpointReferenceResponse &tds__GetEndpointReferenceResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetRemoteUser(_tds__GetRemoteUser *tds__GetRemoteUser, _tds__GetRemoteUserResponse &tds__GetRemoteUserResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetRemoteUser(_tds__SetRemoteUser *tds__SetRemoteUser, _tds__SetRemoteUserResponse &tds__SetRemoteUserResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetUsers(_tds__GetUsers *tds__GetUsers, _tds__GetUsersResponse &tds__GetUsersResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::CreateUsers(_tds__CreateUsers *tds__CreateUsers, _tds__CreateUsersResponse &tds__CreateUsersResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::DeleteUsers(_tds__DeleteUsers *tds__DeleteUsers, _tds__DeleteUsersResponse &tds__DeleteUsersResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetUser(_tds__SetUser *tds__SetUser, _tds__SetUserResponse &tds__SetUserResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetWsdlUrl(_tds__GetWsdlUrl *tds__GetWsdlUrl, _tds__GetWsdlUrlResponse &tds__GetWsdlUrlResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetCapabilities(_tds__GetCapabilities *tds__GetCapabilities, _tds__GetCapabilitiesResponse &tds__GetCapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	tds__GetCapabilitiesResponse.Capabilities = soap_new_tt__Capabilities(this);
	tds__GetCapabilitiesResponse.Capabilities->Device = soap_new_tt__DeviceCapabilities(this);
	return SOAP_OK;
}

int DeviceBindingService::SetDPAddresses(_tds__SetDPAddresses *tds__SetDPAddresses, _tds__SetDPAddressesResponse &tds__SetDPAddressesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetHostname(_tds__GetHostname *tds__GetHostname, _tds__GetHostnameResponse &tds__GetHostnameResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetHostname(_tds__SetHostname *tds__SetHostname, _tds__SetHostnameResponse &tds__SetHostnameResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetHostnameFromDHCP(_tds__SetHostnameFromDHCP *tds__SetHostnameFromDHCP, _tds__SetHostnameFromDHCPResponse &tds__SetHostnameFromDHCPResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetDNS(_tds__GetDNS *tds__GetDNS, _tds__GetDNSResponse &tds__GetDNSResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetDNS(_tds__SetDNS *tds__SetDNS, _tds__SetDNSResponse &tds__SetDNSResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetNTP(_tds__GetNTP *tds__GetNTP, _tds__GetNTPResponse &tds__GetNTPResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetNTP(_tds__SetNTP *tds__SetNTP, _tds__SetNTPResponse &tds__SetNTPResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetDynamicDNS(_tds__GetDynamicDNS *tds__GetDynamicDNS, _tds__GetDynamicDNSResponse &tds__GetDynamicDNSResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetDynamicDNS(_tds__SetDynamicDNS *tds__SetDynamicDNS, _tds__SetDynamicDNSResponse &tds__SetDynamicDNSResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetNetworkInterfaces(_tds__GetNetworkInterfaces *tds__GetNetworkInterfaces, _tds__GetNetworkInterfacesResponse &tds__GetNetworkInterfacesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetNetworkInterfaces(_tds__SetNetworkInterfaces *tds__SetNetworkInterfaces, _tds__SetNetworkInterfacesResponse &tds__SetNetworkInterfacesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetNetworkProtocols(_tds__GetNetworkProtocols *tds__GetNetworkProtocols, _tds__GetNetworkProtocolsResponse &tds__GetNetworkProtocolsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetNetworkProtocols(_tds__SetNetworkProtocols *tds__SetNetworkProtocols, _tds__SetNetworkProtocolsResponse &tds__SetNetworkProtocolsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetNetworkDefaultGateway(_tds__GetNetworkDefaultGateway *tds__GetNetworkDefaultGateway, _tds__GetNetworkDefaultGatewayResponse &tds__GetNetworkDefaultGatewayResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetNetworkDefaultGateway(_tds__SetNetworkDefaultGateway *tds__SetNetworkDefaultGateway, _tds__SetNetworkDefaultGatewayResponse &tds__SetNetworkDefaultGatewayResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetZeroConfiguration(_tds__GetZeroConfiguration *tds__GetZeroConfiguration, _tds__GetZeroConfigurationResponse &tds__GetZeroConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetZeroConfiguration(_tds__SetZeroConfiguration *tds__SetZeroConfiguration, _tds__SetZeroConfigurationResponse &tds__SetZeroConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetIPAddressFilter(_tds__GetIPAddressFilter *tds__GetIPAddressFilter, _tds__GetIPAddressFilterResponse &tds__GetIPAddressFilterResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetIPAddressFilter(_tds__SetIPAddressFilter *tds__SetIPAddressFilter, _tds__SetIPAddressFilterResponse &tds__SetIPAddressFilterResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::AddIPAddressFilter(_tds__AddIPAddressFilter *tds__AddIPAddressFilter, _tds__AddIPAddressFilterResponse &tds__AddIPAddressFilterResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::RemoveIPAddressFilter(_tds__RemoveIPAddressFilter *tds__RemoveIPAddressFilter, _tds__RemoveIPAddressFilterResponse &tds__RemoveIPAddressFilterResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetAccessPolicy(_tds__GetAccessPolicy *tds__GetAccessPolicy, _tds__GetAccessPolicyResponse &tds__GetAccessPolicyResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetAccessPolicy(_tds__SetAccessPolicy *tds__SetAccessPolicy, _tds__SetAccessPolicyResponse &tds__SetAccessPolicyResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::CreateCertificate(_tds__CreateCertificate *tds__CreateCertificate, _tds__CreateCertificateResponse &tds__CreateCertificateResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetCertificates(_tds__GetCertificates *tds__GetCertificates, _tds__GetCertificatesResponse &tds__GetCertificatesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetCertificatesStatus(_tds__GetCertificatesStatus *tds__GetCertificatesStatus, _tds__GetCertificatesStatusResponse &tds__GetCertificatesStatusResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetCertificatesStatus(_tds__SetCertificatesStatus *tds__SetCertificatesStatus, _tds__SetCertificatesStatusResponse &tds__SetCertificatesStatusResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::DeleteCertificates(_tds__DeleteCertificates *tds__DeleteCertificates, _tds__DeleteCertificatesResponse &tds__DeleteCertificatesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetPkcs10Request(_tds__GetPkcs10Request *tds__GetPkcs10Request, _tds__GetPkcs10RequestResponse &tds__GetPkcs10RequestResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::LoadCertificates(_tds__LoadCertificates *tds__LoadCertificates, _tds__LoadCertificatesResponse &tds__LoadCertificatesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetClientCertificateMode(_tds__GetClientCertificateMode *tds__GetClientCertificateMode, _tds__GetClientCertificateModeResponse &tds__GetClientCertificateModeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetClientCertificateMode(_tds__SetClientCertificateMode *tds__SetClientCertificateMode, _tds__SetClientCertificateModeResponse &tds__SetClientCertificateModeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetRelayOutputs(_tds__GetRelayOutputs *tds__GetRelayOutputs, _tds__GetRelayOutputsResponse &tds__GetRelayOutputsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetRelayOutputSettings(_tds__SetRelayOutputSettings *tds__SetRelayOutputSettings, _tds__SetRelayOutputSettingsResponse &tds__SetRelayOutputSettingsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetRelayOutputState(_tds__SetRelayOutputState *tds__SetRelayOutputState, _tds__SetRelayOutputStateResponse &tds__SetRelayOutputStateResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SendAuxiliaryCommand(_tds__SendAuxiliaryCommand *tds__SendAuxiliaryCommand, _tds__SendAuxiliaryCommandResponse &tds__SendAuxiliaryCommandResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetCACertificates(_tds__GetCACertificates *tds__GetCACertificates, _tds__GetCACertificatesResponse &tds__GetCACertificatesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::LoadCertificateWithPrivateKey(_tds__LoadCertificateWithPrivateKey *tds__LoadCertificateWithPrivateKey, _tds__LoadCertificateWithPrivateKeyResponse &tds__LoadCertificateWithPrivateKeyResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetCertificateInformation(_tds__GetCertificateInformation *tds__GetCertificateInformation, _tds__GetCertificateInformationResponse &tds__GetCertificateInformationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::LoadCACertificates(_tds__LoadCACertificates *tds__LoadCACertificates, _tds__LoadCACertificatesResponse &tds__LoadCACertificatesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::CreateDot1XConfiguration(_tds__CreateDot1XConfiguration *tds__CreateDot1XConfiguration, _tds__CreateDot1XConfigurationResponse &tds__CreateDot1XConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetDot1XConfiguration(_tds__SetDot1XConfiguration *tds__SetDot1XConfiguration, _tds__SetDot1XConfigurationResponse &tds__SetDot1XConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetDot1XConfiguration(_tds__GetDot1XConfiguration *tds__GetDot1XConfiguration, _tds__GetDot1XConfigurationResponse &tds__GetDot1XConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetDot1XConfigurations(_tds__GetDot1XConfigurations *tds__GetDot1XConfigurations, _tds__GetDot1XConfigurationsResponse &tds__GetDot1XConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::DeleteDot1XConfiguration(_tds__DeleteDot1XConfiguration *tds__DeleteDot1XConfiguration, _tds__DeleteDot1XConfigurationResponse &tds__DeleteDot1XConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetDot11Capabilities(_tds__GetDot11Capabilities *tds__GetDot11Capabilities, _tds__GetDot11CapabilitiesResponse &tds__GetDot11CapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetDot11Status(_tds__GetDot11Status *tds__GetDot11Status, _tds__GetDot11StatusResponse &tds__GetDot11StatusResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::ScanAvailableDot11Networks(_tds__ScanAvailableDot11Networks *tds__ScanAvailableDot11Networks, _tds__ScanAvailableDot11NetworksResponse &tds__ScanAvailableDot11NetworksResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetSystemUris(_tds__GetSystemUris *tds__GetSystemUris, _tds__GetSystemUrisResponse &tds__GetSystemUrisResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::StartFirmwareUpgrade(_tds__StartFirmwareUpgrade *tds__StartFirmwareUpgrade, _tds__StartFirmwareUpgradeResponse &tds__StartFirmwareUpgradeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::StartSystemRestore(_tds__StartSystemRestore *tds__StartSystemRestore, _tds__StartSystemRestoreResponse &tds__StartSystemRestoreResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetStorageConfigurations(_tds__GetStorageConfigurations *tds__GetStorageConfigurations, _tds__GetStorageConfigurationsResponse &tds__GetStorageConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::CreateStorageConfiguration(_tds__CreateStorageConfiguration *tds__CreateStorageConfiguration, _tds__CreateStorageConfigurationResponse &tds__CreateStorageConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetStorageConfiguration(_tds__GetStorageConfiguration *tds__GetStorageConfiguration, _tds__GetStorageConfigurationResponse &tds__GetStorageConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetStorageConfiguration(_tds__SetStorageConfiguration *tds__SetStorageConfiguration, _tds__SetStorageConfigurationResponse &tds__SetStorageConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::DeleteStorageConfiguration(_tds__DeleteStorageConfiguration *tds__DeleteStorageConfiguration, _tds__DeleteStorageConfigurationResponse &tds__DeleteStorageConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

// ======================================= MediaBindingService
int MediaBindingService::GetServiceCapabilities(_trt__GetServiceCapabilities *trt__GetServiceCapabilities, _trt__GetServiceCapabilitiesResponse &trt__GetServiceCapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetVideoSources(_trt__GetVideoSources *trt__GetVideoSources, _trt__GetVideoSourcesResponse &trt__GetVideoSourcesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetAudioSources(_trt__GetAudioSources *trt__GetAudioSources, _trt__GetAudioSourcesResponse &trt__GetAudioSourcesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetAudioOutputs(_trt__GetAudioOutputs *trt__GetAudioOutputs, _trt__GetAudioOutputsResponse &trt__GetAudioOutputsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::CreateProfile(_trt__CreateProfile *trt__CreateProfile, _trt__CreateProfileResponse &trt__CreateProfileResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetProfile(_trt__GetProfile *trt__GetProfile, _trt__GetProfileResponse &trt__GetProfileResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetProfiles(_trt__GetProfiles *trt__GetProfiles, _trt__GetProfilesResponse &trt__GetProfilesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::AddVideoEncoderConfiguration(_trt__AddVideoEncoderConfiguration *trt__AddVideoEncoderConfiguration, _trt__AddVideoEncoderConfigurationResponse &trt__AddVideoEncoderConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::AddVideoSourceConfiguration(_trt__AddVideoSourceConfiguration *trt__AddVideoSourceConfiguration, _trt__AddVideoSourceConfigurationResponse &trt__AddVideoSourceConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::AddAudioEncoderConfiguration(_trt__AddAudioEncoderConfiguration *trt__AddAudioEncoderConfiguration, _trt__AddAudioEncoderConfigurationResponse &trt__AddAudioEncoderConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::AddAudioSourceConfiguration(_trt__AddAudioSourceConfiguration *trt__AddAudioSourceConfiguration, _trt__AddAudioSourceConfigurationResponse &trt__AddAudioSourceConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::AddPTZConfiguration(_trt__AddPTZConfiguration *trt__AddPTZConfiguration, _trt__AddPTZConfigurationResponse &trt__AddPTZConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::AddVideoAnalyticsConfiguration(_trt__AddVideoAnalyticsConfiguration *trt__AddVideoAnalyticsConfiguration, _trt__AddVideoAnalyticsConfigurationResponse &trt__AddVideoAnalyticsConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::AddMetadataConfiguration(_trt__AddMetadataConfiguration *trt__AddMetadataConfiguration, _trt__AddMetadataConfigurationResponse &trt__AddMetadataConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::AddAudioOutputConfiguration(_trt__AddAudioOutputConfiguration *trt__AddAudioOutputConfiguration, _trt__AddAudioOutputConfigurationResponse &trt__AddAudioOutputConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::AddAudioDecoderConfiguration(_trt__AddAudioDecoderConfiguration *trt__AddAudioDecoderConfiguration, _trt__AddAudioDecoderConfigurationResponse &trt__AddAudioDecoderConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::RemoveVideoEncoderConfiguration(_trt__RemoveVideoEncoderConfiguration *trt__RemoveVideoEncoderConfiguration, _trt__RemoveVideoEncoderConfigurationResponse &trt__RemoveVideoEncoderConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::RemoveVideoSourceConfiguration(_trt__RemoveVideoSourceConfiguration *trt__RemoveVideoSourceConfiguration, _trt__RemoveVideoSourceConfigurationResponse &trt__RemoveVideoSourceConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::RemoveAudioEncoderConfiguration(_trt__RemoveAudioEncoderConfiguration *trt__RemoveAudioEncoderConfiguration, _trt__RemoveAudioEncoderConfigurationResponse &trt__RemoveAudioEncoderConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::RemoveAudioSourceConfiguration(_trt__RemoveAudioSourceConfiguration *trt__RemoveAudioSourceConfiguration, _trt__RemoveAudioSourceConfigurationResponse &trt__RemoveAudioSourceConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::RemovePTZConfiguration(_trt__RemovePTZConfiguration *trt__RemovePTZConfiguration, _trt__RemovePTZConfigurationResponse &trt__RemovePTZConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::RemoveVideoAnalyticsConfiguration(_trt__RemoveVideoAnalyticsConfiguration *trt__RemoveVideoAnalyticsConfiguration, _trt__RemoveVideoAnalyticsConfigurationResponse &trt__RemoveVideoAnalyticsConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::RemoveMetadataConfiguration(_trt__RemoveMetadataConfiguration *trt__RemoveMetadataConfiguration, _trt__RemoveMetadataConfigurationResponse &trt__RemoveMetadataConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::RemoveAudioOutputConfiguration(_trt__RemoveAudioOutputConfiguration *trt__RemoveAudioOutputConfiguration, _trt__RemoveAudioOutputConfigurationResponse &trt__RemoveAudioOutputConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::RemoveAudioDecoderConfiguration(_trt__RemoveAudioDecoderConfiguration *trt__RemoveAudioDecoderConfiguration, _trt__RemoveAudioDecoderConfigurationResponse &trt__RemoveAudioDecoderConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


	/// Web service operation 'DeleteProfile' (returns error code or SOAP_OK)
int MediaBindingService::DeleteProfile(_trt__DeleteProfile *trt__DeleteProfile, _trt__DeleteProfileResponse &trt__DeleteProfileResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


	/// Web service operation 'GetVideoSourceConfigurations' (returns error code or SOAP_OK)
int MediaBindingService::GetVideoSourceConfigurations(_trt__GetVideoSourceConfigurations *trt__GetVideoSourceConfigurations, _trt__GetVideoSourceConfigurationsResponse &trt__GetVideoSourceConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


	/// Web service operation 'GetVideoEncoderConfigurations' (returns error code or SOAP_OK)
int MediaBindingService::GetVideoEncoderConfigurations(_trt__GetVideoEncoderConfigurations *trt__GetVideoEncoderConfigurations, _trt__GetVideoEncoderConfigurationsResponse &trt__GetVideoEncoderConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


	/// Web service operation 'GetAudioSourceConfigurations' (returns error code or SOAP_OK)
int MediaBindingService::GetAudioSourceConfigurations(_trt__GetAudioSourceConfigurations *trt__GetAudioSourceConfigurations, _trt__GetAudioSourceConfigurationsResponse &trt__GetAudioSourceConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


	/// Web service operation 'GetAudioEncoderConfigurations' (returns error code or SOAP_OK)
int MediaBindingService::GetAudioEncoderConfigurations(_trt__GetAudioEncoderConfigurations *trt__GetAudioEncoderConfigurations, _trt__GetAudioEncoderConfigurationsResponse &trt__GetAudioEncoderConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


	/// Web service operation 'GetVideoAnalyticsConfigurations' (returns error code or SOAP_OK)
int MediaBindingService::GetVideoAnalyticsConfigurations(_trt__GetVideoAnalyticsConfigurations *trt__GetVideoAnalyticsConfigurations, _trt__GetVideoAnalyticsConfigurationsResponse &trt__GetVideoAnalyticsConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


	/// Web service operation 'GetMetadataConfigurations' (returns error code or SOAP_OK)
int MediaBindingService::GetMetadataConfigurations(_trt__GetMetadataConfigurations *trt__GetMetadataConfigurations, _trt__GetMetadataConfigurationsResponse &trt__GetMetadataConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


	/// Web service operation 'GetAudioOutputConfigurations' (returns error code or SOAP_OK)
int MediaBindingService::GetAudioOutputConfigurations(_trt__GetAudioOutputConfigurations *trt__GetAudioOutputConfigurations, _trt__GetAudioOutputConfigurationsResponse &trt__GetAudioOutputConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


	/// Web service operation 'GetAudioDecoderConfigurations' (returns error code or SOAP_OK)
int MediaBindingService::GetAudioDecoderConfigurations(_trt__GetAudioDecoderConfigurations *trt__GetAudioDecoderConfigurations, _trt__GetAudioDecoderConfigurationsResponse &trt__GetAudioDecoderConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


	/// Web service operation 'GetVideoSourceConfiguration' (returns error code or SOAP_OK)
int MediaBindingService::GetVideoSourceConfiguration(_trt__GetVideoSourceConfiguration *trt__GetVideoSourceConfiguration, _trt__GetVideoSourceConfigurationResponse &trt__GetVideoSourceConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


	/// Web service operation 'GetVideoEncoderConfiguration' (returns error code or SOAP_OK)
int MediaBindingService::GetVideoEncoderConfiguration(_trt__GetVideoEncoderConfiguration *trt__GetVideoEncoderConfiguration, _trt__GetVideoEncoderConfigurationResponse &trt__GetVideoEncoderConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


	/// Web service operation 'GetAudioSourceConfiguration' (returns error code or SOAP_OK)
int MediaBindingService::GetAudioSourceConfiguration(_trt__GetAudioSourceConfiguration *trt__GetAudioSourceConfiguration, _trt__GetAudioSourceConfigurationResponse &trt__GetAudioSourceConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


	/// Web service operation 'GetAudioEncoderConfiguration' (returns error code or SOAP_OK)
int MediaBindingService::GetAudioEncoderConfiguration(_trt__GetAudioEncoderConfiguration *trt__GetAudioEncoderConfiguration, _trt__GetAudioEncoderConfigurationResponse &trt__GetAudioEncoderConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


	/// Web service operation 'GetVideoAnalyticsConfiguration' (returns error code or SOAP_OK)
int MediaBindingService::GetVideoAnalyticsConfiguration(_trt__GetVideoAnalyticsConfiguration *trt__GetVideoAnalyticsConfiguration, _trt__GetVideoAnalyticsConfigurationResponse &trt__GetVideoAnalyticsConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


	/// Web service operation 'GetMetadataConfiguration' (returns error code or SOAP_OK)
int MediaBindingService::GetMetadataConfiguration(_trt__GetMetadataConfiguration *trt__GetMetadataConfiguration, _trt__GetMetadataConfigurationResponse &trt__GetMetadataConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetAudioOutputConfiguration(_trt__GetAudioOutputConfiguration *trt__GetAudioOutputConfiguration, _trt__GetAudioOutputConfigurationResponse &trt__GetAudioOutputConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetAudioDecoderConfiguration(_trt__GetAudioDecoderConfiguration *trt__GetAudioDecoderConfiguration, _trt__GetAudioDecoderConfigurationResponse &trt__GetAudioDecoderConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetCompatibleVideoEncoderConfigurations(_trt__GetCompatibleVideoEncoderConfigurations *trt__GetCompatibleVideoEncoderConfigurations, _trt__GetCompatibleVideoEncoderConfigurationsResponse &trt__GetCompatibleVideoEncoderConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetCompatibleVideoSourceConfigurations(_trt__GetCompatibleVideoSourceConfigurations *trt__GetCompatibleVideoSourceConfigurations, _trt__GetCompatibleVideoSourceConfigurationsResponse &trt__GetCompatibleVideoSourceConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetCompatibleAudioEncoderConfigurations(_trt__GetCompatibleAudioEncoderConfigurations *trt__GetCompatibleAudioEncoderConfigurations, _trt__GetCompatibleAudioEncoderConfigurationsResponse &trt__GetCompatibleAudioEncoderConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetCompatibleAudioSourceConfigurations(_trt__GetCompatibleAudioSourceConfigurations *trt__GetCompatibleAudioSourceConfigurations, _trt__GetCompatibleAudioSourceConfigurationsResponse &trt__GetCompatibleAudioSourceConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetCompatibleVideoAnalyticsConfigurations(_trt__GetCompatibleVideoAnalyticsConfigurations *trt__GetCompatibleVideoAnalyticsConfigurations, _trt__GetCompatibleVideoAnalyticsConfigurationsResponse &trt__GetCompatibleVideoAnalyticsConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetCompatibleMetadataConfigurations(_trt__GetCompatibleMetadataConfigurations *trt__GetCompatibleMetadataConfigurations, _trt__GetCompatibleMetadataConfigurationsResponse &trt__GetCompatibleMetadataConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetCompatibleAudioOutputConfigurations(_trt__GetCompatibleAudioOutputConfigurations *trt__GetCompatibleAudioOutputConfigurations, _trt__GetCompatibleAudioOutputConfigurationsResponse &trt__GetCompatibleAudioOutputConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetCompatibleAudioDecoderConfigurations(_trt__GetCompatibleAudioDecoderConfigurations *trt__GetCompatibleAudioDecoderConfigurations, _trt__GetCompatibleAudioDecoderConfigurationsResponse &trt__GetCompatibleAudioDecoderConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::SetVideoSourceConfiguration(_trt__SetVideoSourceConfiguration *trt__SetVideoSourceConfiguration, _trt__SetVideoSourceConfigurationResponse &trt__SetVideoSourceConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::SetVideoEncoderConfiguration(_trt__SetVideoEncoderConfiguration *trt__SetVideoEncoderConfiguration, _trt__SetVideoEncoderConfigurationResponse &trt__SetVideoEncoderConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::SetAudioSourceConfiguration(_trt__SetAudioSourceConfiguration *trt__SetAudioSourceConfiguration, _trt__SetAudioSourceConfigurationResponse &trt__SetAudioSourceConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::SetAudioEncoderConfiguration(_trt__SetAudioEncoderConfiguration *trt__SetAudioEncoderConfiguration, _trt__SetAudioEncoderConfigurationResponse &trt__SetAudioEncoderConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::SetVideoAnalyticsConfiguration(_trt__SetVideoAnalyticsConfiguration *trt__SetVideoAnalyticsConfiguration, _trt__SetVideoAnalyticsConfigurationResponse &trt__SetVideoAnalyticsConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::SetMetadataConfiguration(_trt__SetMetadataConfiguration *trt__SetMetadataConfiguration, _trt__SetMetadataConfigurationResponse &trt__SetMetadataConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::SetAudioOutputConfiguration(_trt__SetAudioOutputConfiguration *trt__SetAudioOutputConfiguration, _trt__SetAudioOutputConfigurationResponse &trt__SetAudioOutputConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::SetAudioDecoderConfiguration(_trt__SetAudioDecoderConfiguration *trt__SetAudioDecoderConfiguration, _trt__SetAudioDecoderConfigurationResponse &trt__SetAudioDecoderConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetVideoSourceConfigurationOptions(_trt__GetVideoSourceConfigurationOptions *trt__GetVideoSourceConfigurationOptions, _trt__GetVideoSourceConfigurationOptionsResponse &trt__GetVideoSourceConfigurationOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetVideoEncoderConfigurationOptions(_trt__GetVideoEncoderConfigurationOptions *trt__GetVideoEncoderConfigurationOptions, _trt__GetVideoEncoderConfigurationOptionsResponse &trt__GetVideoEncoderConfigurationOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetAudioSourceConfigurationOptions(_trt__GetAudioSourceConfigurationOptions *trt__GetAudioSourceConfigurationOptions, _trt__GetAudioSourceConfigurationOptionsResponse &trt__GetAudioSourceConfigurationOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetAudioEncoderConfigurationOptions(_trt__GetAudioEncoderConfigurationOptions *trt__GetAudioEncoderConfigurationOptions, _trt__GetAudioEncoderConfigurationOptionsResponse &trt__GetAudioEncoderConfigurationOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetMetadataConfigurationOptions(_trt__GetMetadataConfigurationOptions *trt__GetMetadataConfigurationOptions, _trt__GetMetadataConfigurationOptionsResponse &trt__GetMetadataConfigurationOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetAudioOutputConfigurationOptions(_trt__GetAudioOutputConfigurationOptions *trt__GetAudioOutputConfigurationOptions, _trt__GetAudioOutputConfigurationOptionsResponse &trt__GetAudioOutputConfigurationOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetAudioDecoderConfigurationOptions(_trt__GetAudioDecoderConfigurationOptions *trt__GetAudioDecoderConfigurationOptions, _trt__GetAudioDecoderConfigurationOptionsResponse &trt__GetAudioDecoderConfigurationOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetGuaranteedNumberOfVideoEncoderInstances(_trt__GetGuaranteedNumberOfVideoEncoderInstances *trt__GetGuaranteedNumberOfVideoEncoderInstances, _trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse &trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetStreamUri(_trt__GetStreamUri *trt__GetStreamUri, _trt__GetStreamUriResponse &trt__GetStreamUriResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	trt__GetStreamUriResponse.MediaUri = soap_new_tt__MediaUri(this);
	trt__GetStreamUriResponse.MediaUri->Uri = "rtsp://127.0.0.1/video.264";
	return SOAP_OK;
}

int MediaBindingService::StartMulticastStreaming(_trt__StartMulticastStreaming *trt__StartMulticastStreaming, _trt__StartMulticastStreamingResponse &trt__StartMulticastStreamingResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::StopMulticastStreaming(_trt__StopMulticastStreaming *trt__StopMulticastStreaming, _trt__StopMulticastStreamingResponse &trt__StopMulticastStreamingResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::SetSynchronizationPoint(_trt__SetSynchronizationPoint *trt__SetSynchronizationPoint, _trt__SetSynchronizationPointResponse &trt__SetSynchronizationPointResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetSnapshotUri(_trt__GetSnapshotUri *trt__GetSnapshotUri, _trt__GetSnapshotUriResponse &trt__GetSnapshotUriResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetVideoSourceModes(_trt__GetVideoSourceModes *trt__GetVideoSourceModes, _trt__GetVideoSourceModesResponse &trt__GetVideoSourceModesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::SetVideoSourceMode(_trt__SetVideoSourceMode *trt__SetVideoSourceMode, _trt__SetVideoSourceModeResponse &trt__SetVideoSourceModeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetOSDs(_trt__GetOSDs *trt__GetOSDs, _trt__GetOSDsResponse &trt__GetOSDsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetOSD(_trt__GetOSD *trt__GetOSD, _trt__GetOSDResponse &trt__GetOSDResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::GetOSDOptions(_trt__GetOSDOptions *trt__GetOSDOptions, _trt__GetOSDOptionsResponse &trt__GetOSDOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::SetOSD(_trt__SetOSD *trt__SetOSD, _trt__SetOSDResponse &trt__SetOSDResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::CreateOSD(_trt__CreateOSD *trt__CreateOSD, _trt__CreateOSDResponse &trt__CreateOSDResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int MediaBindingService::DeleteOSD(_trt__DeleteOSD *trt__DeleteOSD, _trt__DeleteOSDResponse &trt__DeleteOSDResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

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
	DeviceBindingService deviceService;
	deviceService.user = (void*)"devicemgmt.wsdl";
	deviceService.fget = http_get; 
	
	MediaBindingService mediaService;
	mediaService.user = (void*)"media.wsdl";
	mediaService.fget = http_get; 
	
	std::thread thread_device (&DeviceBindingService::run, &deviceService, 8080);	
	
	mediaService.run(9090);
	
	thread_device.join();
	
	return 0;
}
