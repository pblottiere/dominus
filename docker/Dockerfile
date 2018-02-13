FROM debian:stable

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
	wget

WORKDIR /root

RUN wget https://buildroot.org/downloads/buildroot-2017.08.tar.gz
RUN tar zxvf buildroot-2017.08.tar.gz

WORKDIR /root/buildroot-2017.08

COPY users.tables /root/buildroot-2017.08/users.tables
COPY defconfig /root/buildroot-2017.08/configs/dominus_defconfig

RUN git config --global http.postBuffer 1048576000
RUN make dominus_defconfig
RUN make

RUN cd output && tar zcvf images.tar.gz images

CMD ["/bin/bash"]
