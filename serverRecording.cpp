/* ---------------------------------------------------------------------------
** this->soap software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** serverRecording.cpp
** 
** recording.wsdl server
**
** -------------------------------------------------------------------------*/


#include "soapRecordingBindingService.h"
#include "onvif_impl.h"

int RecordingBindingService::GetServiceCapabilities(_trc__GetServiceCapabilities *trc__GetServiceCapabilities, _trc__GetServiceCapabilitiesResponse *trc__GetServiceCapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	trc__GetServiceCapabilitiesResponse->Capabilities = ctx->getRecordingServiceCapabilities(this->soap);
	return SOAP_OK;
}

int RecordingBindingService::CreateRecording(_trc__CreateRecording *trc__CreateRecording, _trc__CreateRecordingResponse *trc__CreateRecordingResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int RecordingBindingService::DeleteRecording(_trc__DeleteRecording *trc__DeleteRecording, _trc__DeleteRecordingResponse *trc__DeleteRecordingResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int RecordingBindingService::GetRecordings(_trc__GetRecordings *trc__GetRecordings, _trc__GetRecordingsResponse *trc__GetRecordingsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	trc__GetRecordingsResponse->RecordingItem.push_back(soap_new_tt__GetRecordingsResponseItem(this->soap));
	for (auto it: ctx->m_devices) 
	{		
		trc__GetRecordingsResponse->RecordingItem.back()->RecordingToken = it.first;
		trc__GetRecordingsResponse->RecordingItem.back()->Configuration	= ctx->getRecordingCfg(this->soap);
		trc__GetRecordingsResponse->RecordingItem.back()->Tracks = soap_new_tt__GetTracksResponseList(soap);
		trc__GetRecordingsResponse->RecordingItem.back()->Tracks->Track.push_back(soap_new_tt__GetTracksResponseItem(soap));
		trc__GetRecordingsResponse->RecordingItem.back()->Tracks->Track.back()->TrackToken = "video";
		trc__GetRecordingsResponse->RecordingItem.back()->Tracks->Track.back()->Configuration = ctx->getTracksCfg(this->soap);
	}
	return SOAP_OK;
}

int RecordingBindingService::SetRecordingConfiguration(_trc__SetRecordingConfiguration *trc__SetRecordingConfiguration, _trc__SetRecordingConfigurationResponse *trc__SetRecordingConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int RecordingBindingService::GetRecordingConfiguration(_trc__GetRecordingConfiguration *trc__GetRecordingConfiguration, _trc__GetRecordingConfigurationResponse *trc__GetRecordingConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	auto it = ctx->m_devices.find(trc__GetRecordingConfiguration->RecordingToken);
	if (it != ctx->m_devices.end())
	{
		trc__GetRecordingConfigurationResponse->RecordingConfiguration = ctx->getRecordingCfg(this->soap);
	}
	return SOAP_OK;
}

int RecordingBindingService::GetRecordingOptions(_trc__GetRecordingOptions *trc__GetRecordingOptions, _trc__GetRecordingOptionsResponse *trc__GetRecordingOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	trc__GetRecordingOptionsResponse->Options = soap_new_trc__RecordingOptions(this->soap);
	trc__GetRecordingOptionsResponse->Options->Job = soap_new_trc__JobOptions(this->soap);
	trc__GetRecordingOptionsResponse->Options->Track = soap_new_trc__TrackOptions(this->soap);
	return SOAP_OK;
}

int RecordingBindingService::CreateTrack(_trc__CreateTrack *trc__CreateTrack, _trc__CreateTrackResponse *trc__CreateTrackResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int RecordingBindingService::DeleteTrack(_trc__DeleteTrack *trc__DeleteTrack, _trc__DeleteTrackResponse *trc__DeleteTrackResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int RecordingBindingService::GetTrackConfiguration(_trc__GetTrackConfiguration *trc__GetTrackConfiguration, _trc__GetTrackConfigurationResponse *trc__GetTrackConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	auto it = ctx->m_devices.find(trc__GetTrackConfiguration->RecordingToken);
	if ( (it != ctx->m_devices.end()) && (trc__GetTrackConfiguration->TrackToken == "video") )
	{
		trc__GetTrackConfigurationResponse->TrackConfiguration = ctx->getTracksCfg(this->soap);
	}
	return SOAP_OK;
}

int RecordingBindingService::SetTrackConfiguration(_trc__SetTrackConfiguration *trc__SetTrackConfiguration, _trc__SetTrackConfigurationResponse *trc__SetTrackConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int RecordingBindingService::CreateRecordingJob(_trc__CreateRecordingJob *trc__CreateRecordingJob, _trc__CreateRecordingJobResponse *trc__CreateRecordingJobResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int RecordingBindingService::DeleteRecordingJob(_trc__DeleteRecordingJob *trc__DeleteRecordingJob, _trc__DeleteRecordingJobResponse *trc__DeleteRecordingJobResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int RecordingBindingService::GetRecordingJobs(_trc__GetRecordingJobs *trc__GetRecordingJobs, _trc__GetRecordingJobsResponse *trc__GetRecordingJobsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	for (auto it: ctx->m_devices) 
	{		
		trc__GetRecordingJobsResponse->JobItem.push_back(soap_new_tt__GetRecordingJobsResponseItem(this->soap));
		trc__GetRecordingJobsResponse->JobItem.back()->JobToken = it.first;	
		trc__GetRecordingJobsResponse->JobItem.back()->JobConfiguration	= ctx->getRecordingJobConfiguration(this->soap, it.first);
	}
	
	return SOAP_OK;
}

int RecordingBindingService::SetRecordingJobConfiguration(_trc__SetRecordingJobConfiguration *trc__SetRecordingJobConfiguration, _trc__SetRecordingJobConfigurationResponse *trc__SetRecordingJobConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int RecordingBindingService::GetRecordingJobConfiguration(_trc__GetRecordingJobConfiguration *trc__GetRecordingJobConfiguration, _trc__GetRecordingJobConfigurationResponse *trc__GetRecordingJobConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	auto it = ctx->m_devices.find(trc__GetRecordingJobConfiguration->JobToken);
	if (it != ctx->m_devices.end())
	{
		trc__GetRecordingJobConfigurationResponse->JobConfiguration = ctx->getRecordingJobConfiguration(this->soap, it->first);
	}
	return SOAP_OK;
}

int RecordingBindingService::SetRecordingJobMode(_trc__SetRecordingJobMode *trc__SetRecordingJobMode, _trc__SetRecordingJobModeResponse *trc__SetRecordingJobModeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int RecordingBindingService::GetRecordingJobState(_trc__GetRecordingJobState *trc__GetRecordingJobState, _trc__GetRecordingJobStateResponse *trc__GetRecordingJobStateResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int RecordingBindingService::ExportRecordedData(_trc__ExportRecordedData *trc__ExportRecordedData, _trc__ExportRecordedDataResponse *trc__ExportRecordedDataResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int RecordingBindingService::StopExportRecordedData(_trc__StopExportRecordedData *trc__StopExportRecordedData, _trc__StopExportRecordedDataResponse *trc__StopExportRecordedDataResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int RecordingBindingService::GetExportRecordedDataState(_trc__GetExportRecordedDataState *trc__GetExportRecordedDataState, _trc__GetExportRecordedDataStateResponse *trc__GetExportRecordedDataStateResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}
