GSOAP_PREFIX=/usr
GSOAP_BASE=$(GSOAP_PREFIX)/share/gsoap
GSOAP_IMPORT=$(GSOAP_BASE)/import
GSOAP_PLUGINS=$(GSOAP_BASE)/plugin
GSOAP_CFLAGS=-I gen -I $(GSOAP_PREFIX)/include -I $(GSOAP_PLUGINS) -DSOAP_PURE_VIRTUAL -DWITH_OPENSSL -fpermissive 
GSOAP_LDFLAGS=-L $(GSOAP_PREFIX)/lib/ -lgsoapssl++ -lssl -lcrypto -lz 
GSOAP_WSSE=$(GSOAP_PLUGINS)/wsseapi.c $(GSOAP_PLUGINS)/smdevp.c $(GSOAP_PLUGINS)/mecevp.c $(GSOAP_PLUGINS)/wsaapi.c

CXXFLAGS+=$(GSOAP_CFLAGS) -std=c++11

SOAP_SRC=$(wildcard gen/soapC_*.cpp)
SOAP_OBJ=$(SOAP_SRC:%.cpp=%.o)

all: gen server.exe client.exe

gen:
	mkdir gen
	
gen/onvif.h: 
	$(GSOAP_PREFIX)/bin/wsdl2h -d -Ntev -z6 devicemgmt.wsdl media.wsdl recording.wsdl replay.wsdl receiver.wsdl event.wsdl imaging.wsdl onvif.xsd b-2.xsd include bf-2.xsd t-1.xsd bw-2.wsdl -o $@.tmp 
	echo '#import "wsse.h"' > $@
	cat $@.tmp >> $@

gen/soapDeviceBindingService.cpp: gen/onvif.h
	$(GSOAP_PREFIX)/bin/soapcpp2 -2jx $^ -I $(GSOAP_IMPORT) -d gen -f250 

server.exe: $(SOAP_OBJ) gen/soapDeviceBindingService.o serverDevice.o gen/soapMediaBindingService.o serverMedia.o gen/soapRecordingBindingService.o serverRecording.o gen/soapReplayBindingService.o serverReplay.o gen/soapEventBindingService.o serverEvent.o gen/soapPullPointSubscriptionBindingService.o serverPullPointSubscription.o gen/soapReceiverBindingService.o serverReceiver.o  gen/soapImagingBindingService.o serverImaging.o $(GSOAP_WSSE) server.o   
	$(CXX) -g -o $@ $^ $(GSOAP_LDFLAGS) $(GSOAP_CFLAGS)

client.exe: $(SOAP_OBJ) gen/soapDeviceBindingProxy.o gen/soapMediaBindingProxy.o gen/soapRecordingBindingProxy.o gen/soapReplayBindingProxy.o gen/soapEventBindingProxy.o gen/soapPullPointSubscriptionBindingProxy.o gen/soapReceiverBindingProxy.o gen/soapImagingBindingProxy.o $(GSOAP_WSSE) client.o 
	$(CXX) -g -o $@ $^ $(GSOAP_LDFLAGS) $(GSOAP_CFLAGS)

clean:
	rm -rf gen *.o

