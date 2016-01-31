GSOAP_PREFIX=/usr
GSOAP_BASE=$(GSOAP_PREFIX)/share/gsoap
GSOAP_IMPORT=$(GSOAP_BASE)/import
GSOAP_PLUGINS=$(GSOAP_BASE)/plugin
GSOAP_CFLAGS= -I gen -I $(GSOAP_PREFIX)/include -I $(GSOAP_PLUGINS) -DSOAP_PURE_VIRTUAL
GSOAP_LDFLAGS= -lgsoap++ -L $(GSOAP_PREFIX)/lib/

CXXFLAGS+=$(GSOAP_CFLAGS) -std=c++11 -pthread

all: gen server.exe client.exe

SOAP_SRC=$(wildcard gen/soapC_*.cpp)
SOAP_OBJ=$(SOAP_SRC:%.cpp=%.o)

server.exe: $(SOAP_OBJ) gen/soapDeviceBindingService.o serverDevice.o gen/soapMediaBindingService.o serverMedia.o gen/soapRecordingBindingService.o serverRecording.o gen/soapReplayBindingService.o serverReplay.o server.o   
	$(CXX) -g -o $@ $^ $(GSOAP_LDFLAGS) -pthread

client.exe: $(SOAP_OBJ) gen/soapDeviceBindingProxy.o gen/soapMediaBindingProxy.o gen/soapRecordingBindingProxy.o gen/soapReplayBindingProxy.o client.o 
	$(CXX) -g -o $@ $^ $(GSOAP_LDFLAGS)

gen:
	mkdir gen

gen/onvif.h: 
	wsdl2h devicemgmt.wsdl media.wsdl recording.wsdl replay.wsdl onvif.xsd b-2.xsd include bf-2.xsd t-1.xsd -o $@ 

gen/soapDeviceBindingService.cpp: gen/onvif.h
	soapcpp2 -2ix $^ -I $(GSOAP_IMPORT) -d gen -f500

clean:
	rm -rf gen *.o

