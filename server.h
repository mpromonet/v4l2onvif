#ifndef SERVICE_CONTEXT_H
#define SERVICE_CONTEXT_H

#include <map>

struct ServiceContext
{
	std::string m_wsdlurl;
	std::map<std::string,std::string> m_devices;
	std::string m_rtspport;
	int         m_port;
	std::string m_user;
	std::string m_password;
};

// V4L2 access
std::string getServerIpFromClientIp(int ip);
int getFormat(const std::string &device, int& width, int& height, int& format);
int getCtrlValue(const std::string &device, int idctrl);
std::pair<int,int> getCtrlRange(const std::string &device, int idctrl);

// service capabilities
tds__DeviceServiceCapabilities* getDeviceServiceCapabilities(struct soap* soap);
trt__Capabilities*  getMediaServiceCapabilities(struct soap* soap);
timg__Capabilities* getImagingServiceCapabilities(struct soap* soap);
trc__Capabilities*  getRecordingServiceCapabilities(struct soap* soap);
tse__Capabilities*  getSearchServiceCapabilities(struct soap* soap);

// device
tds__StorageConfiguration* getStorageCfg(struct soap* soap, const std::string & path);

// media 
tt__VideoEncoderConfiguration* getVideoEncoderCfg(struct soap* soap, const std::string & device);
tt__VideoSourceConfiguration* getVideoSourceCfg(struct soap* soap, const std::string & token);
tt__VideoEncoderConfigurationOptions* getVideoEncoderCfgOptions(struct soap* soap, const std::string & device);

// recording
tt__RecordingJobConfiguration* getRecordingJobConfiguration(struct soap* soap, const std::string & token);
tt__RecordingConfiguration* getRecordingCfg(struct soap* soap);
tt__TrackConfiguration* getTracksCfg(struct soap* soap);


template<typename T>
T * soap_new_ptr(struct soap* soap, T value)
{
	T* ptr = (T*)soap_malloc(soap, sizeof(T));
	*ptr = value;
	return ptr;
}


#endif