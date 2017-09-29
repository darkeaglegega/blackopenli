require vuplus-initrd.inc

do_install() {
	install -d ${D}/boot
        install -m 0755 ${WORKDIR}/vmlinuz-initrd-7425b0 ${D}/boot/initrd_cfe_auto.bin
}

SRCDATE = "20130220"
SRC_URI[md5sum] = "90f22e35a63dca8591d2e21fef417377"
SRC_URI[sha256sum] = "48d612d8383113008569dd422a7cafa8d0f6b5c6e77772dd73f77724ede205c6"
