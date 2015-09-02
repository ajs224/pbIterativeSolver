#!/bin/bash

KERNEL=$1
if [ -z "$KERNEL" ]; then 
    echo "No collision kernel specified!";
    exit
fi

# Args
ARGS="-cells 100 -length 1 -u 1 -k $KERNEL -p 10 -res 1e-12 -mass -nin mono"
LOGFILE="$KERNEL"_p10_res1e-12_delta_cells100_length1_u1_mf.log

# Specify binary
BIN="/home/userspace/ajs224/C++/pbIterativeSolver/pbIterativeSolver"

# Check for directories
BASEDIR="/scratch/ajs224/pbIterativeSolver/tst"
DATADIR=$BASEDIR"/data"
KERNELSDIR=$BASEDIR"/kernels"

if [ ! -d $BASEDIR ]; then
    echo "Creating $BASEDIR"
    mkdir -p $BASEDIR
fi

if [ ! -d $DATADIR ]; then
    echo "Creating $DATADIR"
    mkdir $DATADIR
fi

if [ ! -d $KERNELSDIR ]; then
    echo "Creating $KERNELSDIR"
    mkdir $KERNELSDIR
fi

# Load modules
module load boost
module load mpi

cd $BASEDIR
$BIN $ARGS &> $LOGFILE
