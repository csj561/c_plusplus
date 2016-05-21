#!/bin/sh
name=`pwd|sed 's/^.*\///g'`;
soure=`ls *.cpp`;
make clean;
#mv $(soure) $(name)'.cpp'
echo mv ${soure} ${name}'.cpp';
mv ${soure} ${name}'.cpp';
