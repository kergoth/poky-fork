DESCRIPTION = "which - shows the full path of (shell) commands."
SECTION     = "libs"
LICENSE = "GPLv3+"
LIC_FILES_CHKSUM = "file://COPYING;md5=d32239bcb673463ab874e80d47fae504\
                    file://which.c;beginline=1;endline=17;md5=a9963693af2272e7a8df6f231164e7a2"
HOMEPAGE = "http://ftp.gnu.org/gnu/which/"
DEPENDS     = "cwautomacros-native"

inherit autotools update-alternatives

PR = "r1"

SRC_URI = "http://ftp.gnu.org/gnu/which/which-${PV}.tar.gz \
           file://remove-declaration.patch"

SRC_URI[md5sum] = "95be0501a466e515422cde4af46b2744"
SRC_URI[sha256sum] = "d417b65c650d88ad26a208293c1c6e3eb60d4b6d847f01ff8f66aca63e2857f8"

do_configure_prepend() {
	sed -i -e 's%@ACLOCAL_CWFLAGS@%-I ${STAGING_DIR_NATIVE}/usr/share/cwautomacros/m4%g' ${S}/Makefile.am ${S}/tilde/Makefile.am
}

do_install() {
	autotools_do_install
	mv ${D}${bindir}/which ${D}${bindir}/which.${PN}
}

ALTERNATIVE_NAME = "which"
ALTERNATIVE_PATH = "which.${PN}"
ALTERNATIVE_PRIORITY = "100"
