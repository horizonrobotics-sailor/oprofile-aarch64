dnl AX_EXTRA_DIRS - Let user specify extra dirs for include/libs
AC_DEFUN(AX_EXTRA_DIRS,
[
AC_ARG_WITH(extra-includes,
[  --with-extra-includes=DIR    add extra include paths],
  use_extra_includes="$withval",
  use_extra_includes=NO
)
if test -n "$use_extra_includes" && \
        test "$use_extra_includes" != "NO"; then
  ac_save_ifs=$IFS
  IFS=':'
  for dir in $use_extra_includes; do
    extra_includes="$extra_includes -I$dir"
  done
  IFS=$ac_save_ifs
  CPPFLAGS="$CPPFLAGS $extra_includes"
fi

AC_ARG_WITH(extra-libs,
[  --with-extra-libs=DIR        add extra library paths],
  use_extra_libs=$withval,
  use_extra_libs=NO
)
if test -n "$use_extra_libs" && \
        test "$use_extra_libs" != "NO"; then
   ac_save_ifs=$IFS
   IFS=':'
   for dir in $use_extra_libs; do
     extra_libraries="$extra_libraries -L$dir"
   done
   IFS=$ac_save_ifs
   LDFLAGS="$LDFLAGS $extra_libraries"
fi
]
)
