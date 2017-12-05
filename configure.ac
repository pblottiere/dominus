# Prelude
AC_PREREQ(2.4)
AC_INIT([TestPackage], [0.1], [noelie.ramuzat@ensta-bretagne.org])
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_PROG_AR
AC_PROG_CXX 
AM_CONFIG_HEADER([config.h])

# libtool init
LT_INIT
AC_ENABLE_SHARED

# check headers
AC_CHECK_HEADER(sys/socket.h, [],
                [AC_MSG_ERROR(["Couldn't find sys/socket.h"])])

AC_CHECK_HEADER(curl/curl.h, [],
                [AC_MSG_ERROR(["Couldn't find curl/curl.h"])])

# output files
AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/domoticz_create_assign/Makefile])

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
