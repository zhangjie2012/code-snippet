
AC_INIT([kit], [1.0], [me@zhangjiee.com])

AM_INIT_AUTOMAKE([foreign])

# 编译参数
CXXFLAGS="-Wall -Werror -Wno-unused-result -g --std=c++0x"
AC_SUBST(CXXFLAGS)

# Checks for programs.
AC_PROG_CXX
AC_PROG_LN_S
AC_PROG_RANLIB
AM_PROG_AR

# Checks for libraries.
AC_CHECK_LIB([pthread], [main], [], [exit -1])

AC_CONFIG_HEADER([config.h])

AC_CONFIG_FILES([Makefile
                kit/Makefile
                tests/Makefile])

AC_OUTPUT

