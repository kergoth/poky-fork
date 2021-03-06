SUMMARY = "Multiplexing terminal manager"
DESCRIPTION = "Screen is a full-screen window manager \
that multiplexes a physical terminal between several \
processes, typically interactive shells."
HOMEPAGE = "http://www.gnu.org/software/screen/"
BUGTRACKER = "https://savannah.gnu.org/bugs/?func=additem&group=screen"

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING;md5=0774d66808b0f602e94448108f59448b \
                    file://screen.h;endline=23;md5=9a7ae69a2aafed891bf7c38ddf9f6b7d"

SECTION = "console/utils"
DEPENDS = "ncurses"
PR = "r0"

SRC_URI = "${GNU_MIRROR}/screen/screen-${PV}.tar.gz;name=tarball \
           ${DEBIAN_MIRROR}/main/s/screen/screen_4.0.3-11+lenny1.diff.gz;name=patch \
           file://configure.patch"

SRC_URI[tarball.md5sum] = "8506fd205028a96c741e4037de6e3c42"
SRC_URI[tarball.sha256sum] = "78f0d5b1496084a5902586304d4a73954b2bfe33ea13edceecf21615c39e6c77"

SRC_URI[patch.md5sum] = "9bacd9be1d9c57e2e0381df2775b33e0"
SRC_URI[patch.sha256sum] = "19130d097e9ed897c84a2c640634dd36ee3233c17b0bf5d18549ed1e064b3073"

inherit autotools

EXTRA_OECONF = "--with-pty-mode=0620 --with-pty-group=5"

