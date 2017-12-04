#!/bin/sh

echo "clear ..."

cat /dev/null > file_list.txt
cat /dev/null > cscope.files
cat /dev/null > cscope.out
cat /dev/null > TAGS

echo "gen file_list ..."

find . -name '*h' -o -name '*.cpp' >> file_list.txt
cat file_list.txt | etags -

echo "build index ..."

cscope-indexer -r

echo "done !"


rm file_list.txt
