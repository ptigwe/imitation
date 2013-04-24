#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([imitation], [1.0], [ptigwe@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([ -Wall -Werror])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O

AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
   then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi

AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([docs/Doxyfile])])


# Checks for libraries.
AC_CHECK_LIB([gmp], [__gmpz_init], [], [AC_MSG_ERROR([Could not find -lgmp. GNUMP can be installed from http://gmplib.org/])])
AC_CHECK_LIB([m], [floor])

# Check for GLib version
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.32],
   [AC_DEFINE([HAVE_GLIB_2_32], [1], [Use GLIB])],
   [PKG_CHECK_MODULES([GLIB], [glib-2.0],
       [AC_DEFINE([HAVE_GLIB], [1], [Use GLIB])
    ])
])

# Check for GTK+ and opencv
PKG_CHECK_MODULES([DEPS], [gtk+-2.0 opencv])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_HEADERS([gmp.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([pow])

AC_CONFIG_FILES([Makefile
                 docs/Makefile
                 bin/Makefile
                 tests/bin/Makefile])
AC_OUTPUT
