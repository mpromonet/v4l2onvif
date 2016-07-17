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
 serverNotificationConsumer.cpp
 
 bw-2.wsdl server
----------------------------------------------------------------------------- */

#include "soapNotificationConsumerBindingService.h"
#include "onvif_impl.h"


int NotificationConsumerBindingService::Notify(_wsnt__Notify *wsnt__Notify) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	for (auto msg : wsnt__Notify->NotificationMessage)
	{
		std::cout << "\tMessage:" << msg->Message.__any << std::endl;
	}
	
	return SOAP_OK;
}
