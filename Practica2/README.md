# Algoritmo del Rey
## Descripción de la Práctica

El Algoritmo del Rey es un algoritmo de consenso distribuido que puede implementarse en C con MPI para manejar fallos bizantinos simulados. Cada nodo determina aleatoriamente su plan inicial (atacar o retirarse). Un subconjunto de nodos finge ser traidores, enviando información arbitraria durante la comunicación. Las rondas de comunicación continúan hasta alcanzar un consenso o hasta que se agoten las rondas máximas sin consenso.

## Solución Implementada

1. **Inicialización de MPI:**
   - Inicializamos MPI para obtener el número de nodos y el rango de cada proceso.

2. **Selección de Plan Inicial:**
   - Cada nodo elige aleatoriamente su plan inicial, considerando la posibilidad de ser un traidor.

3. **Rondas de Comunicación:**
   - Implementamos rondas de comunicación donde los nodos difunden sus planes y recopilan los planes de otros nodos.

4. **Votación y Consenso:**
   - Los nodos votan por el plan mayoritario recibido y actualizan su propio plan en consecuencia.

5. **Elección del Rey:**
   - Después de cada ronda de comunicación, si no se alcanza un consenso, se selecciona aleatoriamente a un nodo como rey.

6. **Manejo de Fallos:**
   - Se incluye lógica para detectar fallos cuando no se alcanza un consenso dentro de las rondas máximas o cuando se detecta un número excesivo de nodos traidores.

7. **Informe Final:**
   - Cada nodo informa su decisión final junto con su estado (leal o traidor).

8. **Finalización de MPI:**
   - Finalizamos MPI después de completar todas las operaciones.

## Conclusiones

El Algoritmo del Rey permite elegir un líder en un entorno distribuido incluso en presencia de nodos traidores que pueden enviar información incorrecta. A través de la comunicación y votación entre nodos, se logra un consenso o se gestiona adecuadamente la falta de consenso. Este algoritmo es útil para aplicaciones donde se requiere robustez frente a fallos bizantinos simulados.

## Cómo compilar y ejecutar:

```bash
mpicc -o Practica2 Practica2.c
mpirun -np 4 ./Practica2
```