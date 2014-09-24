#!/usr/bin/env bash

# mAIDA bash script to setup env

user=`whoami`
if [ `whoami` == 'drd25' ]; then
    setupATLAS
    # using root version 5.34.13 on the SLC6 machines because
    # i know it runs TMVA smoothly and doesnt have the
    # PyROOT TLeaf bug that wasnt fixed until 5.34.20
    # 
    # set path to kind cmake28 installed in $HOME
    # set boost_root for cmake to find it
    root_version=5.34.13-x86_64-slc6-gcc47-opt
    source ${ATLAS_LOCAL_ROOT_BASE}/packageSetups/atlasLocalROOTSetup.sh --rootVersion $root_version
    export CXX=g++;
    export CC=gcc;
    export PATH=/home/$user/localCMake/bin:$PATH
    export PATH=/home/$user/sw/atl_cmake/bin:$PATH
    export BOOST_ROOT=/home/$user/sw/atl_boost
fi

# Must have $ROOTSYS defined
# Must have $ROOTSYS/thisroot.sh sourced
# Must have Boost installed
# Must have $BOOST_ROOT defined (if  necessary, cmake
#   module might be able to fine it automatically)

export TOPDIR=$PWD
mkdir -p $TOPDIR/build
cd $TOPDIR/build
cmake $TOPDIR
make
cd $TOPDIR
export PATH=$PATH:$TOPDIR/bin
export PATH=$PATH:$TOPDIR/python
