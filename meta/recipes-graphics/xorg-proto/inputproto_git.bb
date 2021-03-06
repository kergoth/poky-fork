require xorg-proto-common.inc

SUMMARY = "XI: X Input extension headers"

DESCRIPTION = "This package provides the wire protocol for the X Input \
extension.  The extension supports input devices other then the core X \
keyboard and pointer."

PR = "r1"
PE = "1"
PV = "1.9.99.12+git${SRCPV}"

SRC_URI = "git://anongit.freedesktop.org/git/xorg/proto/inputproto;protocol=git"
S = "${WORKDIR}/git"

inherit gettext

BBCLASSEXTEND = "native nativesdk"
