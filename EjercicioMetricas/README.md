# Ejercicio de métricas

Primero, compilar el archivo "Ejercicio.c":

```bash
mpicc
```
O bien:
```bash
gcc -l mpi
```
Una vez compilado el código, lanzar el ejecutable resultante con diferentes cantidades de nodos, por ejemplo:

```bash
mpirun -np 4 --oversubscribe ./a.out
```