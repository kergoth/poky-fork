DESCRIPTION = "An open source implementation of the OpenGL spec"
HOMEPAGE = "http://mesa3d.org"
BUGTRACKER = "https://bugs.freedesktop.org"
SECTION = "x11"
LICENSE = "MIT"

SRC_URI = "ftp://ftp.freedesktop.org/pub/mesa/${PV}/MesaLib-${PV}.tar.bz2 \
           ftp://ftp.freedesktop.org/pub/mesa/${PV}/MesaDemos-${PV}.tar.bz2 "

S = "${WORKDIR}/Mesa-${PV}"

PROVIDES = "virtual/libgl"

inherit autotools pkgconfig

EXTRA_OECONF = "--disable-glu \
                --disable-glw \
                --disable-glut \
                --enable-glx-tls"

# Multiple virtual/gl providers being built breaks staging
EXCLUDE_FROM_WORLD = "1"

