# mAIDA bash script to setup env

user=`whoami`
#if [ `hostname` == 'atl010.phy.duke.edu' ] || [ `hostname` == 'atl009.phy.duke.edu' ]; then
if [ $ATL_MACHINE == 'yes' ]; then
    setupATLAS
    # using root version 5.34.13 on the SLC6 machiens because
    # i know it runs TMVA smoothly and doesnt have the
    # PyROOT TLeaf bug that wasnt fixed until 5.34.20
    root_version=5.34.13-x86_64-slc6-gcc47-opt
    source ${ATLAS_LOCAL_ROOT_BASE}/packageSetups/atlasLocalROOTSetup.sh --rootVersion $root_version
    export CXX=g++;
    export CC=gcc;
    export PATH=/home/$user/localCMake/bin:$PATH
    export PATH=/home/$user/sw/atl_cmake/bin:$PATH
    export BOOST_ROOT=/home/$user/sw/atl_boost
fi

# Must have $ROOTSYS defined
# Must have $ROOTSYS/thisroot.sh sources
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
