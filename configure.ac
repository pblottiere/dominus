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
                 [AC_MSG_ERROR(["Couldn't find libconfig.h++"])])

# wiringpi option
AC_ARG_ENABLE([wiringpi],
              [AS_HELP_STRING([--enable-wiringpi],
              [Enable wiringpi support for GPIO instead of SYSFS only])])

AS_IF([test "x$enable_wiringpi" = "xyes"],
      [AC_DEFINE([WIRINGPI], [1], [""])])

AM_CONDITIONAL([WIRINGPI], [test "x$enable_wiringpi" = "xyes"])

AS_IF([test "x$enable_wiringpi" = "xyes"],
      [AC_CHECK_HEADERS(wiringPi.h, [], [AC_MSG_ERROR(["Couldn't find wiringPi.h"])])
])

# output files
AC_CONFIG_FILES([Makefile
                 scripts/Makefile
                 src/Makefile
                 src/lib/Makefile
                 src/lib/domoticz/Makefile
                 src/lib/net/Makefile
                 src/lib/logger/Makefile
                 src/lib/devices/Makefile
                 src/lib/devices/device/Makefile
                 src/lib/devices/bme280/Makefile
                 src/lib/devices/dht11/Makefile
                 src/lib/devices/gpio/Makefile
                 src/apps/Makefile
                 src/apps/server/Makefile
                 src/apps/client/Makefile
                 examples/Makefile])

AC_OUTPUT

AC_MSG_NOTICE([

------------------------------------------------------------------------
  $PACKAGE $VERSION - Configuration Report
------------------------------------------------------------------------

 prefix:            $prefix
 exec-prefix:       $exec_prefix
 bin path:          $bindir
 lib path:          $libdir/dominus
 include path:      $includedir
 etc path:          $sysconfdir
 data path:         $datarootdir
])

