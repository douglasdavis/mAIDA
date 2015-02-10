#!/usr/bin/env bash

user=`whoami`
hoststring=`hostname`
if [[ $hoststring == *atl* ]]
then
    setupATLAS
    rv=5.34.22-x86_64-slc6-gcc48-opt
    source ${ATLAS_LOCAL_ROOT_BASE}/packageSetups/atlasLocalROOTSetup.sh --rootVersion $rv
    export CXX=g++;
    export CC=gcc;
    export PATH=/home/$user/localCMake/bin:$PATH
    export PATH=/home/$user/sw/atl_cmake/bin:$PATH
    export BOOST_ROOT=/home/$user/sw/atl_boost
fi

export mAIDA_BASE=$PWD
mkdir -p $mAIDA_BASE/build
cd $mAIDA_BASE/build
cmake $mAIDA_BASE
make
cd $mAIDA_BASE
ln -s $mAIDA_BASE/build/mAIDAclassesdict_rdict.pcm $mAIDA_BASE/lib/mAIDAclassesdict_rdict.pcm
export PATH=$PATH:$mAIDA_BASE/bin
export PATH=$PATH:$mAIDA_BASE/python
