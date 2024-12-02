#! /bin/bash

VOLUME=dominus
WORKDIR="/workdir"
USER=pokyuser
CONTAINER=dominus-bsp

# clear previous image
rm -f dominus.sdimg

# init volume
docker volume create --name $VOLUME
docker run -it --rm -v $VOLUME:$WORKDIR busybox chown -R 1000:1000 $WORKDIR

# run container
docker run -d --rm -it --name=$CONTAINER -v $VOLUME:$WORKDIR crops/poky:ubuntu-20.04 --workdir=$WORKDIR
sleep 5

# clone poky
docker cp scripts/clone.sh $CONTAINER:$WORKDIR/
docker exec -u $USER -it $CONTAINER sh $WORKDIR/clone.sh

# copy config files
docker cp conf/local.conf $CONTAINER:$WORKDIR/poky/build/conf/
docker cp conf/bblayers.conf $CONTAINER:$WORKDIR/poky/build/conf/

# copy stormm-solar layer
docker cp meta-dominus $CONTAINER:$WORKDIR/poky/

# build
docker cp scripts/build.sh $CONTAINER:$WORKDIR/
docker exec -u $USER -it $CONTAINER sh $WORKDIR/build.sh

# copy image
docker cp -L $CONTAINER:$WORKDIR/poky/build/tmp/deploy/images/raspberrypi3-64/dominus-image-raspberrypi3-64.rpi-sdimg dominus.sdimg

# stop
# docker stop $CONTAINER
