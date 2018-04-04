#!/bin/bash

make
dir='result/'

rm -rf $dir
mkdir $dir

for element in $* ; do
    if [ -x $element ]
    then
        otool -t $element &> diff1
        status_otool=`grep -oE "^[a-zA-Z0-9_.:/]*" diff1`
    	./ft_otool $element &> diff2
    	status_ft=$?
    	tmp=`diff diff1 diff2`

    	if [ "$tmp" != "" ]
    	then

    	    if [ "$status_otool" = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump:" ] && [ $status_ft = 1 ]
    	    then
    	        printf "[\033[42mOK\033[0m] $element\n"
    	    else
                printf "[\033[41mKO\033[0m] $element\n"
                file=`echo $element | grep -oE "[a-zA-Z0-9_.]*$"`
                diff diff1 diff2 > $dir$file
            fi

    	else
	    printf "[\033[42mOK\033[0m] $element\n"
    	fi

       	rm -f diff1 diff2
    fi
done
