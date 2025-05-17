#include <stdio.h>
#include <pthread.h>

int array1[5] = {1, 2, 3, 4, 5};
int array2[5] = {1, 2, 3, 4, 5};
int resultados[3];  // resultados de hilos 1, 2, 3
int resultado_hilo4;

void* sumar_posicion(void* arg) {
    int pos = *(int*)arg;
    resultados[pos] = array1[pos] + array2[pos];
    printf("Hilo %d: Suma %d + %d = %d\n", pos + 1, array1[pos], array2[pos], resultados[pos]);
    return NULL;
}

void* hilo4(void* arg) {
    int suma = *(int*)arg;
    resultado_hilo4 = suma * array1[3] * array2[3];
    printf("Hilo 4: Suma total = %d\n", suma);
    printf("Hilo 4: Multiplicación %d * %d * %d = %d\n", suma, array1[3], array2[3], resultado_hilo4);
    return NULL;
}

void* hilo5(void* arg) {
    int valor = *(int*)arg;
    int final = valor + array1[4] + array2[4];
    printf("Hilo 5: %d + %d + %d = %d\n", valor, array1[4], array2[4], final);
    printf("Resultado final: %d\n", final);
    return NULL;
}

int main() {
    pthread_t hilos[5];
    int posiciones[3] = {0, 1, 2};

    // Crear hilos 1, 2, 3
    for (int i = 0; i < 3; i++) {
        pthread_create(&hilos[i], NULL, sumar_posicion, &posiciones[i]);
    }

    // Esperar hilos 1, 2, 3
    for (int i = 0; i < 3; i++) {
        pthread_join(hilos[i], NULL);
    }

    int suma_total = resultados[0] + resultados[1] + resultados[2];

    // Crear y esperar hilo 4
    pthread_create(&hilos[3], NULL, hilo4, &suma_total);
    pthread_join(hilos[3], NULL);

    // Crear y esperar hilo 5
    pthread_create(&hilos[4], NULL, hilo5, &resultado_hilo4);
    pthread_join(hilos[4], NULL);

    return 0;
}
