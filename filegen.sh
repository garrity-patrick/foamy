#!/bin/bash
# Updated 11/7/11 to touche_foamy -- adds specific header stuff for the foamy project

# Chris Cornelius October 2011
# A script to touch files which automatically adds a default header

#################################################
# FOR CUSTOMIZING ### ###########################
author="Chris Cornelius, Patrick Garrity, Jonathan Sandness"
info0="Foamy (toy language project) - ProLang course, Fall 2011"
info1="//TODO: write description here!!!"
info2=""
#################################################

# get the current date in a given formula
date=`date +%m/%d/%Y`
c_comment="//"
c_author="@author"
py_comment="#"
py_author="__credits__ = [\""$author"\",]"

# check 
if [ $# -lt 1 ]; then
	echo "Usage: touche filename"
	exit 0
fi

# assert: we're going to make a file with the name given $1
if [ -f $1 ]; then
	echo "touche: $1 already exists"
	exit -1
fi


# simply add more clauses here if you want to work with other filetypes

# check to see if the file is a .cpp file
res=`echo $1 | grep ".cpp"`
if [[ ${#res} > 0 ]]; then
	touch $1
	echo $c_comment $1 >> $1
	echo $c_comment $c_author $author >> $1
	echo $c_comment "Created" $date >> $1
	echo $c_comment $info0 >> $1
	echo $c_comment $info1 >> $1
	echo $c_comment $info2 >> $1
	echo >> $1
	exit 0
fi

# check to see if the file is a .h file
res=`echo $1 | grep ".h"`
if [[ ${#res} > 0 ]]; then
	touch $1
	echo $c_comment $1 >> $1
	echo $c_comment $c_author $author >> $1
	echo $c_comment "Created" $date >> $1
	echo $c_comment $info0 >> $1
	echo $c_comment $info1 >> $1
	echo $c_comment $info2 >> $1
	echo >> $1
	exit 0
fi

# check to see if the file is a .c file
res=`echo $1 | grep ".c"`
if [[ ${#res} > 0 ]]; then
	touch $1
	echo $c_comment $1 >> $1
	echo $c_comment $c_author $author >> $1
	echo $c_comment "Created" $date >> $1
	echo $c_comment $info0 >> $1
	echo $c_comment $info1 >> $1
	echo $c_comment $info2 >> $1
	echo >> $1
	exit 0
fi


# check to see if the file is a .py file
res=`echo $1 | grep ".py"`
if [[ ${#res} > 0 ]]; then
	touch $1
	echo $py_comment $1 >> $1
	echo $py_comment "Created" $date >> $1
	echo $py_comment $info0 >> $1
	echo $py_comment $info1 >> $1
	echo $py_comment $info2 >> $1
	echo >> $1
	echo $py_author >> $1
	echo >> $1
	exit 0
fi



# else -- if it's not a filetype we recognize, simply touch the file
touch $1
