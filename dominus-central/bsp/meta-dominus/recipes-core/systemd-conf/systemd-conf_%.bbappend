FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " file://10-en.network"
FILES:${PN} += "${sysconfdir}/systemd/network/10-en.network"
FILES:${PN} += "${sysconfdir}/systemd/system.conf.d/system.conf"

do_install:append() {
  install -d ${D}/${sysconfdir}/systemd/network
  install -d ${D}/${sysconfdir}/systemd/system.conf.d
  install -m 0644 ${WORKDIR}/system.conf ${D}/${sysconfdir}/systemd/system.conf.d/
  install -m 0644 ${WORKDIR}/10-en.network ${D}/${sysconfdir}/systemd/network
}
