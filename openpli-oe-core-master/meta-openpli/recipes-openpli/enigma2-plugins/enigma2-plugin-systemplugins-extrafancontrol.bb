DESCRIPTION = "Extra fan control - using HDD/SSD/CPU temp"
HOMEPAGE = "https://github.com/Dima73/enigma2-plugin-systemplugins-extrafancontrol"
LICENSE = "PD"
LIC_FILES_CHKSUM = "file://README;md5=8e3a3f140c512edb33d2e027096fd1cc"
SRC_URI = "git://github.com/Dima73/enigma2-plugin-systemplugins-extrafancontrol.git"
S = "${WORKDIR}/git"

inherit gitpkgv
SRCREV = "6e77b17108230342d72e68fd35b9f693fdb23d99"
PV = "1+git${SRCPV}"
PKGV = "1+git${GITPKGV}"

inherit allarch distutils-openplugins

RDEPENDS_${PN} = "hddtemp"
