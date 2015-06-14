
#prerequest version and initializing with name, version and bug fix adress.
AC_PREREQ([2.69])
AC_INIT([testris], [0.2], [douglasknowman@gmail.com])

#initializing automake
AM_INIT_AUTOMAKE([foreign])

# Checks for C compiler.
AC_PROG_CC

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h string.h termios.h unistd.h])

#check configure files.
AC_CONFIG_FILES([Makefile src/Makefile])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([select])

AC_OUTPUT
