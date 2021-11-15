
# This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "git://git@github.com/cu-ecen-aeld/final-project-chth2844.git;protocol=ssh;branch=main"
PV = "1.0+git${SRCPV}"
SRCREV = "3908718feb9bb37894dab92ed0aeaa3d096e1da0"


S = "${WORKDIR}/git"

#inherit autotools

FILES_${PN} += "${bindir}/uart"
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
	install -m 0755 ${S}/uart ${D}${bindir}/	


}

# The autotools configuration I am basing this on seems to have a problem with a race condition when parallel make is enabled
PARALLEL_MAKE = ""
