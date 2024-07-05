#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ROUNDS 10
#define MAX_TRAITORS 1

int n_nodos;
int rango;
char plan;
char* planes;
int rey;

char generar_plan() {
    return rand() % 2 == 0 ? 'A' : 'R';
}

void comunicar() {
    MPI_Allgather(&plan, 1, MPI_CHAR, planes, 1, MPI_CHAR, MPI_COMM_WORLD);
}

void elegir_nuevo_rey() {
    // Calcular el rey común utilizando una operación de reducción
    char rey_local = plan;
    MPI_Allreduce(&rey_local, &rey, 1, MPI_CHAR, MPI_MAX, MPI_COMM_WORLD);
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &n_nodos);
    MPI_Comm_rank(MPI_COMM_WORLD, &rango);

    planes = (char*)malloc(n_nodos * sizeof(char));

    plan = generar_plan();

    int ronda = 0;
    while (ronda < MAX_ROUNDS) {
        comunicar();
        ronda++;

        // Elegir un nuevo rey después de cada ronda
        elegir_nuevo_rey();

        // Esperar a que todos los nodos actualicen su rey
        MPI_Barrier(MPI_COMM_WORLD);

        // Si el rey es igual al plan de este nodo, se ha alcanzado un consenso
        if (rey == plan) {
            break;
        }
    }

    if (rey == plan) {
        printf("Nodo %d: Consenso alcanzado, el rey es %d\n", rango, rey);
    } else {
        printf("Nodo %d: Consenso no alcanzado\n", rango);
    }

    MPI_Finalize();

    free(planes);

    return 0;
}