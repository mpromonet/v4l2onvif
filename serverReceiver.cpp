/* ---------------------------------------------------------------------------
** this->soap software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** serverReceiver.cpp
** 
** receiver.wsdl server
**
** -------------------------------------------------------------------------*/


#include "soapReceiverBindingService.h"
#include "serviceContext.h"

int ReceiverBindingService::GetServiceCapabilities(_trv__GetServiceCapabilities *trv__GetServiceCapabilities, _trv__GetServiceCapabilitiesResponse *trv__GetServiceCapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ReceiverBindingService::GetReceivers(_trv__GetReceivers *trv__GetReceivers, _trv__GetReceiversResponse *trv__GetReceiversResponse) 
{	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ReceiverBindingService::GetReceiver(_trv__GetReceiver *trv__GetReceiver, _trv__GetReceiverResponse *trv__GetReceiverResponse) 
{	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ReceiverBindingService::CreateReceiver(_trv__CreateReceiver *trv__CreateReceiver, _trv__CreateReceiverResponse *trv__CreateReceiverResponse) 
{	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ReceiverBindingService::DeleteReceiver(_trv__DeleteReceiver *trv__DeleteReceiver, _trv__DeleteReceiverResponse *trv__DeleteReceiverResponse) 
{	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ReceiverBindingService::ConfigureReceiver(_trv__ConfigureReceiver *trv__ConfigureReceiver, _trv__ConfigureReceiverResponse *trv__ConfigureReceiverResponse) 
{	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ReceiverBindingService::SetReceiverMode(_trv__SetReceiverMode *trv__SetReceiverMode, _trv__SetReceiverModeResponse *trv__SetReceiverModeResponse) 
{	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ReceiverBindingService::GetReceiverState(_trv__GetReceiverState *trv__GetReceiverState, _trv__GetReceiverStateResponse *trv__GetReceiverStateResponse) 
{	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}


