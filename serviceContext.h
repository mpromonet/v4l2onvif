#ifndef SERVICE_CONTEXT_H
#define SERVICE_CONTEXT_H

struct ServiceContext
{
	ServiceContext(const std::string& wsdlurl, int port = 0) : m_wsdlurl(wsdlurl), m_port(port) {};
	std::string m_wsdlurl;
	int         m_port;
};

std::string getServerIpFromClientIp(int ip);

#endif