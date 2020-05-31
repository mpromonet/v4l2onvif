GSOAP_PREFIX=/usr
GSOAP_BASE=$(GSOAP_PREFIX)/share/gsoap
GSOAP_IMPORT=$(GSOAP_BASE)/import
GSOAP_PLUGINS=$(GSOAP_BASE)/plugin
GSOAP_CFLAGS=-I gen -I $(GSOAP_PREFIX)/include -I $(GSOAP_PLUGINS) -DSOAP_PURE_VIRTUAL -fpermissive -pthread
GSOAP_LDFLAGS=-L $(GSOAP_PREFIX)/lib/ -lgsoapssl++ -lz  -pthread

PREFIX?=/usr
SYSROOT?=$(shell $(CXX) --print-sysroot)
$(info SYSROOT=$(SYSROOT))
ifneq ($(wildcard $(SYSROOT)$(PREFIX)/include/openssl/bio.h),)
$(info WITH_OPENSSL)
GSOAP_CFLAGS+=-DWITH_OPENSSL
GSOAP_LDFLAGS+=-lssl -lcrypto
endif

CXXFLAGS+=$(GSOAP_CFLAGS) -std=c++11 -g -Iinc -I ws-discovery/gsoap/

WSSE_SRC=$(GSOAP_PLUGINS)/wsseapi.c $(GSOAP_PLUGINS)/smdevp.c $(GSOAP_PLUGINS)/mecevp.c

SOAP_SRC=$(wildcard gen/soapC_*.cpp)
SOAP_OBJ=$(SOAP_SRC:%.cpp=%.o)

SERVER_OBJ=gen/soapDeviceBindingService.o gen/soapDeviceIOBindingService.o
SERVER_OBJ+=gen/soapMediaBindingService.o gen/soapImagingBindingService.o 
SERVER_OBJ+=gen/soapPTZBindingService.o
SERVER_OBJ+=gen/soapEventBindingService.o gen/soapPullPointSubscriptionBindingService.o gen/soapNotificationProducerBindingService.o gen/soapSubscriptionManagerBindingService.o
SERVER_OBJ+=gen/soapNotificationConsumerBindingProxy.o
SERVER_OBJ+=gen/soapRecordingBindingService.o gen/soapReplayBindingService.o gen/soapSearchBindingService.o gen/soapReceiverBindingService.o 
SERVER_OBJ+=gen/soapDisplayBindingService.o

CLIENT_OBJ=gen/soapDeviceBindingProxy.o gen/soapDeviceIOBindingProxy.o
CLIENT_OBJ+=gen/soapMediaBindingProxy.o gen/soapImagingBindingProxy.o
CLIENT_OBJ+=gen/soapPTZBindingProxy.o
CLIENT_OBJ+=gen/soapEventBindingProxy.o gen/soapPullPointSubscriptionBindingProxy.o gen/soapNotificationProducerBindingProxy.o gen/soapSubscriptionManagerBindingProxy.o
CLIENT_OBJ+=gen/soapNotificationConsumerBindingService.o
CLIENT_OBJ+=gen/soapRecordingBindingProxy.o gen/soapReplayBindingProxy.o gen/soapReceiverBindingProxy.o gen/soapSearchBindingProxy.o 
CLIENT_OBJ+=gen/soapDisplayBindingProxy.o

all: gen/onvif.h onvif-server.exe onvif-client.exe

gen/onvif.h: $(wildcard wsdl/*) | libwsdd.a
	mkdir -p gen
	$(GSOAP_PREFIX)/bin/wsdl2h -d -Ntev -z6 -o $@ $^
	$(GSOAP_PREFIX)/bin/soapcpp2 -2jx $@ -I $(GSOAP_IMPORT) -d gen -f250 || :
	make

libsoap.a: $(SOAP_OBJ) | gen/onvif.h
	$(AR) rcs $@ $^

libserver.a: $(SERVER_OBJ) | gen/onvif.h
	$(AR) rcs $@ $^

libclient.a: $(CLIENT_OBJ) | gen/onvif.h
	$(AR) rcs $@ $^

ONVIF_SRC=$(wildcard src/server*.cpp)
libonvif.a: $(ONVIF_SRC:%.cpp=%.o)
	$(AR) rcs $@ $^

# ws-discovery
libwsdd.a:
	git submodule init ws-discovery
	git submodule update ws-discovery
	make -C ws-discovery/gsoap libwsdd.a
	cp ws-discovery/gsoap/libwsdd.a .

# v4l2rtsp
v4l2rtspserver/CMakeList.txt:
	git submodule update --recursive --init v4l2rtspserver

liblibv4l2rtspserver.a: v4l2rtspserver/CMakeList.txt
	cd v4l2rtspserver && cmake . && make libv4l2rtspserver		
	cp v4l2rtspserver/$@ .

libv4l2wrapper.a: v4l2rtspserver/CMakeList.txt
	cd v4l2rtspserver && cmake . && make v4l2wrapper
	cp v4l2rtspserver/$@ .

LIVE = v4l2rtspserver/live
CXXFLAGS += -I ${LIVE}/groupsock/include -I ${LIVE}/liveMedia/include -I ${LIVE}/UsageEnvironment/include -I ${LIVE}/BasicUsageEnvironment/include
CXXFLAGS += -I v4l2rtspserver/inc -I v4l2rtspserver/v4l2wrapper/inc

onvif-server.exe: src/onvif-server.o src/onvif_impl.o $(WSSE_SRC) libserver.a libonvif.a gen/soapNotificationConsumerBindingProxy.o libsoap.a libwsdd.a liblibv4l2rtspserver.a libv4l2wrapper.a
	$(CXX) -g -o $@ $^ $(GSOAP_LDFLAGS) $(GSOAP_CFLAGS) 

onvif-client.exe: src/onvif-client.o $(WSSE_SRC) $(GSOAP_PLUGINS)/wsaapi.c libclient.a libsoap.a libonvif.a
	$(CXX) -g -o $@ $^ $(GSOAP_LDFLAGS) $(GSOAP_CFLAGS) 

clean:
	rm -rf gen *.o *.a

install:
	cp *.exe /usr/local/bin
