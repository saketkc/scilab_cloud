#!/bin/sh

if [ $# != 1 ]; then
    echo "Wrong number of arguments"
    echo "fr_FR, en_US, ... is expected as argument"
    exit
fi

MAXDOC_DIR="./maxima-5.13.0-doc"
SCILAB_MAXDOC_DIR="../../help/$1/Maxima"
LISTMAXFUN_DIR="../../macros/maxfun"
CUR_DIR=`pwd`
MAXIMA_VER=`maxima --version`

if  ! test -f texi2scidoc; then
    echo "You should execute make before"
    exit
fi

if ! test -e $SCILAB_MAXDOC_DIR; then
    mkdir -p $SCILAB_MAXDOC_DIR
fi

# this command generates listPnames.txt which contains personnalized names of
# Maxima's functions
scilab -nb -nw -nwni -f "genPnames.sce"

# we generate xml files in SCILAB_MAXDOC_DIR, the list of Maxima's function
# in LISTMAXFUN_DIR  
./texi2scidoc -s $SCILAB_MAXDOC_DIR -l $LISTMAXFUN_DIR -p listPnames.txt $MAXDOC_DIR/*.texi 

# directory figures contains gif files useful for the documentation
cp -r $MAXDOC_DIR/figures $SCILAB_MAXDOC_DIR

cd $SCILAB_MAXDOC_DIR/..
scilab -nb -nw -e "maxima_version='$MAXIMA_VER';exec('build_help.sce');exit"
rm -r scilab_$1_help Maxima/* master_help.xml

cd $CUR_DIR

