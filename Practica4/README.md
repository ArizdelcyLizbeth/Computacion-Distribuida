# Algoritmo de ordenamiento por mezcla (Merge Sort)

## Descripción de la práctica y cómo funciona la solución implementada:
El algoritmo propuesto implementa el algoritmo de ordenación Merge Sort utilizando el paradigma de programación paralela con MPI (Message Passing Interface). La idea principal es dividir el arreglo en subarreglos, distribuirlos entre procesos MPI y luego combinar los resultados ordenados para obtener el arreglo final ordenado.

## Solución implementada:

1. **División del arreglo:**
   En el proceso con rango 0, el arreglo original se divide en subarreglos de tamaño igual, y se envía cada subarreglo a los procesos secundarios usando `MPI_Send`.

2. **Ordenación local:**
   Cada proceso secundario realiza la ordenación local de su subarreglo utilizando la función `mergeSort`.

3. **Combinación de resultados:**
   Después de la ordenación local, los subarreglos ordenados se envían de vuelta al proceso con rango 0 usando `MPI_Send`. El proceso con rango 0 recibe los subarreglos ordenados y realiza la fusión (`merge`) de estos subarreglos para obtener el arreglo final ordenado.

4. **Impresión del resultado:**
   El proceso con rango 0 imprime el arreglo original y el arreglo ordenado.

5. **MPI Finalize:**
   Se finaliza el entorno MPI al final del programa.

## Partes clave del código y sus funciones:

1. **merge:** Función que fusiona dos subarreglos ordenados en uno solo.
2. **mergeSort:** Función recursiva que implementa el algoritmo de ordenamiento por fusión.
3. **MPI_Init:** Inicializa el entorno MPI.
4. **MPI_Comm_rank** y **MPI_Comm_size:** Obtiene el rango y el tamaño del comunicador MPI.

## Proceso Maestro:

- Inicialización y presentación del arreglo original.
- Cálculo del tamaño de los subarreglos y distribución a los procesos trabajadores.
- Ordenamiento local por fusión en el proceso maestro.
- Recepción y fusión de los subarreglos ordenados de los procesos trabajadores.
- Impresión del arreglo final ordenado.

## Procesos Trabajadores:

- Recepción del tamaño del subarreglo y del subarreglo en sí.
- Ordenamiento local por fusión del subarreglo.
- Envío del subarreglo ordenado de vuelta al proceso maestro.

## Conclusiones:
Este enfoque paralelo permite dividir la carga de trabajo entre múltiples procesos, acelerando el tiempo de ejecución en comparación con una implementación secuencial. La comunicación entre procesos se realiza a través de mensajes MPI, lo que facilita la coordinación entre ellos. La eficiencia de este enfoque depende del equilibrio en la carga de trabajo y de la eficiencia de la implementación del algoritmo de ordenación.

## Cómo compilar y ejecutar:

```bash
mpicc -o Practica4 Practica4.c
mpirun -np 4 ./Practica4