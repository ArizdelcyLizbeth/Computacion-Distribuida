#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>

#define RAIZ 0

int main(int argc, char *argv[]) {
    int rango, tamaño;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rango);
    MPI_Comm_size(MPI_COMM_WORLD, &tamaño);

    // Simular nodos caídos basados en alguna condición
    bool estaCaido = (rango % 2 == 0); 

    int lider = -1; 
    int mensaje;     
    int nodosActivos; 

    // Proceso de elección del líder
    for (int i = 0; i < tamaño; i++) {
        MPI_Send(&rango, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }

    // Esperar acuses de recibo de todos los nodos
    nodosActivos = tamaño;

    while (nodosActivos > 0) {
        MPI_Recv(&mensaje, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        nodosActivos--;

        if (mensaje > lider) {
            lider = mensaje;
        }
    }

    // Asegurar que todos los nodos esperen antes de imprimir...
    MPI_Barrier(MPI_COMM_WORLD);

    printf("Nodo %d: El líder es el Nodo %d (Vivo: %s)\n", rango, lider, estaCaido ? "No" : "Sí");

    MPI_Finalize();
    return 0;
}