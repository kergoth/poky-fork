DESCRIPTION = "Sato Icon Theme"
HOMEPAGE = "http://www.o-hand.com"
BUGTRACKER = "http://bugzilla.openedhand.com/"

LICENSE = "CCPL"
LIC_FILES_CHKSUM = "file://COPYING;md5=56a830bbe6e4697fe6cbbae01bb7c2b2"

SECTION = "x11"
DEPENDS = ""

inherit autotools pkgconfig

FILES_${PN} += "${datadir}"

PACKAGE_ARCH = "all"

EXTRA_OECONF += "--with-iconmap=${STAGING_LIBDIR_NATIVE}/../libexec/icon-name-mapping"

pkg_postinst_${PN} () {
        if [ "x$D" != "x" ]; then
                exit 1
        fi
        gtk-update-icon-cache -q /usr/share/icons/Sato
}
