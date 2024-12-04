FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " file://dominusd.service"
SRC_URI += " file://christmas0.wav"

FILES:${PN} += "${sysconfdir}/systemd/system/dominusd.service"
FILES:${PN} += "${datadir}/dominus/christmas0.wav"

do_install:append() {
  install -d ${D}/${sysconfdir}/systemd/system
  install -m 0644 ${WORKDIR}/dominusd.service ${D}/${sysconfdir}/systemd/system/

  install -d ${D}/${datadir}/dominus/
  install -m 0644 ${WORKDIR}/christmas0.wav ${D}/${datadir}/dominus/
}
