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
 onvif_impl.h
 
 V4L2 implementation of ONVIF services
----------------------------------------------------------------------------- */

#ifndef SERVICE_CONTEXT_H
#define SERVICE_CONTEXT_H

#include <list>
#include <map>

#include "soapH.h"

class NotificationConsumerBindingProxy;

class ServiceContext
{
public:
	std::string getServerIpFromClientIp(int ip);
	
	// V4L2 access
	int                getFormat        (const std::string &device, int& width, int& height, int& format);
	int                getCtrlValue     (const std::string &device, int idctrl);
	void               setCtrlValue     (const std::string &device, int idctrl, int value);
	std::pair<int,int> getCtrlRange     (const std::string &device, int idctrl);
	void               getIdentification(const std::string &device, std::string & card, std::string & driver, std::string & bus);

	// service capabilities
	tds__DeviceServiceCapabilities* getDeviceServiceCapabilities(struct soap* soap);
	trt__Capabilities*  getMediaServiceCapabilities    (struct soap* soap);
	timg__Capabilities* getImagingServiceCapabilities  (struct soap* soap);
	trc__Capabilities*  getRecordingServiceCapabilities(struct soap* soap);
	tse__Capabilities*  getSearchServiceCapabilities   (struct soap* soap);
	trv__Capabilities*  getReceiverServiceCapabilities (struct soap* soap);
	trp__Capabilities*  getReplayServiceCapabilities   (struct soap* soap);
	tev__Capabilities*  getEventServiceCapabilities    (struct soap* soap);
	tls__Capabilities*  getDisplayServiceCapabilities  (struct soap* soap);
	tmd__Capabilities*  getDeviceIOServiceCapabilities (struct soap* soap);

	// device
	tds__StorageConfiguration* getStorageCfg(struct soap* soap, const std::string & path);

	// media 
	tt__Profile*                          getProfile               (struct soap* soap, const std::string & token);
	tt__VideoSourceConfiguration*         getVideoSourceCfg        (struct soap* soap, const std::string & token);
	tt__VideoSourceConfigurationOptions*  getVideoSourceCfgOptions (struct soap* soap, const std::string & token);
	tt__VideoEncoderConfiguration*        getVideoEncoderCfg       (struct soap* soap, const std::string & token);
	tt__VideoEncoderConfigurationOptions* getVideoEncoderCfgOptions(struct soap* soap, const std::string & token);

	// recording
	tt__RecordingJobConfiguration* getRecordingJobConfiguration(struct soap* soap, const std::string & token);
	tt__RecordingConfiguration*    getRecordingCfg(struct soap* soap);
	tt__TrackConfiguration*        getTracksCfg(struct soap* soap);
	
public:
	std::map<std::string,std::string> m_devices;
	std::string m_outdevice;
	int         m_port;
	std::string m_user;
	std::string m_password;
	std::string Manufacturer;
	std::string Model;
	std::string FirmwareVersion;
	std::list<NotificationConsumerBindingProxy*> m_subscriber;
};

template<typename T>
T * soap_new_ptr(struct soap* soap, T value)
{
	T* ptr = (T*)soap_malloc(soap, sizeof(T));
	*ptr = value;
	return ptr;
}


#endif
