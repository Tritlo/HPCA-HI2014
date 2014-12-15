#!/bin/sh
#PBS -N CPUChat
#PBS -lnodes=4
#PBS -M mpg3@hi.is
#PBS -m abe
#PBS -o /home/mpg3/CPUChat/
mpirun /home/mpg3/CPUChat/cpuchat
