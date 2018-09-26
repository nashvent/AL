#!/bin/sh

#PBS -N script
#PBS -q batch
#PBS -l nodes=2:ppn=3
NPROC=`wc -l < $PBS_NODEFILE`
source /opt/shared/openmpi-2.0.1/environment.sh
cd paralelos
mpic++ -g -Wall pruebaMPI.cpp -o mpi2
mpiexec -n $NPROC mpi2

