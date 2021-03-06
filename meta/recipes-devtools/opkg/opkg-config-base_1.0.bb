DESCRIPTION = "Base configuration files for opkg"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${POKYBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"
PACKAGE_ARCH = "${MACHINE_ARCH}"

do_compile() {
	mkdir -p ${S}/${sysconfdir}/opkg/

	archconf=${S}/${sysconfdir}/opkg/arch.conf

	rm -f $archconf
	ipkgarchs="${PACKAGE_ARCHS}"
	priority=1
	for arch in $ipkgarchs; do 
		echo "arch $arch $priority" >> $archconf
		priority=$(expr $priority + 5)
	done
}


do_install () {
	install -d ${D}${sysconfdir}/opkg
	install -m 0644  ${S}/${sysconfdir}/opkg/* ${D}${sysconfdir}/opkg/
}

FILES_${PN} = "${sysconfdir}/opkg/ "

CONFFILES_${PN} += "${sysconfdir}/opkg/arch.conf"

