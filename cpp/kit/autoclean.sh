#!/bin/sh

find . -iname 'makefile' -o -iname '*.o' -o -iname '*.in' -o -iname '*.m4' -o -iname '*.a' | xargs rm -f
rm -rf *.cache/
rm -f compile
rm -f config.h*
rm -f *.log
rm -f *.status
rm -f configure
rm -f missing
rm -rf stamp-h1
rm -rf ar-lib
rm -rf depcomp
rm -rf install-sh
rm -f ./tests/tests
rm -f ./tests/*.out
rm -f ./tests/*.txt
