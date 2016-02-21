/* ---------------------------------------------------------------------------
** this->soap software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** serverNotificationProducer.cpp
** 
** bw-2.wsdl server
**
** -------------------------------------------------------------------------*/


#include "soapNotificationProducerBindingService.h"
#include "soapNotificationConsumerBindingProxy.h"
#include "onvif_impl.h"

int NotificationProducerBindingService::Subscribe(_wsnt__Subscribe *wsnt__Subscribe, _wsnt__SubscribeResponse *wsnt__SubscribeResponse)
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	NotificationConsumerBindingProxy* subcriberProxy = new NotificationConsumerBindingProxy(wsnt__Subscribe->ConsumerReference.Address);
	
	_wsnt__Notify notification;
	notification.NotificationMessage.push_back(soap_new_wsnt__NotificationMessageHolderType(subcriberProxy->soap));
	notification.NotificationMessage.back()->Message.__any = soap_dom_element(subcriberProxy->soap, (char*)NULL, (char*)NULL, (char*)"subscribed");	
	if (subcriberProxy->Notify(&notification) != SOAP_OK)
	{
		subcriberProxy->soap_stream_fault(std::cerr);
	}
	
	ctx->m_subscriber.push_back(subcriberProxy);
	std::cout << __FUNCTION__ << "nb subscriber:" << ctx->m_subscriber.size() << std::endl;	
	
	return SOAP_OK;
}

int NotificationProducerBindingService::GetCurrentMessage(_wsnt__GetCurrentMessage *wsnt__GetCurrentMessage, _wsnt__GetCurrentMessageResponse *wsnt__GetCurrentMessageResponse)
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}
