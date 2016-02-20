GSOAP_PREFIX=/usr
GSOAP_BASE=$(GSOAP_PREFIX)/share/gsoap
GSOAP_IMPORT=$(GSOAP_BASE)/import
GSOAP_PLUGINS=$(GSOAP_BASE)/plugin
GSOAP_CFLAGS=-I gen -I $(GSOAP_PREFIX)/include -I $(GSOAP_PLUGINS) -DSOAP_PURE_VIRTUAL -DWITH_OPENSSL -fpermissive 
GSOAP_LDFLAGS=-L $(GSOAP_PREFIX)/lib/ -lgsoapssl++ -lssl -lcrypto -lz 

CXXFLAGS+=$(GSOAP_CFLAGS) -std=c++11

WSSE_SRC=$(GSOAP_PLUGINS)/wsseapi.c $(GSOAP_PLUGINS)/smdevp.c $(GSOAP_PLUGINS)/mecevp.c $(GSOAP_PLUGINS)/wsaapi.c

SOAP_SRC=$(wildcard gen/soapC_*.cpp)
SOAP_OBJ=$(SOAP_SRC:%.cpp=%.o)

SERVER_OBJ=gen/soapDeviceBindingService.o gen/soapDeviceIOBindingService.o
SERVER_OBJ+=gen/soapMediaBindingService.o gen/soapImagingBindingService.o 
SERVER_OBJ+=gen/soapEventBindingService.o gen/soapPullPointSubscriptionBindingService.o 
SERVER_OBJ+=gen/soapRecordingBindingService.o gen/soapReplayBindingService.o gen/soapSearchBindingService.o gen/soapReceiverBindingService.o 
SERVER_OBJ+=gen/soapDisplayBindingService.o

CLIENT_OBJ=gen/soapDeviceBindingProxy.o gen/soapDeviceIOBindingProxy.o
CLIENT_OBJ+=gen/soapMediaBindingProxy.o gen/soapImagingBindingProxy.o
CLIENT_OBJ+=gen/soapEventBindingProxy.o gen/soapPullPointSubscriptionBindingProxy.o 
CLIENT_OBJ+=gen/soapRecordingBindingProxy.o gen/soapReplayBindingProxy.o gen/soapReceiverBindingProxy.o gen/soapSearchBindingProxy.o 
CLIENT_OBJ+=gen/soapDisplayBindingProxy.o

all: gen server.exe client.exe

gen:
	mkdir gen
	
gen/onvif.h: devicemgmt.wsdl media.wsdl recording.wsdl replay.wsdl receiver.wsdl search.wsdl event.wsdl imaging.wsdl display.wsdl deviceio.wsdl onvif.xsd b-2.xsd include bf-2.xsd t-1.xsd 
	$(GSOAP_PREFIX)/bin/wsdl2h -d -Ntev -z6 -o $@ $^

gen/soapDeviceBindingService.cpp: gen/onvif.h
	$(GSOAP_PREFIX)/bin/soapcpp2 -2jx $^ -I $(GSOAP_IMPORT) -d gen -f250 

libsoap.a: $(SOAP_OBJ)
	ar rcs $@ $^

libserver.a: $(SERVER_OBJ) 
	ar rcs $@ $^

libclient.a: $(CLIENT_OBJ) 
	ar rcs $@ $^

server.exe: $(SOAP_OBJ) $(SERVER_OBJ) serverDevice.o serverMedia.o serverRecording.o serverReplay.o serverEvent.o serverPullPointSubscription.o serverReceiver.o  serverImaging.o serverSearch.o serverDisplay.o serverDeviceIO.o  server.o onvif_impl.o $(WSSE_SRC)
	$(CXX) -g -o $@ $^ $(GSOAP_LDFLAGS) $(GSOAP_CFLAGS)

client.exe: $(SOAP_OBJ) $(CLIENT_OBJ) client.o $(WSSE_SRC)
	$(CXX) -g -o $@ $^ $(GSOAP_LDFLAGS) $(GSOAP_CFLAGS)

clean:
	rm -rf gen *.o

