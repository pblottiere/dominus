#! /bin/sh

IMAGE="dominus/rpi3"
ROOTFS="/root/buildroot-2017.08/output/images/rootfs.tar"
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

  configure)
    docker run --rm -v $PWD/../..:/src -w /src -it $(id) ./autogen.sh
    docker run --rm -v $PWD/../..:/src -w /src -it $(id) ./configure --host=arm-linux --prefix=/src/install
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

  maintainer-clean)
    docker run --rm -v $PWD/../..:/src -w /src -it $(id) make maintainer-clean
  ;;

  connect)
    docker run --rm -v $PWD/../..:/src -w /src -it $(id) /bin/bash
  ;;

  clean)
    docker rmi $(id)
  ;;
esac

exit 0
