#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // Igual que (l+r)/2, pero evita desbordamiento para l y r grandes
        int m = l + (r - l) / 2;
        // Ordena recursivamente la primera y segunda mitades
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        // Fusiona las mitades ordenadas
        merge(arr, l, m, r);
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    // Obtenemos el rango y el tamaño del comunicador MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        int arr[] = {12, 11, 13, 5, 6, 7, 1, 4, 8, 9, 2, 10};
        int n = sizeof(arr) / sizeof(arr[0]);

        printf("Arreglo original: ");
        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");

        int subarr_size = n / size;
        // Distribuye subarreglos a otros procesos
        for (int i = 1; i < size; i++) {
            MPI_Send(&subarr_size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(arr + i * subarr_size, subarr_size, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        // Realiza el ordenamiento local por fusion en el proceso
        mergeSort(arr, 0, n - 1);
        // Fusiona los subarreglos ordenados recibidos de otros procesos
        for (int i = 1; i < size; i++) {
            int recv_arr[subarr_size];
            MPI_Recv(recv_arr, subarr_size, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            merge(arr, i * subarr_size, (i + 1) * subarr_size - 1, n - 1);
        }

        printf("Arreglo ordenado: ");
        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");
    } else {
        int subarr_size;
        MPI_Recv(&subarr_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int subarr[subarr_size];
        MPI_Recv(subarr, subarr_size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // Realiza el ordenamiento local por fusion en cada proceso 
        mergeSort(subarr, 0, subarr_size - 1);
        // Envia el subarreglo ordenado de vuelta al proceso maestro
        MPI_Send(subarr, subarr_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}