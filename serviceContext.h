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
int getFormat(const char* device, int& width, int& height, int& format);
tt__VideoEncoderConfiguration* getVideoEncoderCfg(struct soap* soap, const char* device);

template<typename T>
T * soap_new_ptr(struct soap* soap, T value)
{
	T* ptr = (T*)soap_malloc(soap, sizeof(T));
	*ptr = value;
	return ptr;
}


#endif