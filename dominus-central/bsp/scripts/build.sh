#! /bin/bash

cd /workdir/poky
source ./oe-init-build-env
rm -rf tmp/*
bitbake -k dominus-image
