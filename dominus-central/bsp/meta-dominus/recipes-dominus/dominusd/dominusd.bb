SUMMARY = "dominus"
LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

inherit systemd

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI = "file://dominusd.py"

BB_STRICT_CHECKSUM = "0"

FILES:${PN} += "${bindir}/dominusd.py"

do_install () {
    install -d ${D}/${bindir}/
    install -m 0755 ${WORKDIR}/dominusd.py ${D}${bindir}/
}

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE:${PN} = "dominusd.service"
