#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#AC_PREREQ([2.68])
AC_INIT([lconvert], [0.0.1], [jianqiang070@foxmail.com])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([float.h limits.h locale.h stddef.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MKTIME
AC_FUNC_REALLOC
AC_FUNC_STRCOLL
AC_CHECK_FUNCS([floor memchr setlocale strchr strerror strpbrk strrchr strspn strstr])

AC_ARG_ENABLE(log4cpp, 
                [  --enable-log4cpp    turn on log4cpp],
                [CPPFLAGS="-D_HAS_LOG4CPP"; LIBS="-llogger -llog4cpp"],
                [])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/lua/Makefile
                 test/Makefile])
AC_OUTPUT
