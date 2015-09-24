#!/bin/bash
####################################################################
#                                                                  #
#  PB Iterative Solver runs (quasi-1D Case)                        #
#  A. J. Smith (ajs224@cam.ac.uk)                                  #
#  20/06/2015                                                      #
#                                                                  #
####################################################################

#SBATCH -p cares.cluster                     # partition (queue)
#SBATCH --nodes=1                            # -N number of nodes
#SBATCH --ntasks-per-node=1                  # -n number of cores
#SBATCH --mem 128000                         # memory pool for all cores
#SBATCH --time 6-0:00                        # -t time (D-HH:MM)
#SBATCH --output slurm.%u.%N.%j.out          # -o STDOUT (%u,%N,%j)=(user, node, job allocation #)  
#SBATCH --error slurm.%u.%N.%j.err           # -e STDERR
#SBATCH --mail-type=END,FAIL                 # notifications for job done & fail
#SBATCH --mail-user=ajs224@cam.ac.uk         # send-to address
#SBATCH --workdir=/scratch/ajs224/pbIterativeSolver

KERNEL=$1
if [ -z "$KERNEL" ]; then 
    echo "No collision kernel specified!";
    srun false
    exit
fi

# Run parameters
#CELLS=1000
#LENGTH=1
#u=1
#GRID="grid_1000cells_log.dat"
#GRID="grid_1000cells_log10.dat"
#GRID="grid_1000cells_lin.dat"
#GRID="grid_length1_1000cells_log.dat" # Match DQMoMIC grid
#GRID="grid_length10_10000cells_log.dat" # Match DQMoMIC grid
GRID="grid_length1_1000cells_lin.dat" # Match DQMoMIC grid

p=16
res=1e-12
rep="nd" # nd or mf

# Check for directories
#BASEDIR="/scratch/ajs224/pbIterativeSolver/tst"
BASEDIR="." # From working dir
DATADIR=$BASEDIR"/data"
KERNELSDIR=$BASEDIR"/kernels"

# Args
if [ $rep == "mf" ]; then
	#ARGS="-cells $CELLS -length $LENGTH -u $u -k $KERNEL -p $p -res $res -mass -nin mono" 
	ARGS="-grid $GRID -k $KERNEL -p $p -res $res -mass -nin mono"
else
	#ARGS="-cells $CELLS -length $LENGTH -u $u -k $KERNEL -p $p -res $res -nin mono" 
	ARGS="-grid $GRID -k $KERNEL -p $p -res $res"
fi

# Files
GRIDDESC=`basename $GRID .dat`
LOGFILE=$DATADIR"/""$KERNEL"_p"$p"_res"$res"_delta_"$GRIDDESC"_$rep".log"
MOMSFILE=$DATADIR"/""$KERNEL"_moments_p"$p"_res"$res"_delta_"$GRIDDESC"_$rep.txt
DATAFILE=$DATADIR"/""$KERNEL"_data_p"$p"_res"$res"_delta_"$GRIDDESC"_$rep.txt

# WORKDIR must exist before script submission
#if [ ! -d $BASEDIR ]; then
#    echo "Creating $BASEDIR"
#    mkdir -p $BASEDIR
#fi

if [ ! -d $DATADIR ]; then
    echo "Creating $DATADIR"
    mkdir $DATADIR
fi

if [ ! -d $KERNELSDIR ]; then
    echo "Creating $KERNELSDIR"
    mkdir $KERNELSDIR
fi

# Specify binary
BINDIR="/home/userspace/ajs224/C++/pbIterativeSolver"
BIN=$BINDIR"/pbIterativeSolver"

# broacast grid file to scratch space
#sbcast $BINDIR"/"$GRID /scratch/ajs224/pbIterativeSolver/
cp $BINDIR"/"$GRID /scratch/ajs224/pbIterativeSolver/

# Load modules
module load boost
module load mpi

srun $BIN $ARGS &> $LOGFILE

echo "" >> $LOGFILE

# N.B. Can use sacct, in order to find lots of information about CPU times, memory use and disk access, using for example
sacct --job $SLURM_JOBID --format "JobName,Submit,Elapsed,AveCPU,CPUTime,UserCPU,TotalCPU,NodeList,NTasks,AveDiskRead,AveDiskWrite" >> $LOGFILE

# Copy data back to userspace
cp $LOGFILE $MOMSFILE $DATAFILE $BINDIR"/data/"
