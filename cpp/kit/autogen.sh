#!/bin/sh

aclocal
autoheader
automake --add-missing -Wno-portability
autoconf

./configure $*
