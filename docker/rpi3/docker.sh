#! /bin/sh

IMAGE="dominus/rpi3"

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
