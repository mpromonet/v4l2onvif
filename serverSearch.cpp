/* ---------------------------------------------------------------------------
** this->soap software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** serverSearch.cpp
** 
** search.wsdl server
**
** -------------------------------------------------------------------------*/


#include "soapSearchBindingService.h"
#include "server.h"

int SearchBindingService::GetServiceCapabilities(_tse__GetServiceCapabilities *tse__GetServiceCapabilities, _tse__GetServiceCapabilitiesResponse *tse__GetServiceCapabilitiesResponse) 
{	
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	tse__GetServiceCapabilitiesResponse->Capabilities = ctx->getSearchServiceCapabilities(this->soap);	
	return SOAP_OK;
}

int SearchBindingService::GetRecordingSummary(_tse__GetRecordingSummary *tse__GetRecordingSummary, _tse__GetRecordingSummaryResponse *tse__GetRecordingSummaryResponse) 
{	
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int SearchBindingService::GetRecordingInformation(_tse__GetRecordingInformation *tse__GetRecordingInformation, _tse__GetRecordingInformationResponse *tse__GetRecordingInformationResponse) 
{	
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int SearchBindingService::GetMediaAttributes(_tse__GetMediaAttributes *tse__GetMediaAttributes, _tse__GetMediaAttributesResponse *tse__GetMediaAttributesResponse) 
{	
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int SearchBindingService::FindRecordings(_tse__FindRecordings *tse__FindRecordings, _tse__FindRecordingsResponse *tse__FindRecordingsResponse) 
{	
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int SearchBindingService::GetRecordingSearchResults(_tse__GetRecordingSearchResults *tse__GetRecordingSearchResults, _tse__GetRecordingSearchResultsResponse *tse__GetRecordingSearchResultsResponse) 
{	
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int SearchBindingService::FindEvents(_tse__FindEvents *tse__FindEvents, _tse__FindEventsResponse *tse__FindEventsResponse) 
{	
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int SearchBindingService::GetEventSearchResults(_tse__GetEventSearchResults *tse__GetEventSearchResults, _tse__GetEventSearchResultsResponse *tse__GetEventSearchResultsResponse) 
{	
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int SearchBindingService::FindPTZPosition(_tse__FindPTZPosition *tse__FindPTZPosition, _tse__FindPTZPositionResponse *tse__FindPTZPositionResponse) 
{	
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int SearchBindingService::GetPTZPositionSearchResults(_tse__GetPTZPositionSearchResults *tse__GetPTZPositionSearchResults, _tse__GetPTZPositionSearchResultsResponse *tse__GetPTZPositionSearchResultsResponse) 
{	
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int SearchBindingService::GetSearchState(_tse__GetSearchState *tse__GetSearchState, _tse__GetSearchStateResponse *tse__GetSearchStateResponse) 
{	
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int SearchBindingService::EndSearch(_tse__EndSearch *tse__EndSearch, _tse__EndSearchResponse *tse__EndSearchResponse) 
{	
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int SearchBindingService::FindMetadata(_tse__FindMetadata *tse__FindMetadata, _tse__FindMetadataResponse *tse__FindMetadataResponse) 
{	
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int SearchBindingService::GetMetadataSearchResults(_tse__GetMetadataSearchResults *tse__GetMetadataSearchResults, _tse__GetMetadataSearchResultsResponse *tse__GetMetadataSearchResultsResponse) 
{	
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


