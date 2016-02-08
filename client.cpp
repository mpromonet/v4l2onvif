/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** client.cpp
** 
** onvif client
**
** -------------------------------------------------------------------------*/

#include <memory>
#include "DeviceBinding.nsmap"
#include "soapDeviceBindingProxy.h"
#include "soapMediaBindingProxy.h"
#include "soapRecordingBindingProxy.h"
#include "soapReceiverBindingProxy.h"
#include "soapReplayBindingProxy.h"
#include "soapEventBindingProxy.h"
#include "soapPullPointSubscriptionBindingProxy.h"

#include "wsseapi.h"

int main(int argc, char* argv[])
{
	std::string url = "http://127.0.0.1:8080";
	std::string username = "admin";
	std::string password = "admin";
	if (argc > 1)
	{
		url.assign(argv[1]);
	}
	if (argc > 3)
	{
		username.assign(argv[2]);
		password.assign(argv[3]);
	}
	
	// create connection to devicemgmt.wsdl server
        DeviceBindingProxy deviceProxy(url.c_str());
	soap_wsse_add_Security(deviceProxy.soap);
	soap_wsse_add_UsernameTokenDigest(deviceProxy.soap, "Id", username.c_str() , password.c_str());	
	
	// call Device::GetDeviceInformation
	std::cout << "=>Device::GetDeviceInformation" << std::endl;	
	_tds__GetDeviceInformation         tds__GetDeviceInformation;
	_tds__GetDeviceInformationResponse tds__GetDeviceInformationResponse;
	if (deviceProxy.GetDeviceInformation(&tds__GetDeviceInformation, &tds__GetDeviceInformationResponse) == SOAP_OK)
	{
		std::cout << "Manufacturer:" << tds__GetDeviceInformationResponse.Manufacturer << std::endl;
	}
	else
	{
		deviceProxy.soap_stream_fault(std::cerr);
	}

	// call Device::GetHostname
	std::cout << "=>Device::GetHostname" << std::endl;	
	_tds__GetHostname         tds__GetHostname;
	_tds__GetHostnameResponse tds__GetHostnameResponse;
	if (deviceProxy.GetHostname(&tds__GetHostname, &tds__GetHostnameResponse) == SOAP_OK)
	{
		std::cout << "Hostname:" << tds__GetHostnameResponse.HostnameInformation->Name->c_str() << std::endl;
	}
	else
	{
		deviceProxy.soap_stream_fault(std::cerr);
	}

	// call Device::GetNetworkInterfaces
	std::cout << "=>Device::GetNetworkInterfaces" << std::endl;	
	_tds__GetNetworkInterfaces         tds__GetNetworkInterfaces;
	_tds__GetNetworkInterfacesResponse tds__GetNetworkInterfacesResponse;
	if (deviceProxy.GetNetworkInterfaces(&tds__GetNetworkInterfaces, &tds__GetNetworkInterfacesResponse) == SOAP_OK)
	{
		for (auto iface : tds__GetNetworkInterfacesResponse.NetworkInterfaces)
		{
			if (iface->Info != NULL)
			{
				std::cout << iface->Info->Name->c_str() <<  " MAC:" << iface->Info->HwAddress << std::endl;			
			}
			if ( (iface->IPv4 != NULL) && (iface->IPv4->Config != NULL) )
			{
				for (auto addr : iface->IPv4->Config ->Manual)
				{
					std::cout << "IP:" << addr->Address  << "/" << addr->PrefixLength << std::endl;					
				}
			}
		}
	}
	else
	{
		deviceProxy.soap_stream_fault(std::cerr);
	}
	
	// call Device::GetServices
	std::cout << "=>Device::GetServices" << std::endl;		
	_tds__GetServices         tds__GetServices;
	tds__GetServices.IncludeCapability = true;
	_tds__GetServicesResponse tds__GetServicesResponse;
	if (deviceProxy.GetServices(&tds__GetServices, &tds__GetServicesResponse) == SOAP_OK)
	{
		for (auto service : tds__GetServicesResponse.Service)
		{
			std::cout << service->Namespace << " " << service->XAddr << " " << service->Version->Major << "." << service->Version->Minor << std::endl;
			if (service->Capabilities)
			{
				std::cout << service->Capabilities->__any << std::endl;
			}
		}
	}
	
	// call Device::GetCapabilities
	std::cout << "=>Device::GetCapabilities" << std::endl;		
	_tds__GetCapabilities         tds__GetCapabilities;
	_tds__GetCapabilitiesResponse tds__GetCapabilitiesResponse;
	if (deviceProxy.GetCapabilities(&tds__GetCapabilities, &tds__GetCapabilitiesResponse) == SOAP_OK)
	{
		if (tds__GetCapabilitiesResponse.Capabilities->Media != NULL)
		{
			std::string mediaUrl(tds__GetCapabilitiesResponse.Capabilities->Media->XAddr);
			std::cout << "Media Url:" << mediaUrl << std::endl;
			
			MediaBindingProxy mediaProxy(mediaUrl.c_str());
			
			// call Device::GetProfiles
			std::cout << "=>Device::GetProfiles" << std::endl;					
			_trt__GetProfiles         trt__GetProfiles;
			_trt__GetProfilesResponse trt__GetProfilesResponse;
			if (mediaProxy.GetProfiles(&trt__GetProfiles, &trt__GetProfilesResponse) == SOAP_OK)
			{		
				for (auto profile : trt__GetProfilesResponse.Profiles)
				{
					std::string token(profile->token);
					std::cout << "MediaProfile:" << token << std::endl;
					
					_trt__GetStreamUri         trt__GetStreamUri;
					_trt__GetStreamUriResponse trt__GetStreamUriResponse;
					trt__GetStreamUri.ProfileToken = token;
					if (mediaProxy.GetStreamUri(&trt__GetStreamUri, &trt__GetStreamUriResponse) == SOAP_OK)
					{
						std::cout << "MediaUri:" << trt__GetStreamUriResponse.MediaUri->Uri << std::endl;
					}
					else
					{
						mediaProxy.soap_stream_fault(std::cerr);
					}
				}
			}
			else
			{
				mediaProxy.soap_stream_fault(std::cerr);
			}	
		}	
		if (tds__GetCapabilitiesResponse.Capabilities->Events != NULL)
		{
			std::string eventUrl(tds__GetCapabilitiesResponse.Capabilities->Events->XAddr);
			std::cout << "Event Url:" << eventUrl << std::endl;
			
			EventBindingProxy eventProxy(eventUrl.c_str());
			
			_tev__CreatePullPointSubscription         tev__CreatePullPointSubscription;
			_tev__CreatePullPointSubscriptionResponse tev__CreatePullPointSubscriptionResponse;
			if (eventProxy.CreatePullPointSubscription(&tev__CreatePullPointSubscription, &tev__CreatePullPointSubscriptionResponse) == SOAP_OK)
			{
				std::cout << "Pullpoint Url:" << tev__CreatePullPointSubscriptionResponse.SubscriptionReference.Address << std::endl;
				PullPointSubscriptionBindingProxy pullpoint(tev__CreatePullPointSubscriptionResponse.SubscriptionReference.Address);
				
				_tev__PullMessages         tev__PullMessages;
				_tev__PullMessagesResponse tev__PullMessagesResponse;
				if (pullpoint.PullMessages(&tev__PullMessages, &tev__PullMessagesResponse) == SOAP_OK)
				{
					for (auto msg : tev__PullMessagesResponse.wsnt__NotificationMessage)
					{
						std::cout << "Message:" << msg->Message.__any << std::endl;
					}
				}
				else
				{
					pullpoint.soap_stream_fault(std::cerr);
				}
			}
			else
			{
				eventProxy.soap_stream_fault(std::cerr);
			}
		}
		std::unique_ptr<ReplayBindingProxy> replayProxy;
		if ( (tds__GetCapabilitiesResponse.Capabilities->Extension != NULL) && (tds__GetCapabilitiesResponse.Capabilities->Extension->Replay != NULL) )
		{
			std::string replayUrl(tds__GetCapabilitiesResponse.Capabilities->Extension->Replay->XAddr);
			std::cout << "Replay Url:" << replayUrl << std::endl;
			
			replayProxy.reset(new ReplayBindingProxy(replayUrl.c_str()));
		}
		if ( (tds__GetCapabilitiesResponse.Capabilities->Extension != NULL) && (tds__GetCapabilitiesResponse.Capabilities->Extension->Recording != NULL) )
		{
			std::string recordingUrl(tds__GetCapabilitiesResponse.Capabilities->Extension->Recording->XAddr);
			std::cout << "Recording Url:" << recordingUrl << std::endl;
			
			RecordingBindingProxy recordingProxy(recordingUrl.c_str());
			
			_trc__GetRecordings         trc__GetRecordings;
			_trc__GetRecordingsResponse trc__GetRecordingsResponse;
			if (recordingProxy.GetRecordings(&trc__GetRecordings, &trc__GetRecordingsResponse) == SOAP_OK)
			{
				for (auto recording : trc__GetRecordingsResponse.RecordingItem)
				{
					std::string token(recording->RecordingToken);
					std::cout << "Recording:" << token << std::endl;
					
					if (replayProxy.get() != NULL)
					{
						_trp__GetReplayUri         trp__GetReplayUri;
						_trp__GetReplayUriResponse trp__GetReplayUriResponse;
						trp__GetReplayUri.RecordingToken = token;
						if (replayProxy->GetReplayUri(&trp__GetReplayUri, &trp__GetReplayUriResponse) == SOAP_OK)
						{
							std::cout << "Replay Uri:" << trp__GetReplayUriResponse.Uri << std::endl;
						}
						else
						{
							replayProxy->soap_stream_fault(std::cerr);
						}
					}
				}
			}
			else
			{
				recordingProxy.soap_stream_fault(std::cerr);
			}
		}
		
		if ( (tds__GetCapabilitiesResponse.Capabilities->Extension != NULL) && (tds__GetCapabilitiesResponse.Capabilities->Extension->Receiver != NULL) )
		{
			std::string receiverUrl(tds__GetCapabilitiesResponse.Capabilities->Extension->Receiver->XAddr);
			std::cout << "Receiver Url:" << receiverUrl << std::endl;
			
			ReceiverBindingProxy receiverProxy(receiverUrl.c_str());
			
			_trv__GetReceivers         trv__GetReceivers;
			_trv__GetReceiversResponse trv__GetReceiversResponse;
			if (receiverProxy.GetReceivers(&trv__GetReceivers, &trv__GetReceiversResponse) == SOAP_OK)
			{
				for (auto receiver : trv__GetReceiversResponse.Receivers)
				{
					std::string token(receiver->Token);
					std::cout << "Receiver:" << token << std::endl;					
				}
			}
			else
			{
				receiverProxy.soap_stream_fault(std::cerr);
			}
		}
	}
	else
	{
		deviceProxy.soap_stream_fault(std::cerr);
	}
	

	
        return 0;
}


