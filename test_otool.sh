#!/bin/bash

make
dir='result/'

rm -rf $dir
mkdir $dir

for element in $* ; do
    if [ -x $element ]
    then
        otool -t $element &> diff1
    	./ft_otool $element &> diff2
    	tmp=`diff diff1 diff2`

    	if [ "$tmp" != "" ]
    	then
            printf "[\033[41mKO\033[0m] $element\n"
            file=`echo $element | grep -oE "[a-zA-Z0-9_]*$"`
            echo $tmp > $dir$file
    	else
	    printf "[\033[42mOK\033[0m] $element\n"
    	fi

       	rm -f diff1 diff2
    fi
done
