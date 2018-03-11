#! /bin/sh

ROOTFS_TAR=$1
QEMU_DIR=$2

mkdir $QEMU_DIR > /dev/null 2>&1
cp $ROOTFS_TAR $QEMU_DIR
cd $QEMU_DIR
tar xf $ROOTFS_TAR
mount --bind /dev dev/
mount --bind /proc proc/
cp /usr/bin/qemu-arm-static usr/bin/
chroot . bin/busybox ash
