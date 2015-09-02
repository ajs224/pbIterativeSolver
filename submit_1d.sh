#!/bin/bash
####################################################################
#                                                                  #
#  PB Iterative Solver runs (1D Case)                              #
#  A. J. Smith (ajs224@cam.ac.uk)                                  #
#  20/06/2015                                                      #
#                                                                  #
####################################################################

# Continuum kernel, alpha=1/10 (=beta, implicitly), N=16384, L=1, t=12.0s    

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
    exit
fi

# Args
ARGS="-cells 100 -length 1 -u 1 -k $KERNEL -p 16 -res 1e-12 -mass -nin mono"
LOGFILE="$KERNEL"_p16_res1e-12_delta_cells100_length1_u1_mf.log

# Check for directories
#BASEDIR="/scratch/ajs224/pbIterativeSolver/tst"
BASEDIR="." # From working dir
DATADIR=$BASEDIR"/data"
KERNELSDIR=$BASEDIR"/kernels"

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
BIN="/home/userspace/ajs224/C++/pbIterativeSolver/pbIterativeSolver"

# Load modules
module load boost
module load mpi

srun $BIN $ARGS &> $DATADIR"/"$LOGFILE

echo "" >> $DATADIR"/"$LOGFILE

# N.B. Can use sacct, in order to find lots of information about CPU times, memory use and disk access, using for example
sacct --job $SLURM_JOBID --format "JobName,Submit,Elapsed,AveCPU,CPUTime,UserCPU,TotalCPU,NodeList,NTasks,AveDiskRead,AveDiskWrite" >> $DATADIR"/"$LOGFILE



