# Prelude
AC_PREREQ(2.4)
AC_INIT([dominus], [0.1], [blottiere.paul@gmail.com])
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_PROG_AR
AC_PROG_CC
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11
AC_LANG_PUSH([C++])
AM_CONFIG_HEADER([config.h])

# libtool init
LT_INIT
AC_ENABLE_SHARED

# check headers
AC_CHECK_HEADER(curl/curl.h, [],
                [AC_MSG_ERROR(["Couldn't find curl/curl.h"])])

AC_CHECK_HEADERS(libconfig.h++, [],
                 [AC_MSG_ERROR(["Couldn't find libconfig.h"])])


# output files
AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/lib/Makefile
                 src/lib/domoticz/Makefile
                 src/lib/net/Makefile
                 src/lib/devices/Makefile
                 src/lib/devices/device/Makefile
                 src/lib/devices/bme280/Makefile
                 src/lib/devices/gpio/Makefile
                 src/apps/server/Makefile
                 src/apps/Makefile
                 examples/Makefile])

AC_OUTPUT

AC_MSG_NOTICE([

------------------------------------------------------------------------
  $PACKAGE $VERSION - Configuration Report
------------------------------------------------------------------------

 prefix:            $prefix
 exec-prefix:       $exec_prefix
 bin path:          $bindir
 lib path:          $libdir
 include path:      $includedir
 etc path:          $sysconfdir
 data path:         $datarootdir
])

