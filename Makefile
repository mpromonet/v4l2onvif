GSOAP_PREFIX=/usr
GSOAP_BASE=$(GSOAP_PREFIX)/share/gsoap
GSOAP_IMPORT=$(GSOAP_BASE)/import
GSOAP_PLUGINS=$(GSOAP_BASE)/plugin
GSOAP_CFLAGS= -I gen -I $(GSOAP_PREFIX)/include -I $(GSOAP_PLUGINS)
GSOAP_LDFLAGS= -lgsoap++ -L $(GSOAP_PREFIX)/lib/

all: server.exe client.exe

server.exe: gen/soapC.o gen/soapDeviceBindingService.o server.o
	$(CXX) -g -o $@ $^ $(GSOAP_LDFLAGS) $(GSOAP_CFLAGS) 

client.exe: gen/soapC.o gen/soapDeviceBindingProxy.o client.o
	$(CXX) -g -o $@ $^ $(GSOAP_LDFLAGS) $(GSOAP_CFLAGS) 

gen:
	mkdir gen

gen/onvif.h: gen
	wsdl2h devicemgmt.wsdl media.wsdl onvif.xsd b-2.xsd include bf-2.xsd t-1.xsd -o $@ 

gen/soapC.cpp: gen/onvif.h

	soapcpp2 -2ix $^ -I $(GSOAP_IMPORT) -d gen 

clean:
	rm -rf gen *.o

