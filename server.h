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

std::string getServerIpFromClientIp(int ip);

int getFormat(const std::string &device, int& width, int& height, int& format);
int getCtrlValue(const std::string &device, int idctrl);
std::pair<int,int> getCtrlRange(const std::string &device, int idctrl);

tt__VideoEncoderConfiguration* getVideoEncoderCfg(struct soap* soap, const char* device);
tt__VideoSourceConfiguration* getVideoSourceCfg(struct soap* soap, const std::string &token);

tds__DeviceServiceCapabilities* getDeviceServiceCapabilities(struct soap* soap);
trt__Capabilities* getMediaServiceCapabilities(struct soap* soap);
timg__Capabilities* getImagingServiceCapabilities(struct soap* soap);

template<typename T>
T * soap_new_ptr(struct soap* soap, T value)
{
	T* ptr = (T*)soap_malloc(soap, sizeof(T));
	*ptr = value;
	return ptr;
}


#endif