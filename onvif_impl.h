/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** onvif_impl.h
** 
** onvif callbacks
**
** -------------------------------------------------------------------------*/

#ifndef SERVICE_CONTEXT_H
#define SERVICE_CONTEXT_H

#include <map>

#include "soapH.h"

class ServiceContext
{
public:
	std::string getServerIpFromClientIp(int ip);
	
	// V4L2 access
	int getFormat(const std::string &device, int& width, int& height, int& format);
	int getCtrlValue(const std::string &device, int idctrl);
	void setCtrlValue(const std::string &device, int idctrl, int value);
	std::pair<int,int> getCtrlRange(const std::string &device, int idctrl);
	void getIdentification(const std::string &device, std::string & card, std::string & driver, std::string & bus);

	// service capabilities
	tds__DeviceServiceCapabilities* getDeviceServiceCapabilities(struct soap* soap);
	trt__Capabilities*  getMediaServiceCapabilities    (struct soap* soap);
	timg__Capabilities* getImagingServiceCapabilities  (struct soap* soap);
	trc__Capabilities*  getRecordingServiceCapabilities(struct soap* soap);
	tse__Capabilities*  getSearchServiceCapabilities   (struct soap* soap);
	trv__Capabilities*  getReceiverServiceCapabilities (struct soap* soap);
	trp__Capabilities*  getReplayServiceCapabilities   (struct soap* soap);
	tev__Capabilities*  getEventServiceCapabilities    (struct soap* soap);

	// device
	tds__StorageConfiguration* getStorageCfg(struct soap* soap, const std::string & path);

	// media 
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
	std::string m_rtspport;
	int         m_port;
	std::string m_user;
	std::string m_password;
};

template<typename T>
T * soap_new_ptr(struct soap* soap, T value)
{
	T* ptr = (T*)soap_malloc(soap, sizeof(T));
	*ptr = value;
	return ptr;
}


#endif