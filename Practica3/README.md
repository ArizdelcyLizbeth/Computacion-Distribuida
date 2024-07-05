#  Algoritmo del Abusón
## Descripción de la Práctica

Se implementa un algoritmo simple de elección de lı́der en un
entorno distribuido. Cada nodo envı́a su rango como mensaje a todos los demás nodos y
espera acuses de recibo. El nodo que recibe el rango más alto se convierte en el lı́der, y
todos los nodos imprimen quién es el lı́der y si están caı́dos o no.


## Cómo compilar y ejecutar:

```bash
mpicc -o Practica3 Practica3.c
mpirun -np 4 ./Practica3
```