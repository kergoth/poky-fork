DESCRIPTION = "A Client for Wi-Fi Protected Access (WPA)."
HOMEPAGE = "http://hostap.epitest.fi/wpa_supplicant/"
BUGTRACKER = "http://hostap.epitest.fi/bugz/"
SECTION = "network"
LICENSE = "GPLv2 | BSD"
LIC_FILES_CHKSUM = "file://../COPYING;md5=c54ce9345727175ff66d17b67ff51f58 \
                    file://../README;md5=54cfc88015d3ce83f7156e63c6bb1738 \
                    file://wpa_supplicant.c;beginline=1;endline=17;md5=1eb88410f8cc9b47f077c69b772ec0e2"
DEPENDS = "gnutls dbus"
RRECOMMENDS_${PN} = "wpa-supplicant-passphrase wpa-supplicant-cli"

SRC_URI = "http://hostap.epitest.fi/releases/wpa_supplicant-${PV}.tar.gz \
           file://defconfig-0.6.0-gnutls \
           file://defaults-sane \
           file://wpa-supplicant.sh \
           file://wpa_supplicant.conf \
           file://wpa_supplicant.conf-sane \
           file://99_wpa_supplicant"

S = "${WORKDIR}/wpa_supplicant-${PV}/wpa_supplicant"

PACKAGES_prepend = "wpa-supplicant-passphrase wpa-supplicant-cli "
FILES_wpa-supplicant-passphrase = "/usr/sbin/wpa_passphrase"
FILES_wpa-supplicant-cli = "/usr/sbin/wpa_cli"

do_configure () {
	install -m 0755 ${WORKDIR}/defconfig-0.6.0-gnutls .config
}

export EXTRA_CFLAGS = "${CFLAGS}"
do_compile () {
	unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
	oe_runmake
}

do_install () {
	install -d ${D}${sbindir}
	install -m 755 wpa_supplicant ${D}${sbindir}
	install -m 755 wpa_passphrase ${D}${sbindir}
	install -m 755 wpa_cli        ${D}${sbindir}

	install -d ${D}${docdir}/wpa_supplicant
	install -m 644 README ${WORKDIR}/wpa_supplicant.conf ${D}${docdir}/wpa_supplicant

	install -d ${D}${sysconfdir}/default
	install -m 600 ${WORKDIR}/defaults-sane ${D}${sysconfdir}/default/wpa
	install -m 600 ${WORKDIR}/wpa_supplicant.conf-sane ${D}${sysconfdir}/wpa_supplicant.conf

	install -d ${D}${sysconfdir}/network/if-pre-up.d/
	install -d ${D}${sysconfdir}/network/if-post-down.d/
	install -d ${D}${sysconfdir}/network/if-down.d/
	install -m 644 ${WORKDIR}/wpa_supplicant.conf ${D}${sysconfdir}
	install -m 755 ${WORKDIR}/wpa-supplicant.sh ${D}${sysconfdir}/network/if-pre-up.d/wpa-supplicant
	cd ${D}${sysconfdir}/network/ && \
	ln -sf ../if-pre-up.d/wpa-supplicant if-post-down.d/wpa-supplicant

	install -d ${D}/${sysconfdir}/dbus-1/system.d
	install -m 644 ${S}/dbus-wpa_supplicant.conf ${D}/${sysconfdir}/dbus-1/system.d

	install -d ${D}/etc/default/volatiles
	install -m 0644 ${WORKDIR}/99_wpa_supplicant ${D}/etc/default/volatiles

	install -d ${D}/${datadir}/dbus-1/system-services
	sed -i -e s:${base_sbindir}:${sbindir}:g ${S}/dbus-wpa_supplicant.service
	install -m 644 ${S}/dbus-wpa_supplicant.service ${D}/${datadir}/dbus-1/system-services/fi.epitest.hostap.WPASupplicant.service
}

pkg_postinst_wpa-supplicant () {
	# can't do this offline
	if [ "x$D" != "x" ]; then
		exit 1
	fi

	/etc/init.d/populate-volatile.sh update

	DBUSPID=`pidof dbus-daemon`

	if [ "x$DBUSPID" != "x" ]; then
		/etc/init.d/dbus-1 reload
	fi
}

FILES_${PN} += "${datadir}/dbus-1/system-services/*"
