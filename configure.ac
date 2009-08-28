m4_define([tuxchan_major_version], [0])
m4_define([tuxchan_minor_version], [1])
m4_define([tuxchan_micro_version], [0])

m4_define([tuxchan_version],
          [tuxchan_major_version.tuxchan_minor_version.tuxchan_micro_version])

m4_define([tuxchan_interface_age], [0])
m4_define([tuxchan_binary_age],
          [m4_eval(100 * tuxchan_minor_version + tuxchan_micro_version)])

m4_define([lt_current],
          [m4_eval(100 * tuxchan_minor_version + tuxchan_micro_version - tuxchan_interface_age)])
m4_define([lt_revision], [tuxchan_interface_age])
m4_define([lt_age],
          [m4_eval(tuxchan_binary_age - tuxchan_interface_age)])

m4_define([glib_req_version], [2.16])
m4_define([clutter_req_version], [1.0.0])
m4_define([soup_req_version], [2.26.2])

AC_PREREQ([2.59])
AC_INIT([tuxchan], [tuxchan_version], [], [tuxchan])

AM_INIT_AUTOMAKE([1.10])

GNOME_COMMON_INIT
GNOME_COMPILE_WARNINGS
GNOME_DEBUG_CHECK

IT_PROG_INTLTOOL([0.35.0])

AM_DISABLE_STATIC
AM_PATH_GLIB_2_0
AM_PROG_CC_C_O
AM_PROG_LIBTOOL

AC_HEADER_STDC
AC_C_CONST

TUXCHAN_MAJOR_VERSION=tuxchan_major_version
TUXCHAN_MINOR_VERSION=tuxchan_minor_version
TUXCHAN_MICRO_VERSION=tuxchan_micro_version
TUXCHAN_VERSION=tuxchan_version
AC_SUBST(TUXCHAN_MAJOR_VERSION)
AC_SUBST(TUXCHAN_MICRO_VERSION)
AC_SUBST(TUXCHAN_MINOR_VERSION)
AC_SUBST(TUXCHAN_VERSION)

dnl tuxchan checks
PKG_CHECK_MODULES(TUXCHAN,
                  libsoup-2.4 >= soup_req_version dnl
                  clutter-1.0 >= clutter_req_version)
AC_SUBST(TUXCHAN_CFLAGS)
AC_SUBST(TUXCHAN_LIBS)

dnl = Enable debug level ===================================================

m4_define([debug_default],
          m4_if(m4_eval(tuxchan_minor_version % 2), [1], [yes], [minimum]))

AC_ARG_ENABLE(debug,
              AC_HELP_STRING([--enable-debug=@<:@no/minimum/yes@:>@],
                             [turn on debugging @<:@default=debug_default@:>@]),
,
              enable_debug=debug_default)

if test "x$enable_debug" = "xyes"; then
  test "$cflags_set" = set || CFLAGS="$CFLAGS -g"
  TUXCHAN_DEBUG_CFLAGS="-DTUXCHAN_ENABLE_DEBUG"
else
  if test "x$enable_debug" = "xno"; then
    TUXCHAN_DEBUG_CFLAGS="-DG_DISABLE_ASSERT -DG_DISABLE_CHECKS -DG_DISABLE_CAST_CHECKS"
  else # minimum
    TUXCHAN_DEBUG_CFLAGS="-DTUXCHAN_ENABLE_DEBUG -DG_DISABLE_CAST_CHECKS"
  fi
fi

AC_SUBST(TUXCHAN_DEBUG_CFLAGS)

dnl = Enable strict compiler flags =========================================

# use strict compiler flags only on development releases
#m4_define([maintainer_flags_default],
#          m4_if(m4_eval(tuxchan_minor_version % 2), [1], [yes], [no]))
m4_define([maintainer_flags_default], [no])
AC_ARG_ENABLE([maintainer-flags],
              AC_HELP_STRING([--enable-maintainer-flags=@<:@no/yes@:>@],
                             [Use strict compiler flags @<:@default=maintainer_flags_default@:>@]),,
              enable_maintainer_flags=maintainer_flags_default)

if test "x$enable_maintainer_flags" = "xyes"; then
  CPPFLAGS="$CPPFLAGS -g -Wall -Wshadow -Wcast-align -Wno-uninitialized -Werror"
else
  CPPFLAGS="$CPPFLAGS -g -Wall"
fi

dnl Internationalization
GETTEXT_PACKAGE=tuxchan
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], "$GETTEXT_PACKAGE", [Define the gettext package to use])
AC_SUBST(GETTEXT_PACKAGE)
AM_GLIB_GNU_GETTEXT

AC_CONFIG_FILES([
        Makefile
        src/Makefile
        po/Makefile.in
])

AC_OUTPUT

echo ""
echo "                TuxChan: $VERSION"
echo ""
echo "                 Prefix: ${prefix}"
echo "         Compiler flags: ${CPPFLAGS}"
echo ""
