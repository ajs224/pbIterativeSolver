#!/bin/bash
####################################################################
#                                                                  #
#  PB Solver runs                                                  #
#  A. J. Smith (ajs224@cam.ac.uk)                                  #
#  20/06/2015                                                      #
#                                                                  #
####################################################################

# Continuum kernel, alpha=1/10 (=beta, implicitly), N=16384, L=1, t=12.0s    

#SBATCH -p cares.cluster                     # partition (queue)
#SBATCH --nodes=1                           # -N number of nodes
#SBATCH --ntasks-per-node=1                # -n number of cores
#SBATCH --mem 128000                           # memory pool for all cores
#SBATCH --time 6-0:00                        # -t time (D-HH:MM)
#SBATCH --output slurm.%u.%N.%j.out          # -o STDOUT (%u,%N,%j)=(user, node, job allocation #)  
#SBATCH --error slurm.%u.%N.%j.err           # -e STDERR
#SBATCH --mail-type=END,FAIL                 # notifications for job done & fail
#SBATCH --mail-user=ajs224@cam.ac.uk         # send-to address
#SBATCH --workdir=/home/userspace/ajs224/C++/pbIterativeSolver 

KERNEL="freemolecular"
LOGFILE=$KERNEL"_p16_res1e-12_delta_cells1000_length1_u1_nd.log"

#(time srun ./pbSolve -t 12 -N 16384 -L 1 -alpha 0.1 -k continuum) &> data/continuum_N16384_L1_alpha0.1_t12.log

# Mass density representation
#srun ./pbIterativeSolver -cells 1000 -length 1 -u 1 -k $KERNEL -p 16 -res 1e-12 -mass -nin mono &> $LOGFILE

# Number density representation
srun ./pbIterativeSolver -cells 1000 -length 1 -u 1 -k $KERNEL -p 16 -res 1e-12 -nin mono &> $LOGFILE

echo "" >> $LOGFILE

# N.B. Can use sacct, in order to find lots of information about CPU times, memory use and disk access, using for example
sacct --job $SLURM_JOBID --format "JobName,Submit,Elapsed,AveCPU,CPUTime,UserCPU,TotalCPU,NodeList,NTasks,AveDiskRead,AveDiskWrite" >> $LOGFILE



