/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** serverPullPointSubscriptionBindingService.cpp
** 
** bw-2.wsdl server
**
** -------------------------------------------------------------------------*/

#include <sstream>

#include "soapPullPointSubscriptionBindingService.h"
#include "serviceContext.h"


int PullPointSubscriptionBindingService::PullMessages(_tev__PullMessages *tev__PullMessages, _tev__PullMessagesResponse *tev__PullMessagesResponse) 
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	for (int i=0; i<10; i++)
	{
		std::ostringstream os;
		os << "msg:" << i;
		std::string msg(os.str());
		tev__PullMessagesResponse->wsnt__NotificationMessage.push_back(soap_new_wsnt__NotificationMessageHolderType(this));
		tev__PullMessagesResponse->wsnt__NotificationMessage.back()->Message.__any = (char*)soap_malloc(this, msg.size());
		strncpy(tev__PullMessagesResponse->wsnt__NotificationMessage.back()->Message.__any, msg.c_str(), msg.size());
	}
	return SOAP_OK;
}

int PullPointSubscriptionBindingService::Seek(_tev__Seek *tev__Seek, _tev__SeekResponse *tev__SeekResponse) 
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return SOAP_OK;
}

int PullPointSubscriptionBindingService::SetSynchronizationPoint(_tev__SetSynchronizationPoint *tev__SetSynchronizationPoint, _tev__SetSynchronizationPointResponse *tev__SetSynchronizationPointResponse) 
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return SOAP_OK;
}
