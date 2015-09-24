#!/bin/bash
####################################################################
#                                                                  #
#  PB Iterative Solver runs (quasi-1D Case)                        #
#  A. J. Smith (ajs224@cam.ac.uk)                                  #
#  20/06/2015                                                      #
#                                                                  #
####################################################################
EM=`git config user.email`
#SBATCH -p cares.cluster                     # partition (queue)
#SBATCH --nodes=1                            # -N number of nodes
#SBATCH --ntasks-per-node=1                  # -n number of cores
#SBATCH --mem 128000                         # memory pool for all cores
#SBATCH --time 6-0:00                        # -t time (D-HH:MM)
#SBATCH --output slurm.%u.%N.%j.out          # -o STDOUT (%u,%N,%j)=(user, node, job allocation #)  
#SBATCH --error slurm.%u.%N.%j.err           # -e STDERR
#SBATCH --mail-type=END,FAIL                 # notifications for job done & fail
#SBATCH --mail-user=$(git config user.email)
#SBATCH --workdir=/home/userspace/ajs224/

echo $EM > tst.log
srun false


