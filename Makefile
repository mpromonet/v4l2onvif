SYSROOT?=$(shell $(CXX) --print-sysroot)
PREFIX?=/usr
DESTDIR?=$(PREFIX)/bin
$(info PREFIX=$(PREFIX) SYSROOT=$(SYSROOT) DESTDIR=$(DESTDIR))

VERSION=$(shell git describe --tags --always --dirty)
$(info VERSION=$(VERSION))

GSOAP_PREFIX?=$(SYSROOT)/usr
GSOAP_BIN?=$(GSOAP_PREFIX)/bin
GSOAP_BASE=$(GSOAP_PREFIX)/share/gsoap
GSOAP_PLUGINS=$(GSOAP_BASE)/plugin

CXXFLAGS+=-std=c++11 -g -I inc -I ws-discovery/gsoap/
CXXFLAGS+=-I gen -I $(GSOAP_PREFIX)/include -I $(GSOAP_PLUGINS) 
CXXFLAGS+=-DWITH_OPENSSL -DSOAP_PURE_VIRTUAL -fpermissive -pthread -DVERSION=\"$(VERSION)\"
LDFLAGS+=-L $(GSOAP_PREFIX)/lib/ -lgsoapssl++ -lz -pthread -lssl -lcrypto -ldl -static-libstdc++

WSSE_SRC=$(GSOAP_PLUGINS)/wsseapi.c $(GSOAP_PLUGINS)/smdevp.c $(GSOAP_PLUGINS)/mecevp.c $(GSOAP_BASE)/custom/struct_timeval.c
WSSE_OBJ=$(WSSE_SRC:%.c=%.o)

SOAP_SRC=$(wildcard gen/soapC_*.cpp)
SOAP_OBJ=$(SOAP_SRC:%.cpp=%.o)

SERVER_OBJ=gen/soapDeviceBindingService.o gen/soapDeviceIOBindingService.o
SERVER_OBJ+=gen/soapMediaBindingService.o gen/soapImagingBindingService.o 
SERVER_OBJ+=gen/soapPTZBindingService.o
SERVER_OBJ+=gen/soapEventBindingService.o gen/soapPullPointSubscriptionBindingService.o gen/soapNotificationProducerBindingService.o gen/soapSubscriptionManagerBindingService.o
SERVER_OBJ+=gen/soapRecordingBindingService.o gen/soapReplayBindingService.o gen/soapSearchBindingService.o gen/soapReceiverBindingService.o 
SERVER_OBJ+=gen/soapDisplayBindingService.o

CLIENT_OBJ=gen/soapDeviceBindingProxy.o gen/soapDeviceIOBindingProxy.o
CLIENT_OBJ+=gen/soapMediaBindingProxy.o gen/soapImagingBindingProxy.o
CLIENT_OBJ+=gen/soapPTZBindingProxy.o
CLIENT_OBJ+=gen/soapEventBindingProxy.o gen/soapPullPointSubscriptionBindingProxy.o gen/soapNotificationProducerBindingProxy.o gen/soapSubscriptionManagerBindingProxy.o
CLIENT_OBJ+=gen/soapRecordingBindingProxy.o gen/soapReplayBindingProxy.o gen/soapReceiverBindingProxy.o gen/soapSearchBindingProxy.o 
CLIENT_OBJ+=gen/soapDisplayBindingProxy.o

all: gen/onvif.h libwsdd.a liblibv4l2rtspserver.a libv4l2wrapper.a onvif-server.exe onvif-client.exe

gen/onvif.h: $(wildcard wsdl/*) 
	mkdir -p gen
	$(GSOAP_BIN)/wsdl2h -P -d -Ntev -z6 -o $@ $^
	$(GSOAP_BIN)/soapcpp2 -2jx $@ -I $(GSOAP_BASE)/import -I $(GSOAP_BASE) -I inc -d gen -f1000 || :
	make

libserver.a: $(SERVER_OBJ) $(SOAP_OBJ) | gen/onvif.h
	$(AR) rcs $@ $^

libclient.a: $(CLIENT_OBJ) $(SOAP_OBJ) | gen/onvif.h
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
liblibv4l2rtspserver.a:
	git submodule update --recursive --init v4l2rtspserver
	cd v4l2rtspserver && cmake . && make libv4l2rtspserver		
	cp v4l2rtspserver/$@ .

# lib4l2cpp
libv4l2wrapper.a: 
	git submodule update --recursive --init v4l2rtspserver
	cd v4l2rtspserver && cmake . && make v4l2wrapper
	cp v4l2rtspserver/$@ .

LIVE = v4l2rtspserver/live
CXXFLAGS += -I ${LIVE}/groupsock/include -I ${LIVE}/liveMedia/include -I ${LIVE}/UsageEnvironment/include -I ${LIVE}/BasicUsageEnvironment/include
CXXFLAGS += -I v4l2rtspserver/inc -I v4l2rtspserver/v4l2wrapper/inc

onvif-server.exe: src/onvif-server.o src/onvif_impl.o $(WSSE_SRC) libserver.a libonvif.a gen/soapNotificationConsumerBindingProxy.o libwsdd.a liblibv4l2rtspserver.a libv4l2wrapper.a
	$(CXX) -g -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

onvif-client.exe: src/onvif-client.o $(WSSE_SRC) $(GSOAP_PLUGINS)/wsaapi.c libclient.a gen/soapNotificationConsumerBindingService.o libonvif.a
	$(CXX) -g -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

clean:
	make -C v4l2rtspserver clean || :
	make -C ws-discovery/gsoap clean || :
	rm -rf gen src/*.o *.a *.exe

install:
	mkdir -p $(DESTDIR)
	install -D -m 0755 onvif-server.exe $(DESTDIR)
	install -D -m 0755 onvif-client.exe $(DESTDIR)
