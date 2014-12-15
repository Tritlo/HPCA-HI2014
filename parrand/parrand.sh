#!/bin/sh
#PBS -N parrand
#PBS -lnodes=1:ppn4
#PBS -M mpg3@hi.is
#PBS -m abe
#PBS -o /home/mpg3/parrand/

export OMP_NUM_THREADS=4
cd /home/mpg3/parrand/

./parrand
