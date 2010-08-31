SECTION = "base"
DESCRIPTION = "PM hooks"
LICENSE="GPL"

PR = "r0"

SRC_URI = "http://pm-utils.freedesktop.org/releases/pm-utils-${PV}.tar.gz"

inherit pkgconfig autotools

FILES_${PN}-dbg += "${libdir}/pm-utils/bin/.debug \
		    ${datadir}/doc/pm-utils/README.debugging"

do_configure_prepend () {
	autoreconf -f -i -s
}