/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** serverEvent.cpp
** 
** event.wsdl server
**
** -------------------------------------------------------------------------*/

#include "soapEventBindingService.h"
#include "serviceContext.h"


int EventBindingService::GetServiceCapabilities(_tev__GetServiceCapabilities *tev__GetServiceCapabilities, _tev__GetServiceCapabilitiesResponse *tev__GetServiceCapabilitiesResponse) 
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return SOAP_OK;
}

int EventBindingService::CreatePullPointSubscription(_tev__CreatePullPointSubscription *tev__CreatePullPointSubscription, _tev__CreatePullPointSubscriptionResponse *tev__CreatePullPointSubscriptionResponse) 
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	std::string url("http://");
	url.append(getServerIpFromClientIp(htonl(this->ip))).append(":8085");	
	
	time_t sec = time(NULL);
	tev__CreatePullPointSubscriptionResponse->SubscriptionReference.Address = (char*)soap_malloc(this, url.size());
	strncpy(tev__CreatePullPointSubscriptionResponse->SubscriptionReference.Address, url.c_str(), url.size());
	tev__CreatePullPointSubscriptionResponse->wsnt__CurrentTime = sec;
	tev__CreatePullPointSubscriptionResponse->wsnt__CurrentTime = sec+3600;
	return SOAP_OK;
}

int EventBindingService::GetEventProperties(_tev__GetEventProperties *tev__GetEventProperties, _tev__GetEventPropertiesResponse *tev__GetEventPropertiesResponse) 
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return SOAP_OK;
}

