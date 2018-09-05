```
mpic++ -g -Wall pruebaMPI.cpp -o mpi
mpiexec -n 3 ./mpi
```
En cluster
```
mpirun -np 3 --hostfile .mpi_host ./mpi
```