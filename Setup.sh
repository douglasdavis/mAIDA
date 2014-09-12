# mAIDA bash script to setup env

if [ `hostname` == 'atl010.phy.duke.edu' ] || [ `hostname` == 'atl009.phy.duke.edu' ]; then
    setupATLAS
    source ${ATLAS_LOCAL_ROOT_BASE}/packageSetups/atlasLocalROOTSetup.sh --rootVersion 5.34.13-x86_64-slc6-gcc47-opt
    export CXX=g++;
    export CC=gcc;
    export PATH=/home/drd25/localCMake/bin:$PATH
    export PATH=/home/drd25/sw/atl_cmake/bin:$PATH
    export BOOST_ROOT=/home/drd25/sw/atl_boost
fi

export TOPDIR=$PWD
mkdir -p $TOPDIR/build
cd $TOPDIR/build
cmake $TOPDIR
make
cd $TOPDIR
export PATH=$PATH:$TOPDIR/bin
export PATH=$PATH:$TOPDIR/python
