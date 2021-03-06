DESCRIPTION = "Linux kernel for ${MACHINE}"
LICENSE = "GPL"
SECTION = "kernel"
KV = "3.13.5"
PR_INC = ".6"

SRC_URI[md5sum] = "19e9956653437b99b4fa6ec3e16a3e99"
SRC_URI[sha256sum] = "ef7fb307582ff243aacff8a13025fe028634aaf650ada309991ae03622962f61"

LIC_FILES_CHKSUM = "file://${WORKDIR}/linux/COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

FILESEXTRAPATHS_prepend := "${THISDIR}/linux-vuplus-${KV}:"

KERNEL_CONFIG = "${@bb.utils.contains("MACHINE_FEATURES", "dvbproxy", "${MACHINE}_defconfig_proxy", "${MACHINE}_defconfig", d)}"

SRC_URI += "http://archive.vuplus.com/download/kernel/stblinux-${KV}.tar.bz2 \
	file://nfs-max-rwsize-8k.patch \
	file://rt2800usb_fix_warn_tx_status_timeout_to_dbg.patch \
	file://linux-tcp_output.patch \
	file://linux-3.13-gcc-4.9.3-build-error-fixed.patch \
	file://kernel-add-support-for-gcc-5.patch \
	file://kernel-add-support-for-gcc-6.patch \
	file://rtl8712-fix-warnings.patch \
	file://0001-Support-TBS-USB-drivers-3.13.patch \
	file://0001-STV-Add-PLS-support.patch \
	file://0001-STV-Add-SNR-Signal-report-parameters.patch \
	file://0001-stv090x-optimized-TS-sync-control.patch \
	${@bb.utils.contains("MACHINE_FEATURES", "dvbproxy", "file://linux_dvb_adapter.patch", "", d)} \
	file://${KERNEL_CONFIG} \
	"

inherit kernel machine_kernel_pr

S = "${WORKDIR}/linux"

export OS = "Linux"
KERNEL_IMAGETYPE = "vmlinux"
KERNEL_OUTPUT = "vmlinux"
KERNEL_OBJECT_SUFFIX = "ko"
KERNEL_IMAGEDEST = "tmp"
KERNEL_OUTPUT_DIR = "."

FILES_kernel-image = "/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}.gz"
FILES_kernel-image-dev = "/${KERNEL_IMAGEDEST}"

do_configure_prepend() {
	oe_machinstall -m 0644 ${WORKDIR}/${KERNEL_CONFIG} ${WORKDIR}/defconfig
}

kernel_do_install_append() {
	install -d ${D}/${KERNEL_IMAGEDEST}
	install -m 0755 ${KERNEL_OUTPUT} ${D}/${KERNEL_IMAGEDEST}
	gzip ${D}/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}
}

pkg_postinst_kernel-image () {
	if [ -d /proc/stb ] ; then
		flash_eraseall /dev/mtd2
		nandwrite -p /dev/mtd2 /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}.gz
	fi
	rm -f /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}.gz
	true
}
