#! /bin/sh

# build image
docker build -t dominus/rpi3 .

# run container
docker run -d --name dominus_rpi3 -t dominus/rpi3 /bin/bash

# retrieve images
rm -f images.tar.gz
ID=$(docker inspect --format="{{.Id}}" dominus_rpi3)
docker cp $ID:/root/buildroot-2017.08/output/images.tar.gz images.tar.gz

# stop container
docker stop $ID
