require xf86-input-common.inc

SUMMARY = "X.Org X server -- synaptics touchpad input driver"

DESCRIPTION = "synaptics is an Xorg input driver for the touchpads from \
Synaptics Incorporated. Even though these touchpads (by default, \
operating in a compatibility mode emulating a standard mouse) can be \
handled by the normal evdev or mouse drivers, this driver allows more \
advanced features of the touchpad to become available."

PV = "0.15.2+git${SRCPV}"

SRC_URI = "git://anongit.freedesktop.org/git/xorg/driver/xf86-input-synaptics;protocol=git"
S = "${WORKDIR}/git"

DEPENDS += "libxi"
