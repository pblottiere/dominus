#! /bin/bash

VERSION=mickledore

cd /workdir
git clone --branch $VERSION git://git.yoctoproject.org/poky
cd poky
git clone --branch $VERSION git://git.yoctoproject.org/meta-raspberrypi
git clone --branch $VERSION https://github.com/openembedded/meta-openembedded
rm -rf meta-dominus
source ./oe-init-build-env
