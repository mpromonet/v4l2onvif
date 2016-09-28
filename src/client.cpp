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
 client.cpp
 
 onvif client
----------------------------------------------------------------------------- */

#include <memory>
#include <sstream>
#include <thread>

#include "DeviceBinding.nsmap"
#include "soapDeviceBindingProxy.h"
#include "soapMediaBindingProxy.h"
#include "soapRecordingBindingProxy.h"
#include "soapReceiverBindingProxy.h"
#include "soapReplayBindingProxy.h"
#include "soapImagingBindingProxy.h"
#include "soapSearchBindingProxy.h"

#include "soapEventBindingProxy.h"
#include "soapPullPointSubscriptionBindingProxy.h"
#include "soapNotificationProducerBindingProxy.h"
#include "soapNotificationConsumerBindingService.h"

#include "wsseapi.h"

template<typename T>
std::string printPtr(T* ptr)
{
	std::ostringstream os;
	if (ptr)
	{
		os << *ptr;
	}
	else
	{	
		os << "(null)";
	}
	return os.str();
}

template<typename T>
std::string printMode(T* ptr)
{
	std::ostringstream os;
	if (ptr)
	{
		os << ptr->Mode;
	}
	else
	{	
		os << "(null)";
	}
	return os.str();
}

template<typename T>
std::string printRangePtr(T* ptr)
{
	std::ostringstream os;
	if (ptr)
	{
		os << "[" << ptr->Min << "," << ptr->Max << "]";
	}
	else
	{	
		os << "(null)";
	}
	return os.str();
}

template<typename T>
std::string printResolution(T* ptr)
{
	std::ostringstream os;
	if (ptr)
	{
		os << ptr->Width << "x" << ptr->Height;
	}
	else
	{	
		os << "(null)";
	}
	return os.str();
}

template<typename T>
std::string printRectangle(T* ptr)
{
	std::ostringstream os;
	if (ptr)
	{
		os << ptr->x << "x" << ptr->y << " " << ptr->width << "x" << ptr->height;
	}
	else
	{	
		os << "(null)";
	}
	return os.str();
}

void addSecurity(struct soap* soap, const std::string& username, const std::string & password)
{
	if (!username.empty())
	{
		soap_wsse_add_Timestamp(soap, "Time", 600);
		soap_wsse_add_UsernameTokenDigest(soap, "User", username.c_str() , password.c_str());	
	}
}

std::string getLocalIp()
{
	std::string serverAddress;
	char hostname[HOST_NAME_MAX];
	if (gethostname(hostname, sizeof(hostname)) == 0)
	{
		struct addrinfo hints;
		struct addrinfo *result;
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_INET;
		if (getaddrinfo(hostname, NULL, &hints, &result) == 0)
		{
			if (result != NULL) 
			{
				struct sockaddr_in* addr = (struct sockaddr_in *) result->ai_addr;
				serverAddress.assign(inet_ntoa( addr->sin_addr ));
				freeaddrinfo(result); 
			}
		}
	}
	return serverAddress;
}

int main(int argc, char* argv[])
{
	std::string url = "http://127.0.0.1:8080";
	std::string username;
	std::string password;
	int c=0;
	while ((c = getopt (argc, argv, "hu:p:")) != -1)
	{
		switch (c)
		{
			case 'u':	username = optarg; break;
			case 'p':	password = optarg; break;
			case 'h':
				std::cout << argv[0] << " [-u username] [-p password] url" << std::endl;
				exit(0);
			break;
		}
	}
	if (optind<argc)
	{
		url = argv[optind];
	}		
	
	std::cout << "Connecting to " << url << std::endl;

	
	// create connection to devicemgmt.wsdl server
        DeviceBindingProxy deviceProxy(url.c_str());
	
	// call Device::GetDeviceInformation
	std::cout << "=>Device::GetDeviceInformation" << std::endl;	
	_tds__GetDeviceInformation         tds__GetDeviceInformation;
	_tds__GetDeviceInformationResponse tds__GetDeviceInformationResponse;
	addSecurity(deviceProxy.soap, username, password);	
	if (deviceProxy.GetDeviceInformation(&tds__GetDeviceInformation, &tds__GetDeviceInformationResponse) == SOAP_OK)
	{
		std::cout << "\tManufacturer:" << tds__GetDeviceInformationResponse.Manufacturer << std::endl;
	}
	else
	{
		deviceProxy.soap_stream_fault(std::cerr);
	}

	// call Device::GetHostname
	std::cout << "=>Device::GetHostname" << std::endl;	
	_tds__GetHostname         tds__GetHostname;
	_tds__GetHostnameResponse tds__GetHostnameResponse;
	addSecurity(deviceProxy.soap, username, password);	
	if (deviceProxy.GetHostname(&tds__GetHostname, &tds__GetHostnameResponse) == SOAP_OK)
	{
		std::cout << "\tHostname:" << tds__GetHostnameResponse.HostnameInformation->Name->c_str() << std::endl;
	}
	else
	{
		deviceProxy.soap_stream_fault(std::cerr);
	}

        // call Device::GetDNS
        std::cout << "=>Device::GetDNS" << std::endl;
        _tds__GetDNS         tds__GetDNS;
        _tds__GetDNSResponse tds__GetDNSResponse;
        addSecurity(deviceProxy.soap, username, password);
        if (deviceProxy.GetDNS(&tds__GetDNS, &tds__GetDNSResponse) == SOAP_OK)
        {
		for (auto dns : tds__GetDNSResponse.DNSInformation->DNSManual)
		{
			if (dns->IPv4Address)
			{
		                std::cout << "\tDNS:" << dns->IPv4Address->c_str() << std::endl;
			}
		}
        }
        else
        {
                deviceProxy.soap_stream_fault(std::cerr);
        }

	// call Device::GetNetworkInterfaces
	std::cout << "=>Device::GetNetworkInterfaces" << std::endl;	
	_tds__GetNetworkInterfaces         tds__GetNetworkInterfaces;
	_tds__GetNetworkInterfacesResponse tds__GetNetworkInterfacesResponse;
	addSecurity(deviceProxy.soap, username, password);	
	if (deviceProxy.GetNetworkInterfaces(&tds__GetNetworkInterfaces, &tds__GetNetworkInterfacesResponse) == SOAP_OK)
	{
		for (auto iface : tds__GetNetworkInterfacesResponse.NetworkInterfaces)
		{
			if (iface->Info != NULL)
			{
				std::cout << "\t" << iface->Info->Name->c_str() <<  " " << iface->Info->HwAddress << std::endl;			
			}
			if ( (iface->IPv4 != NULL) && (iface->IPv4->Config != NULL) )
			{
				for (auto addr : iface->IPv4->Config->Manual)
				{
					std::cout << "\tIP:" << addr->Address  << "/" << addr->PrefixLength << std::endl;					
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
	addSecurity(deviceProxy.soap, username, password);	
	if (deviceProxy.GetServices(&tds__GetServices, &tds__GetServicesResponse) == SOAP_OK)
	{
		for (auto service : tds__GetServicesResponse.Service)
		{
			std::cout << "\tns:" << service->Namespace << " " << service->XAddr << " Version:" << service->Version->Major << "." << service->Version->Minor << std::endl;
			if (service->Capabilities)
			{
				std::cout << "\t" << service->Capabilities->__any << std::endl;
			}
		}
	}
	
	// call Device::GetCapabilities
	std::cout << "=>Device::GetCapabilities" << std::endl;		
	_tds__GetCapabilities         tds__GetCapabilities;
	_tds__GetCapabilitiesResponse tds__GetCapabilitiesResponse;
	addSecurity(deviceProxy.soap, username, password);	
	if (deviceProxy.GetCapabilities(&tds__GetCapabilities, &tds__GetCapabilitiesResponse) == SOAP_OK)
	{
		std::unique_ptr<ImagingBindingProxy> imagingProxy;
		if ( (tds__GetCapabilitiesResponse.Capabilities->Extension != NULL) && (tds__GetCapabilitiesResponse.Capabilities->Imaging != NULL) )
		{
			std::cout << "\tImaging Url:" << tds__GetCapabilitiesResponse.Capabilities->Imaging->XAddr << std::endl;			
			imagingProxy.reset(new ImagingBindingProxy(tds__GetCapabilitiesResponse.Capabilities->Imaging->XAddr.c_str()));
		}
		std::unique_ptr<ReplayBindingProxy> replayProxy;
		if ( (tds__GetCapabilitiesResponse.Capabilities->Extension != NULL) && (tds__GetCapabilitiesResponse.Capabilities->Extension->Replay != NULL) )
		{
			std::cout << "\tReplay Url:" << tds__GetCapabilitiesResponse.Capabilities->Extension->Replay->XAddr << std::endl;			
			replayProxy.reset(new ReplayBindingProxy(tds__GetCapabilitiesResponse.Capabilities->Extension->Replay->XAddr.c_str()));
		}
		std::unique_ptr<MediaBindingProxy> mediaProxy;
		if (tds__GetCapabilitiesResponse.Capabilities->Media != NULL)
		{
			std::cout << "\tMedia Url:" << tds__GetCapabilitiesResponse.Capabilities->Media->XAddr << std::endl;			
			mediaProxy.reset(new MediaBindingProxy(tds__GetCapabilitiesResponse.Capabilities->Media->XAddr.c_str()));
		}
		std::unique_ptr<ReceiverBindingProxy> receiverProxy;
		if ( (tds__GetCapabilitiesResponse.Capabilities->Extension != NULL) && (tds__GetCapabilitiesResponse.Capabilities->Extension->Receiver != NULL) )
		{
			std::cout << "\tReceiver Url:" << tds__GetCapabilitiesResponse.Capabilities->Extension->Receiver->XAddr << std::endl;			
			receiverProxy.reset(new ReceiverBindingProxy(tds__GetCapabilitiesResponse.Capabilities->Extension->Receiver->XAddr.c_str()));
		}
		std::unique_ptr<RecordingBindingProxy> recordingProxy;
		if ( (tds__GetCapabilitiesResponse.Capabilities->Extension != NULL) && (tds__GetCapabilitiesResponse.Capabilities->Extension->Recording != NULL) )
		{
			std::cout << "\tRecording Url:" << tds__GetCapabilitiesResponse.Capabilities->Extension->Recording->XAddr << std::endl;			
			recordingProxy.reset(new RecordingBindingProxy(tds__GetCapabilitiesResponse.Capabilities->Extension->Recording->XAddr.c_str()));
		}		
		std::unique_ptr<SearchBindingProxy> searchProxy;
		if ( (tds__GetCapabilitiesResponse.Capabilities->Extension != NULL) && (tds__GetCapabilitiesResponse.Capabilities->Extension->Search != NULL) )
		{
			std::cout << "\tSearch Url:" << tds__GetCapabilitiesResponse.Capabilities->Extension->Search->XAddr << std::endl;			
			searchProxy.reset (new SearchBindingProxy(tds__GetCapabilitiesResponse.Capabilities->Extension->Search->XAddr.c_str()));
		}
		std::unique_ptr<EventBindingProxy> eventProxy;
		if (tds__GetCapabilitiesResponse.Capabilities->Events != NULL)
		{
			std::cout << "\tEvent Url:" << tds__GetCapabilitiesResponse.Capabilities->Events->XAddr << std::endl;			
			eventProxy.reset(new EventBindingProxy(tds__GetCapabilitiesResponse.Capabilities->Events->XAddr.c_str()));
		}
		
		
		if (mediaProxy.get() != NULL)
		{
			// call Media::GetVideoSources
			std::cout << "=>Media::GetVideoSources" << std::endl;				
			_trt__GetVideoSources         trt__GetVideoSources;
			_trt__GetVideoSourcesResponse trt__GetVideoSourcesResponse;			
			addSecurity(mediaProxy->soap, username, password);	
			if (mediaProxy->GetVideoSources(&trt__GetVideoSources, &trt__GetVideoSourcesResponse) == SOAP_OK)
			{		
				for (auto source : trt__GetVideoSourcesResponse.VideoSources)
				{
					std::cout << "\t" << source->token;
					if (source->Resolution)
					{
						std::cout << " " << source->Resolution->Width << "x" << source->Resolution->Height;
					}
					std::cout << std::endl;
					
					_trt__GetVideoEncoderConfiguration         trt__GetVideoEncoderConfiguration;
					trt__GetVideoEncoderConfiguration.ConfigurationToken = source->token;
					_trt__GetVideoEncoderConfigurationResponse trt__GetVideoEncoderConfigurationResponse;
					addSecurity(mediaProxy->soap, username, password);						
					if (mediaProxy->GetVideoEncoderConfiguration(&trt__GetVideoEncoderConfiguration, &trt__GetVideoEncoderConfigurationResponse) == SOAP_OK)
					{		
						std::cout << "\tEncoding:" << trt__GetVideoEncoderConfigurationResponse.Configuration->Encoding << std::endl;
						if (trt__GetVideoEncoderConfigurationResponse.Configuration->H264)
						{
							std::cout << "\tH264Profile:" << trt__GetVideoEncoderConfigurationResponse.Configuration->H264->H264Profile << std::endl;
						}
						if (trt__GetVideoEncoderConfigurationResponse.Configuration->Resolution)
						{
							std::cout << "\tResolution:" << trt__GetVideoEncoderConfigurationResponse.Configuration->Resolution->Width << "x" << trt__GetVideoEncoderConfigurationResponse.Configuration->Resolution->Height << std::endl;
						}
					}

					_trt__GetVideoEncoderConfigurationOptions         trt__GetVideoEncoderConfigurationOptions;
					trt__GetVideoEncoderConfigurationOptions.ConfigurationToken = soap_new_std__string(mediaProxy->soap);
					trt__GetVideoEncoderConfigurationOptions.ConfigurationToken->assign(source->token);
					_trt__GetVideoEncoderConfigurationOptionsResponse trt__GetVideoEncoderConfigurationOptionsResponse;
					addSecurity(mediaProxy->soap, username, password);						
					if (mediaProxy->GetVideoEncoderConfigurationOptions(&trt__GetVideoEncoderConfigurationOptions, &trt__GetVideoEncoderConfigurationOptionsResponse) == SOAP_OK)
					{	
						if (trt__GetVideoEncoderConfigurationOptionsResponse.Options->H264)
						{
							for (auto res : trt__GetVideoEncoderConfigurationOptionsResponse.Options->H264->ResolutionsAvailable)
							{
								std::cout << "\tResolution:" << printResolution(res) << std::endl;
							}
						}
					}
					
					if (imagingProxy.get() != NULL)
					{
						_timg__GetImagingSettings timg__GetImagingSettings;
						timg__GetImagingSettings.VideoSourceToken = source->token;
						_timg__GetImagingSettingsResponse timg__GetImagingSettingsResponse;
						addSecurity(imagingProxy->soap, username, password);						
						if (imagingProxy->GetImagingSettings(&timg__GetImagingSettings, &timg__GetImagingSettingsResponse) == SOAP_OK)
						{
							std::cout << "\tBrightness  :" << printPtr (timg__GetImagingSettingsResponse.ImagingSettings->Brightness)            << std::endl;
							std::cout << "\tContrast    :" << printPtr (timg__GetImagingSettingsResponse.ImagingSettings->Contrast)              << std::endl;
							std::cout << "\tSaturation  :" << printPtr (timg__GetImagingSettingsResponse.ImagingSettings->ColorSaturation)       << std::endl;
							std::cout << "\tSharpness   :" << printPtr (timg__GetImagingSettingsResponse.ImagingSettings->Sharpness)             << std::endl;
							std::cout << "\tBacklight   :" << printMode(timg__GetImagingSettingsResponse.ImagingSettings->BacklightCompensation) << std::endl;
							std::cout << "\tWideDynamic :" << printMode(timg__GetImagingSettingsResponse.ImagingSettings->WideDynamicRange) << std::endl;
							std::cout << "\tExposure    :" << printMode(timg__GetImagingSettingsResponse.ImagingSettings->Exposure)              << std::endl;
							if (timg__GetImagingSettingsResponse.ImagingSettings->Exposure)
								std::cout << "\t\tExposureTime :" << printPtr(timg__GetImagingSettingsResponse.ImagingSettings->Exposure->ExposureTime)          << std::endl;
							std::cout << "\tWhiteBalance:" << printMode(timg__GetImagingSettingsResponse.ImagingSettings->WhiteBalance)          << std::endl;
							
						}
						
						_timg__GetOptions timg__GetOptions;
						timg__GetOptions.VideoSourceToken = source->token;
						_timg__GetOptionsResponse timg__GetOptionsResponse;
						addSecurity(imagingProxy->soap, username, password);						
						if (imagingProxy->GetOptions(&timg__GetOptions, &timg__GetOptionsResponse) == SOAP_OK)
						{
							std::cout << "\tBrightness: " << printRangePtr(timg__GetOptionsResponse.ImagingOptions->Brightness)      << std::endl;
							std::cout << "\tContrast  : " << printRangePtr(timg__GetOptionsResponse.ImagingOptions->Contrast)        << std::endl;
							std::cout << "\tSaturation: " << printRangePtr(timg__GetOptionsResponse.ImagingOptions->ColorSaturation) << std::endl;
							std::cout << "\tSharpness : " << printRangePtr(timg__GetOptionsResponse.ImagingOptions->Sharpness)       << std::endl;
						}
						
					}
				}
			}
			
			std::cout << "=>Media::GetProfiles" << std::endl;					
			_trt__GetProfiles         trt__GetProfiles;
			_trt__GetProfilesResponse trt__GetProfilesResponse;
			addSecurity(mediaProxy->soap, username, password);								
			if (mediaProxy->GetProfiles(&trt__GetProfiles, &trt__GetProfilesResponse) == SOAP_OK)
			{		
				for (auto profile : trt__GetProfilesResponse.Profiles)
				{
					std::string token(profile->token);
					std::cout << "\tMediaProfile:" << token << std::endl;
					if (profile->VideoSourceConfiguration)
					{ 
						std::cout << "\ttoken:" << profile->VideoSourceConfiguration->token                              << std::endl;
						std::cout << "\tSourceToken:" << profile->VideoSourceConfiguration->SourceToken                  << std::endl;
						std::cout << "\tBounds:"      << printRectangle(profile->VideoSourceConfiguration->Bounds)       << std::endl;
					}
					if (profile->VideoEncoderConfiguration)
					{
						std::cout << "\ttoken:" << profile->VideoEncoderConfiguration->token                             << std::endl;
						std::cout << "\tQuality:"    << profile->VideoEncoderConfiguration->Quality                      << std::endl;
						std::cout << "\tResolution:" << printResolution(profile->VideoEncoderConfiguration->Resolution)  << std::endl;
						if (profile->VideoEncoderConfiguration->H264)
						{
							std::cout << "\tGovLength:"   << profile->VideoEncoderConfiguration->H264->GovLength     << std::endl;
							std::cout << "\tH264Profile:" << profile->VideoEncoderConfiguration->H264->H264Profile   << std::endl;
						}
					}
					
					_trt__GetStreamUri         trt__GetStreamUri;
					_trt__GetStreamUriResponse trt__GetStreamUriResponse;
					trt__GetStreamUri.ProfileToken = token;
					trt__GetStreamUri.StreamSetup = soap_new_tt__StreamSetup(mediaProxy->soap);
					trt__GetStreamUri.StreamSetup->Transport = soap_new_tt__Transport(mediaProxy->soap);
					trt__GetStreamUri.StreamSetup->Transport->Protocol = tt__TransportProtocol__RTSP;
					addSecurity(mediaProxy->soap, username, password);						
					if (mediaProxy->GetStreamUri(&trt__GetStreamUri, &trt__GetStreamUriResponse) == SOAP_OK)
					{
						std::cout << "\tMediaUri:" << trt__GetStreamUriResponse.MediaUri->Uri << std::endl;
					}
				}
			}
		}	
		
		if (recordingProxy.get() != NULL)
		{
			std::cout << "=>Recording::GetRecordings" << std::endl;											
			_trc__GetRecordings         trc__GetRecordings;
			_trc__GetRecordingsResponse trc__GetRecordingsResponse;
			addSecurity(recordingProxy->soap, username, password);						
			if (recordingProxy->GetRecordings(&trc__GetRecordings, &trc__GetRecordingsResponse) == SOAP_OK)
			{
				for (auto recording : trc__GetRecordingsResponse.RecordingItem)
				{
					std::string token(recording->RecordingToken);
					std::cout << "\tRecording:" << token << std::endl;
					
					if (replayProxy.get() != NULL)
					{
						_trp__GetReplayUri         trp__GetReplayUri;
						_trp__GetReplayUriResponse trp__GetReplayUriResponse;
						trp__GetReplayUri.RecordingToken = token;
						addSecurity(replayProxy->soap, username, password);						
						if (replayProxy->GetReplayUri(&trp__GetReplayUri, &trp__GetReplayUriResponse) == SOAP_OK)
						{
							std::cout << "\tReplay Uri:" << trp__GetReplayUriResponse.Uri << std::endl;
						}
					}
				}
			}
			
			std::cout << "=>Recording::GetRecordingJobs" << std::endl;											
			_trc__GetRecordingJobs         trc__GetRecordingJobs;
			_trc__GetRecordingJobsResponse trc__GetRecordingJobsResponse;
			addSecurity(recordingProxy->soap, username, password);						
			if (recordingProxy->GetRecordingJobs(&trc__GetRecordingJobs, &trc__GetRecordingJobsResponse) == SOAP_OK)
			{
				for (auto job : trc__GetRecordingJobsResponse.JobItem)
				{
					std::string token(job->JobToken);
					std::cout << "\tRecordingJob:" << token << std::endl;
					
					if (job->JobConfiguration)
					{
						std::cout << "\tRecordingToken:" << job->JobConfiguration->RecordingToken << std::endl;						
						for (auto src : job->JobConfiguration->Source)
						{
							if (src->SourceToken)
							{
								std::cout << "\tSourceToken:" << src->SourceToken->Token << std::endl;						
								std::cout << "\tSourceType:" << src->SourceToken->Type << std::endl;						
							}
						}
					}
				}
			}
		}
		
		if (receiverProxy.get() != NULL)
		{
			std::cout << "=>Receiver::GetReceivers" << std::endl;								
			_trv__GetReceivers         trv__GetReceivers;
			_trv__GetReceiversResponse trv__GetReceiversResponse;
			addSecurity(receiverProxy->soap, username, password);									
			if (receiverProxy->GetReceivers(&trv__GetReceivers, &trv__GetReceiversResponse) == SOAP_OK)
			{
				for (auto receiver : trv__GetReceiversResponse.Receivers)
				{
					std::string token(receiver->Token);
					std::cout << "\tReceiver:" << token << std::endl;	

					if (receiver->Configuration)
					{
						std::cout << "\tReceiver mode:" << receiver->Configuration->Mode << " uri:" << receiver->Configuration->MediaUri << std::endl;	
					}
				}
			}
		}
		
		if (eventProxy.get() != NULL)
		{
			std::cout << "=>Event::CreatePullPoint" << std::endl;								
			_tev__CreatePullPointSubscription         tev__CreatePullPointSubscription;
			_tev__CreatePullPointSubscriptionResponse tev__CreatePullPointSubscriptionResponse;
			addSecurity(eventProxy->soap, username, password);						
			if (eventProxy->CreatePullPointSubscription(&tev__CreatePullPointSubscription, &tev__CreatePullPointSubscriptionResponse) == SOAP_OK)
			{
				std::cout << "\tPullpoint Url:" << tev__CreatePullPointSubscriptionResponse.SubscriptionReference.Address << std::endl;
				
				// pull
				PullPointSubscriptionBindingProxy pullpoint(tev__CreatePullPointSubscriptionResponse.SubscriptionReference.Address);
				soap_wsse_add_Security(pullpoint.soap);
				
				_tev__PullMessages         tev__PullMessages;
				tev__PullMessages.Timeout = "PT10S";
				tev__PullMessages.MessageLimit = 100;
				_tev__PullMessagesResponse tev__PullMessagesResponse;
				if (pullpoint.PullMessages(&tev__PullMessages, &tev__PullMessagesResponse) == SOAP_OK)
				{
					for (auto msg : tev__PullMessagesResponse.wsnt__NotificationMessage)
					{
						std::cout << "\tMessage:" << msg->Message.__any << std::endl;
					}
				}
				
				// subscribe
				const char* notifPort = "9090";
				NotificationConsumerBindingService consumer;
				consumer.soap->accept_timeout=5;
				consumer.bind(NULL,0,10);
				std::thread th(&NotificationConsumerBindingService::run, &consumer, 0);
				
				NotificationProducerBindingProxy producer(tev__CreatePullPointSubscriptionResponse.SubscriptionReference.Address);
				soap_wsse_add_Security(producer.soap);

				// build url to the server
				struct sockaddr_in sin;
				socklen_t len = sizeof(sin);
				std::ostringstream os;
				os << "http://" << getLocalIp() ;
				if (getsockname(consumer.soap->master, (struct sockaddr *)&sin, &len) != -1)
				{
					os << ":" << ntohs(sin.sin_port);
				}				
				std::string url(os.str());
				
				_wsnt__Subscribe         wsnt__Subscribe;
				wsnt__Subscribe.ConsumerReference.Address = strcpy((char*)soap_malloc(producer.soap, url.size()+1), url.c_str());
				_wsnt__SubscribeResponse wsnt__SubscribeResponse;
				if (producer.Subscribe(&wsnt__Subscribe, &wsnt__SubscribeResponse) == SOAP_OK)
				{
					std::cout << "SubscriptionReference:" << wsnt__SubscribeResponse.SubscriptionReference.Address << std::endl;
				}
				else
				{
					producer.soap_stream_fault(std::cerr);
				}

				th.join();
			}
		}
	}
	
        return 0;
}


