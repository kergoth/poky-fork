#
# For now, we will skip building of a gcc package if it is a uclibc one
# and our build is not a uclibc one, and we skip a eglibc one if our build
# is a uclibc build.
#
# See the note in gcc/gcc_3.4.0.oe
#

python __anonymous () {
    import bb, re
    uc_os = (re.match('.*uclibc*', bb.data.getVar('TARGET_OS', d, 1)) != None)
    if uc_os:
        raise bb.parse.SkipPackage("incompatible with target %s" %
                                   bb.data.getVar('TARGET_OS', d, 1))
}

# Binary locales are generated at build time if ENABLE_BINARY_LOCALE_GENERATION
# is set. The idea is to avoid running localedef on the target (at first boot)
# to decrease initial boot time and avoid localedef being killed by the OOM
# killer which used to effectively break i18n on machines with < 128MB RAM.

# default to disabled 
ENABLE_BINARY_LOCALE_GENERATION ?= "0"
ENABLE_BINARY_LOCALE_GENERATION_pn-eglibc-nativesdk = "0"

#enable locale generation on these arches
# BINARY_LOCALE_ARCHES is a space separated list of regular expressions
BINARY_LOCALE_ARCHES ?= "arm.* i[3-6]86 x86_64 powerpc mips"

# set "1" to use cross-localedef for locale generation
# set "0" for qemu emulation of native localedef for locale generation
LOCALE_GENERATION_WITH_CROSS-LOCALEDEF = "1"

# Set this to zero if you don't want ldconfig in the output package
USE_LDCONFIG ?= "1"

PKGSUFFIX = ""
PKGSUFFIX_virtclass-nativesdk = "-nativesdk"

PACKAGES = "${PN}-dbg ${PN} catchsegv${PKGSUFFIX} sln${PKGSUFFIX} nscd${PKGSUFFIX} ldd${PKGSUFFIX} localedef${PKGSUFFIX} ${PN}-utils ${PN}-pic ${PN}-dev eglibc-doc eglibc-locale libcidn libmemusage libsegfault${PKGSUFFIX} eglibc-extra-nss eglibc-thread-db${PKGSUFFIX} eglibc-pcprofile"

PACKAGES_DYNAMIC = " \
		    glibc-gconv-*${PKGSUFFIX} glibc-charmap-* glibc-localedata-* glibc-binary-localedata-* \
		    eglibc-gconv-* eglibc-charmap-* eglibc-localedata-* eglibc-binary-localedata-* \
		    locale-base-*${PKGSUFFIX}"

RPROVIDES_eglibc = "glibc"
RPROVIDES_eglibc-utils = "glibc-utils"
RPROVIDES_eglibc-pic = "glibc-pic"
RPROVIDES_eglibc-dev = "glibc-dev"
RPROVIDES_eglibc-doc = "glibc-doc"
RPROVIDES_eglibc-locale = "glibc-locale"
RPROVIDES_eglibc-extra-nss = "glibc-extra-nss"
RPROVIDES_eglibc-thread-db = "glibc-thread-db"
RPROVIDES_eglibc-pcprofile = "glibc-pcprofile"
RPROVIDES_eglibc-dbg = "glibc-dbg"
libc_baselibs = "${base_libdir}/libcrypt*.so.* ${base_libdir}/libcrypt-*.so ${base_libdir}/libc*.so.* ${base_libdir}/libc*.so ${base_libdir}/libm*.so.* ${base_libdir}/libm-*.so ${base_libdir}/ld*.so.* ${base_libdir}/ld-*.so ${base_libdir}/libpthread*.so.* ${base_libdir}/libpthread-*.so ${base_libdir}/libresolv*.so.* ${base_libdir}/libresolv-*.so ${base_libdir}/librt*.so.* ${base_libdir}/librt-*.so ${base_libdir}/libutil*.so.* ${base_libdir}/libutil-*.so ${base_libdir}/libnsl*.so.* ${base_libdir}/libnsl-*.so ${base_libdir}/libnss_files*.so.* ${base_libdir}/libnss_files-*.so ${base_libdir}/libnss_compat*.so.* ${base_libdir}/libnss_compat-*.so ${base_libdir}/libnss_dns*.so.* ${base_libdir}/libnss_dns-*.so ${base_libdir}/libdl*.so.* ${base_libdir}/libdl-*.so ${base_libdir}/libanl*.so.* ${base_libdir}/libanl-*.so ${base_libdir}/libBrokenLocale*.so.* ${base_libdir}/libBrokenLocale-*.so"

FILES_${PN} = "${libc_baselibs} ${libexecdir}/* ${@base_conditional('USE_LDCONFIG', '1', '${base_sbindir}/ldconfig ${sysconfdir}/ld.so.conf', '', d)}"
FILES_ldd${PKGSUFFIX} = "${bindir}/ldd"
FILES_libsegfault${PKGSUFFIX} = "${base_libdir}/libSegFault*"
FILES_libcidn = "${base_libdir}/libcidn*.so"
FILES_libmemusage = "${base_libdir}/libmemusage.so"
FILES_eglibc-extra-nss = "${base_libdir}/libnss*"
FILES_sln = "/sbin/sln"
FILES_eglibc-pic = "${libdir}/*_pic.a ${libdir}/*_pic.map ${libdir}/libc_pic/"
FILES_eglibc-dev_append += "${bindir}/rpcgen ${libdir}/*.a \
	${base_libdir}/*.a ${base_libdir}/*.o ${datadir}/aclocal"
FILES_nscd${PKGSUFFIX} = "${sbindir}/nscd*"
FILES_eglibc-utils = "${bindir}/* ${sbindir}/*"
FILES_eglibc-gconv = "${libdir}/gconv/*"
FILES_${PN}-dbg += "${libexecdir}/*/.debug ${libdir}/gconv/.debug"
FILES_catchsegv${PKGSUFFIX} = "${bindir}/catchsegv"
RDEPENDS_catchsegv${PKGSUFFIX} = "libsegfault"
FILES_eglibc-pcprofile = "${base_libdir}/libpcprofile.so"
FILES_eglibc-thread-db${PKGSUFFIX} = "${base_libdir}/libthread_db*"
FILES_localedef${PKGSUFFIX} = "${bindir}/localedef"
RPROVIDES_eglibc-dev += "libc-dev"

SUMMARY_sln = "The static ln."
DESCRIPTION_sln = "Similar to the 'ln' utility, but statically linked.  sln is useful to make symbolic links to dynamic libraries if the dynamic linking system, for some reason, is not functional."
SUMMARY_nscd = "Name service cache daemon"
DESCRIPTION_nscd = "nscd, name service cache daemon, caches name service lookups for the passwd, group and hosts information.  It can damatically improvide performance with remote, such as NIS or NIS+, name services."
SUMMARY_eglibc-extra-nss = "hesiod, NIS and NIS+ nss libraries"
DESCRIPTION_eglibc-extra-nss = "eglibc: nis, nisplus and hesiod search services."
SUMMARY_ldd = "print shared library dependencies"
DESCRIPTION_ldd = "/usr/bin/ldd prints shared library dependencies for each program or shared library specified on the command line."
DESCRIPTION_localedef = "eglibc: compile locale definition files"
SUMMARY_eglibc-utils = "Miscellaneous utilities provided by eglibc"
DESCRIPTION_eglibc-utils = "Miscellaneous utilities including getconf, iconf, locale, gencat, tzselect, zic, rpcinfo, ..."

inherit libc-package

