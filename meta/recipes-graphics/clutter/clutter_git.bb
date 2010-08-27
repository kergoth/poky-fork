require clutter.inc
require clutter-package.inc

PV = "1.0.0+git${SRCPV}"
PR = "r8"

SRC_URI = "git://git.clutter-project.org/clutter.git;protocol=git;branch=master \
           file://enable_tests-654c26a1301c9bc5f8e3e5e3b68af5eb1b2e0673.patch;patch=1;rev=654c26a1301c9bc5f8e3e5e3b68af5eb1b2e0673 \
           file://enable_tests.patch;patch=1;notrev=654c26a1301c9bc5f8e3e5e3b68af5eb1b2e0673 "
S = "${WORKDIR}/git"

BASE_CONF += "--disable-introspection"

do_configure_prepend () {
	# Disable DOLT
	sed -i -e 's/^DOLT//' ${S}/configure.ac
}