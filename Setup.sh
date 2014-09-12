# mAIDA bash script to setup env

export TOPDIR=$PWD
mkdir -p $TOPDIR/build
cd $TOPDIR/build
cmake $TOPDIR
make
cd $TOPDIR
export PATH=$PATH:$TOPDIR/bin
export PATH=$PATH:$TOPDIR/python
