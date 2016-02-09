#ifndef SERVICE_CONTEXT_H
#define SERVICE_CONTEXT_H

struct ServiceContext
{
	std::string m_wsdlurl;
	std::string m_rtspurl;
	std::string m_device;
	std::string m_rtspport;
	int         m_port;
	std::string m_user;
	std::string m_password;
};

std::string getServerIpFromClientIp(int ip);

template<typename T>
T * soap_new_ptr(struct soap* soap, T value)
{
	T* ptr = (T*)soap_malloc(soap, sizeof(T));
	*ptr = value;
	return ptr;
}


#endif