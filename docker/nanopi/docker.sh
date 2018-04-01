#! /bin/sh

IMAGE="dominus/nanopi"
ROOTFS="/root/buildroot-2017.11.2/output/images/rootfs.tar"
QEMU_DIR="/tmp/dominus-qemu"
QEMU_CMD="mkdir -p $QEMU_DIR/usr/bin; \
	  mkdir -p $QEMU_DIR/usr/lib; \
	  mkdir -p $QEMU_DIR/etc; \
	  cp -r /src/install/bin/* $QEMU_DIR/usr/bin/; \
	  cp -r /src/install/lib/* $QEMU_DIR/usr/lib/; \
	  cp -r /src/install/etc/* $QEMU_DIR/etc/; \
	  chmod a+x $QEMU_DIR/etc/init.d/S101dominus; \
	  ./scripts/qemu_up.sh $ROOTFS $QEMU_DIR"

id() {
  local id=$(docker inspect --format="{{.Id}}" $IMAGE)
  echo "$id"
}

case "$1" in
  build)
    docker build . -t $IMAGE
  ;;

  img)
    docker run -d -v $PWD/../..:/src -w /src --name dominus-bsp -it $(id) /bin/bash > /dev/null 2>&1
    docker cp dominus-bsp:/root/buildroot-2017.11.2/output/images/sdcard.img .
    docker stop dominus-bsp > /dev/null 2>&1
    docker rm dominus-bsp > /dev/null 2>&1
    echo "Image: sdcard.img"
  ;;

  configure)
    docker run --rm -v $PWD/../..:/src -w /src -it $(id) ./autogen.sh
    docker run --rm -v $PWD/../..:/src -w /src -it $(id) ./configure --host=arm-linux --prefix=/src/install --enable-wiringpi
  ;;

  make)
    docker run --rm -v $PWD/../..:/src -w /src -it $(id) make
  ;;

  install)
    docker run --rm -v $PWD/../..:/src -w /src -it $(id) make install
  ;;

  qemu)
    docker run --rm --privileged -v $PWD/../..:/src -w /src -it $(id) /bin/bash -c "$QEMU_CMD"
  ;;

  clean)
    docker run --rm -v $PWD/../..:/src -w /src -it $(id) make maintainer-clean
  ;;

  connect)
    docker run --rm -v $PWD/../..:/src -w /src -it $(id) /bin/bash
  ;;

  rm)
    docker rmi $(id)
  ;;

  *)
    echo "Usage: docker.sh [OPTIONS]:"
    echo ""
    echo "Options:"
    echo ""
    echo "  img                 Copy the sdcard image from the container to the host"
    echo "  build               Build the BSP in a Docker image"
    echo "  rm                  Remove the underlying Docker image"
    echo "  connect             Create an interactive bash within a Docker container"
    echo "  configure           Run the configure script using the cross-compiler"
    echo "  install             Install cross-compiled application in a sub-directory"
    echo "  clean               Clean generated files"
    echo "  make                Cross-compile the application"
    echo "  qemu                Run QEMU with the built in RFS"
  ;;
esac

exit 0
