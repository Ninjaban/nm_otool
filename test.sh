#!/bin/bash

make

dir='tests/'
mkdir $dir

for element in $* ; do
    if [ -x $element ]
    then
	nm $element > diff1
	status_nm=$?
	./ft_nm $element > diff2
	status_ft=$?
	tmp=`diff diff1 diff2`
	if [ -n $tmp ] || [$status_nm -ne $status_ft]
	then
	    printf "[\033[41mKO\033[0m] $element\n"
	    file=`echo $element | grep -oE "[a-zA-Z0-9_]*$"`
	    echo $tmp > $dir$file
	else
	    printf "[\033[42mOK\033[0m] $element\n"
	fi
    fi
done
