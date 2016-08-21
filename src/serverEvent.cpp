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
 serverEvent.cpp
 
 events.wsdl server
----------------------------------------------------------------------------- */

#include <sstream>

#include "soapEventBindingService.h"
#include "onvif_impl.h"


int EventBindingService::GetServiceCapabilities(_tev__GetServiceCapabilities *tev__GetServiceCapabilities, _tev__GetServiceCapabilitiesResponse *tev__GetServiceCapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	tev__GetServiceCapabilitiesResponse->Capabilities = ctx->getEventServiceCapabilities(this->soap);		
	return SOAP_OK;
}

int EventBindingService::CreatePullPointSubscription(_tev__CreatePullPointSubscription *tev__CreatePullPointSubscription, _tev__CreatePullPointSubscriptionResponse *tev__CreatePullPointSubscriptionResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	std::ostringstream os;
	os << "http://" << ctx->getServerIpFromClientIp(htonl(this->soap->ip)) << ":" << ctx->m_port;
	std::string url(os.str());
	
	time_t sec = time(NULL);
	tev__CreatePullPointSubscriptionResponse->SubscriptionReference.Address = strcpy((char*)soap_malloc(this->soap, url.size()+1), url.c_str());
	tev__CreatePullPointSubscriptionResponse->wsnt__CurrentTime = sec;
	tev__CreatePullPointSubscriptionResponse->wsnt__TerminationTime = sec+3600;
		
	return SOAP_OK;
}

int EventBindingService::GetEventProperties(_tev__GetEventProperties *tev__GetEventProperties, _tev__GetEventPropertiesResponse *tev__GetEventPropertiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

