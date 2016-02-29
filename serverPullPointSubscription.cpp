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
 serverPullPointSubscription.cpp
 
 bw-2.wsdl server
----------------------------------------------------------------------------- */

#include <sstream>

#include "soapPullPointSubscriptionBindingService.h"
#include "onvif_impl.h"


int PullPointSubscriptionBindingService::PullMessages(_tev__PullMessages *tev__PullMessages, _tev__PullMessagesResponse *tev__PullMessagesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	for (int i=0; i<10; i++)
	{
		std::ostringstream os;
		os << "msg:" << i;
		std::string msg(os.str());
		tev__PullMessagesResponse->wsnt__NotificationMessage.push_back(soap_new_wsnt__NotificationMessageHolderType(this->soap));
		tev__PullMessagesResponse->wsnt__NotificationMessage.back()->Message.__any = soap_dom_element(this->soap, (char*)NULL, (char*)NULL, msg.c_str());
	}
	return SOAP_OK;
}

int PullPointSubscriptionBindingService::Seek(_tev__Seek *tev__Seek, _tev__SeekResponse *tev__SeekResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int PullPointSubscriptionBindingService::SetSynchronizationPoint(_tev__SetSynchronizationPoint *tev__SetSynchronizationPoint, _tev__SetSynchronizationPointResponse *tev__SetSynchronizationPointResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}
