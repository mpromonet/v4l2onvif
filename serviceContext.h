#ifndef SERVICE_CONTEXT_H
#define SERVICE_CONTEXT_H

struct ServiceContext
{
	ServiceContext(const std::string& wsdlurl, const std::string& ip, int port) : m_wsdlurl(wsdlurl), m_ip(ip), m_port(port) {};
	std::string m_wsdlurl;
	std::string m_ip;
	int         m_port;
};

#endif