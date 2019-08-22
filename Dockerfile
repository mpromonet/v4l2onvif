# build
FROM ubuntu:18.04 as builder
LABEL maintainer=michel.promonet@free.fr

WORKDIR /v4l2onvif
COPY . /v4l2onvif

RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates g++ make gsoap libgsoap-dev libssl-dev zlib1g-dev \
	&& ( make || make ) \
	&& make install \
	&& apt-get clean && rm -rf /var/lib/apt/lists/

# run
FROM ubuntu:18.04

WORKDIR /app
COPY --from=builder /usr/local/bin/ /app/


RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates libgsoap-2.8 libssl1.0 zlib1g \
    && ./onvif-server.exe -h


EXPOSE 8080

ENTRYPOINT [ "./onvif-server.exe" ]
