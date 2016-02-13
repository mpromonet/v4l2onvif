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
#include "soapImagingBindingProxy.h"
#include "soapSearchBindingProxy.h"

#include "soapEventBindingProxy.h"
#include "soapPullPointSubscriptionBindingProxy.h"

#include "wsseapi.h"

void addSecurity(struct soap* soap, const std::string& username, const std::string & password)
{
	if (!username.empty())
	{
		soap_wsse_add_UsernameTokenDigest(soap, NULL, username.c_str() , password.c_str());	
	}
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
			std::string imagingUrl(tds__GetCapabilitiesResponse.Capabilities->Imaging->XAddr);
			std::cout << "\tImaging Url:" << imagingUrl << std::endl;
			
			imagingProxy.reset(new ImagingBindingProxy(imagingUrl.c_str()));
		}
		std::unique_ptr<ReplayBindingProxy> replayProxy;
		if ( (tds__GetCapabilitiesResponse.Capabilities->Extension != NULL) && (tds__GetCapabilitiesResponse.Capabilities->Extension->Replay != NULL) )
		{
			std::string replayUrl(tds__GetCapabilitiesResponse.Capabilities->Extension->Replay->XAddr);
			std::cout << "\tReplay Url:" << replayUrl << std::endl;
			
			replayProxy.reset(new ReplayBindingProxy(replayUrl.c_str()));
		}
		std::unique_ptr<MediaBindingProxy> mediaProxy;
		if (tds__GetCapabilitiesResponse.Capabilities->Media != NULL)
		{
			std::string mediaUrl(tds__GetCapabilitiesResponse.Capabilities->Media->XAddr);
			std::cout << "\tMedia Url:" << mediaUrl << std::endl;
			
			mediaProxy.reset(new MediaBindingProxy(mediaUrl.c_str()));
		}
		std::unique_ptr<ReceiverBindingProxy> receiverProxy;
		if ( (tds__GetCapabilitiesResponse.Capabilities->Extension != NULL) && (tds__GetCapabilitiesResponse.Capabilities->Extension->Receiver != NULL) )
		{
			std::string receiverUrl(tds__GetCapabilitiesResponse.Capabilities->Extension->Receiver->XAddr);
			std::cout << "\tReceiver Url:" << receiverUrl << std::endl;
			
			receiverProxy.reset(new ReceiverBindingProxy(receiverUrl.c_str()));
		}
		std::unique_ptr<RecordingBindingProxy> recordingProxy;
		if ( (tds__GetCapabilitiesResponse.Capabilities->Extension != NULL) && (tds__GetCapabilitiesResponse.Capabilities->Extension->Recording != NULL) )
		{
			std::string recordingUrl(tds__GetCapabilitiesResponse.Capabilities->Extension->Recording->XAddr);
			std::cout << "\tRecording Url:" << recordingUrl << std::endl;
			
			recordingProxy.reset(new RecordingBindingProxy(recordingUrl.c_str()));
		}		
		std::unique_ptr<SearchBindingProxy> searchProxy;
		if ( (tds__GetCapabilitiesResponse.Capabilities->Extension != NULL) && (tds__GetCapabilitiesResponse.Capabilities->Extension->Search != NULL) )
		{
			std::string searchUrl(tds__GetCapabilitiesResponse.Capabilities->Extension->Search->XAddr);
			std::cout << "\tSearch Url:" << searchUrl << std::endl;
			
			searchProxy.reset (new SearchBindingProxy(searchUrl.c_str()));
		}
		std::unique_ptr<EventBindingProxy> eventProxy;
		if (tds__GetCapabilitiesResponse.Capabilities->Events != NULL)
		{
			std::string eventUrl(tds__GetCapabilitiesResponse.Capabilities->Events->XAddr);
			std::cout << "\tEvent Url:" << eventUrl << std::endl;
			
			eventProxy.reset(new EventBindingProxy(eventUrl.c_str()));
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
								std::cout << "\tResolution:" << res->Width << "x" << res->Height << std::endl;
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
							std::cout << "\tBrightness:" << *timg__GetImagingSettingsResponse.ImagingSettings->Brightness      << std::endl;
							std::cout << "\tContrast  :" << *timg__GetImagingSettingsResponse.ImagingSettings->Contrast        << std::endl;
							std::cout << "\tSaturation:" << *timg__GetImagingSettingsResponse.ImagingSettings->ColorSaturation << std::endl;
							std::cout << "\tSharpness :" << *timg__GetImagingSettingsResponse.ImagingSettings->Sharpness       << std::endl;
						}
						
						_timg__GetOptions timg__GetOptions;
						timg__GetOptions.VideoSourceToken = source->token;
						_timg__GetOptionsResponse timg__GetOptionsResponse;
						addSecurity(imagingProxy->soap, username, password);						
						if (imagingProxy->GetOptions(&timg__GetOptions, &timg__GetOptionsResponse) == SOAP_OK)
						{
							std::cout << "\tBrightness: [" << timg__GetOptionsResponse.ImagingOptions->Brightness->Min      << "," << timg__GetOptionsResponse.ImagingOptions->Brightness->Max      << "]" << std::endl;
							std::cout << "\tContrast:   [" << timg__GetOptionsResponse.ImagingOptions->Contrast->Min        << "," << timg__GetOptionsResponse.ImagingOptions->Contrast->Max        << "]" << std::endl;
							std::cout << "\tSaturation: [" << timg__GetOptionsResponse.ImagingOptions->ColorSaturation->Min << "," << timg__GetOptionsResponse.ImagingOptions->ColorSaturation->Max << "]" << std::endl;
							std::cout << "\tSharpness:  [" << timg__GetOptionsResponse.ImagingOptions->Sharpness->Min       << "," << timg__GetOptionsResponse.ImagingOptions->Sharpness->Max       << "]" << std::endl;
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
					
					_trt__GetStreamUri         trt__GetStreamUri;
					_trt__GetStreamUriResponse trt__GetStreamUriResponse;
					trt__GetStreamUri.ProfileToken = token;
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
			_tev__CreatePullPointSubscription         tev__CreatePullPointSubscription;
			_tev__CreatePullPointSubscriptionResponse tev__CreatePullPointSubscriptionResponse;
			addSecurity(eventProxy->soap, username, password);						
			if (eventProxy->CreatePullPointSubscription(&tev__CreatePullPointSubscription, &tev__CreatePullPointSubscriptionResponse) == SOAP_OK)
			{
				std::cout << "\tPullpoint Url:" << tev__CreatePullPointSubscriptionResponse.SubscriptionReference.Address << std::endl;
				PullPointSubscriptionBindingProxy pullpoint(tev__CreatePullPointSubscriptionResponse.SubscriptionReference.Address);
				soap_wsse_add_Security(pullpoint.soap);
				
				_tev__PullMessages         tev__PullMessages;
				_tev__PullMessagesResponse tev__PullMessagesResponse;
				if (pullpoint.PullMessages(&tev__PullMessages, &tev__PullMessagesResponse) == SOAP_OK)
				{
					for (auto msg : tev__PullMessagesResponse.wsnt__NotificationMessage)
					{
						std::cout << "\tMessage:" << msg->Message.__any << std::endl;
					}
				}
			}
		}
	}
	
        return 0;
}


