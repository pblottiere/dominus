FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " file://dominusd.service"

FILES:${PN} += "${sysconfdir}/systemd/system/dominusd.service"

do_install:append() {
  install -d ${D}/${sysconfdir}/systemd/system
  install -m 0644 ${WORKDIR}/dominusd.service ${D}/${sysconfdir}/systemd/system/
}
