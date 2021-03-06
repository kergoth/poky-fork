#
# eglibc specific configuration
#

# Add glibc overrides to the overrides for eglibc.
OVERRIDES .= ":libc-glibc"

#eglibc
PREFERRED_PROVIDER_virtual/libiconv ?= "eglibc"
PREFERRED_PROVIDER_virtual/libintl ?= "eglibc"
PREFERRED_PROVIDER_virtual/libc ?= "eglibc"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}libc-initial ?= "eglibc-initial"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}libc-for-gcc ?= "eglibc"

#eglibc-nativesdk
PREFERRED_PROVIDER_virtual/libiconv-nativesdk ?= "eglibc-nativesdk"
PREFERRED_PROVIDER_virtual/libc-nativesdk ?= "eglibc-nativesdk"
PREFERRED_PROVIDER_virtual/${SDK_PREFIX}libc-initial-nativesdk ?= "eglibc-initial-nativesdk"

TARGET_OS = "${GLIBCTARGETOS}"

CXXFLAGS += "-fvisibility-inlines-hidden"

LIBC_DEPENDENCIES = "libsegfault \
		     eglibc \
    		     eglibc-dbg \
    		     eglibc-dev \
    		     eglibc-utils \
    		     eglibc-thread-db \
    		     eglibc-localedata-i18n \
    		     eglibc-gconv-ibm850 \
    		     eglibc-gconv-cp1252 \
    		     eglibc-gconv-iso8859-1 \
    		     eglibc-gconv-iso8859-15 \
    		     locale-base-en-us \
    		     locale-base-en-gb "
