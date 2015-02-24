#!/usr/bin/env bash

user=`whoami`
hoststring=`hostname`
if [[ $hoststring == *atl* ]]
then
    export CXX=g++;
    export CC=gcc;
    export PATH=/home/drd25/localCMake/bin:$PATH
    export PATH=/home/drd25/sw/atl_cmake/bin:$PATH
    export BOOST_ROOT=/home/drd25/sw/atl_boost
fi

export mAIDA_BASE=$PWD
mkdir -p $mAIDA_BASE/build
cd $mAIDA_BASE/build
cmake $mAIDA_BASE
make
cd $mAIDA_BASE

DICT_PCM_BUILD=$mAIDA_BASE/build/mAIDAclassesdict_rdict.pcm
DICT_PCM_LIB=$mAIDA_BASE/lib/mAIDAclassesdict_rdict.pcm
ln -s $DICT_PCM_BUILD $DICT_PCM_LIB

export PATH=$PATH:$mAIDA_BASE/bin
export PATH=$PATH:$mAIDA_BASE/python
