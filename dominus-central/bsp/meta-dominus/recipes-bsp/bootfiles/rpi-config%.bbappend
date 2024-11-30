SUMMARY = "Append to meta-raspberrypi/recipes-bsp/bootfiles/rpi-config_git.bb"

do_deploy:append() {
    CONFIG=${DEPLOYDIR}/bootfiles/config.txt
    echo "arm_64bit=1" >> $CONFIG
    echo "kernel=kernel8.img" >> $CONFIG
}
