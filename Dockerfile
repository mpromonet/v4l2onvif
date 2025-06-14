# build
FROM debian:trixie AS builder
LABEL maintainer=michel.promonet@free.fr

WORKDIR /v4l2onvif
COPY . .

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends ca-certificates git g++ make cmake gsoap libgsoap-dev libssl-dev zlib1g-dev \
	&& make \
	&& make install \
	&& apt-get clean && rm -rf /var/lib/apt/lists/

# run
FROM debian:trixie

WORKDIR /app
COPY --from=builder /usr/bin/ /app/


RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends ca-certificates libgsoap-dev libssl-dev zlib1g-dev \
    && ./onvif-server.exe -h


ENTRYPOINT [ "./onvif-server.exe" ]
