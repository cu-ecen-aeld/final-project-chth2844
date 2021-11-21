
# This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "git://git@github.com/cu-ecen-aeld/final-project-chth2844.git;protocol=ssh;branch=main"
PV = "1.0+git${SRCPV}"
SRCREV = "8a29311dce085589afff6e2bf5383d462e4e7b86"


S = "${WORKDIR}/git"

#inherit autotools

FILES_${PN} += "${bindir}/server"
# TODO: customize these as necessary for any libraries you need for your application
TARGET_LDFLAGS += "-pthread -lrt"



do_configure () {
	:
}

do_compile () {
	oe_runmake
}

do_install () {
	install -d ${D}${bindir}
	install -m 0755 ${S}/server ${D}${bindir}/	


}

# The autotools configuration I am basing this on seems to have a problem with a race condition when parallel make is enabled
PARALLEL_MAKE = ""
