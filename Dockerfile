# build
FROM ubuntu:22.04 as builder
LABEL maintainer=michel.promonet@free.fr

WORKDIR /v4l2onvif
COPY . /v4l2onvif

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends ca-certificates git g++ make cmake gsoap libgsoap-dev libssl-dev zlib1g-dev \
	&& make \
	&& make install \
	&& apt-get clean && rm -rf /var/lib/apt/lists/

# run
FROM ubuntu:22.04

WORKDIR /app
COPY --from=builder /usr/bin/ /app/


RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends ca-certificates libgsoap-2.8 libssl1.1 zlib1g \
    && ./onvif-server.exe -h


ENTRYPOINT [ "./onvif-server.exe" ]
