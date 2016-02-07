#ifndef SERVICE_CONTEXT_H
#define SERVICE_CONTEXT_H

struct ServiceContext
{
	std::string m_wsdlurl;
	std::string m_rtspurl;
	std::string m_device;
	std::string m_rtspport;
	int         m_port;
};

std::string getServerIpFromClientIp(int ip);

#endif