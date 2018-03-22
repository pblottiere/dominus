FROM debian:stable

# Buildroot deps
RUN apt-get update && apt-get install -y \
	bc \
	bzip2 \
	cpio \
	file \
	gcc \
	g++ \
	git \
	gzip \
	make \
	ncurses-dev \
	python \
	unzip \
	wget \
	autotools-dev \
	automake \
	libtool

# QEMU deps
RUN apt-get install -y \
	qemu-user-static

WORKDIR /root

RUN wget https://buildroot.org/downloads/buildroot-2017.11.2.tar.gz
RUN tar zxvf buildroot-2017.11.2.tar.gz

WORKDIR /root/buildroot-2017.11.2

RUN mkdir -p patches/linux
COPY patches/enable-sun8i-emac-on-the-nanopi-neo.patch patches/linux/
COPY patches/sun8i-emac-thermal-cpufreq.patch.disable patches/linux/
COPY patches/v4-01-10-ethernet-add-sun8i-emac-driver.patch patches/linux/
COPY patches/v4-04-10-ARM-dts-sun8i-h3-Add-dt-node-for-the-syscon-control-module.patch patches/linux/
COPY patches/v4-05-10-ARM-dts-sun8i-h3-add-sun8i-emac-ethernet-driver.patch patches/linux/

COPY users.tables /root/buildroot-2017.11.2/users.tables
COPY defconfig /root/buildroot-2017.11.2/configs/dominus_defconfig
COPY linux_defconfig /root/buildroot-2017.11.2/dominus_linux_defconfig

RUN git config --global http.postBuffer 1048576000
RUN make dominus_defconfig
RUN make

ENV PATH="/root/buildroot-2017.11.2/output/host/bin:${PATH}"

RUN mkdir /src

CMD ["/bin/bash"]
