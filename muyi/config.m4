dnl $Id$
dnl config.m4 for extension muyi

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(muyi, for muyi support,
Make sure that the comment is aligned:
[  --with-muyi             Include muyi support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(muyi, whether to enable muyi support,
dnl Make sure that the comment is aligned:
dnl [  --enable-muyi           Enable muyi support])

if test "$PHP_MUYI" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-muyi -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/muyi.h"  # you most likely want to change this
  dnl if test -r $PHP_MUYI/$SEARCH_FOR; then # path given as parameter
  dnl   MUYI_DIR=$PHP_MUYI
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for muyi files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       MUYI_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$MUYI_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the muyi distribution])
  dnl fi

  dnl # --with-muyi -> add include path
  dnl PHP_ADD_INCLUDE($MUYI_DIR/include)

  dnl # --with-muyi -> check for lib and symbol presence
  dnl LIBNAME=muyi # you may want to change this
  dnl LIBSYMBOL=muyi # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MUYI_DIR/$PHP_LIBDIR, MUYI_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_MUYILIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong muyi lib version or lib not found])
  dnl ],[
  dnl   -L$MUYI_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(MUYI_SHARED_LIBADD)

  PHP_NEW_EXTENSION(muyi, muyi.c, $ext_shared)
fi
