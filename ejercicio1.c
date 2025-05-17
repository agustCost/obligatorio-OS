//test 
#include <pthread.h>
#include <stdio.h>

int array1[5] = {1, 2, 3, 4, 5};
int array2[5] = {1, 2, 3, 4, 5};

int resultados[3]; // Para guardar resultados de los primeros 3 hilos
int resultado_parcial;
int resultado_final;

void* hilo_suma(void* arg) {
    int idx = *(int*)arg;
    int suma = array1[idx] + array2[idx];
    printf("Hilo %d: Suma %d + %d = %d\n", idx + 1, array1[idx], array2[idx], suma);
    resultados[idx] = suma;
    pthread_exit(NULL);
}

void* hilo_multiplicacion(void* arg) {
    resultado_parcial = *(int*)arg;
    printf("Hilo 4: Suma total = %d\n", resultado_parcial);

    int mult = resultado_parcial * array1[3] * array2[3];
    printf("Hilo 4: Multiplicación %d * %d * %d = %d\n", resultado_parcial, array1[3], array2[3], mult);
    resultado_parcial = mult;
    pthread_exit(NULL);
}

void* hilo_final(void* arg) {
    int res = resultado_parcial + array1[4] + array2[4];
    printf("Hilo 5: %d + %d + %d = %d\n", resultado_parcial, array1[4], array2[4], res);
    resultado_final = res;
    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[5];
    int indices[3] = {0, 1, 2};

    // Crear y esperar los primeros 3 hilos
    for (int i = 0; i < 3; i++) {
        pthread_create(&hilos[i], NULL, hilo_suma, &indices[i]);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(hilos[i], NULL);
    }

    // Sumar resultados y lanzar hilo 4
    int suma_total = resultados[0] + resultados[1] + resultados[2];
    pthread_create(&hilos[3], NULL, hilo_multiplicacion, &suma_total);
    pthread_join(hilos[3], NULL);

    // Lanzar hilo 5
    pthread_create(&hilos[4], NULL, hilo_final, NULL);
    pthread_join(hilos[4], NULL);

    printf("Resultado final: %d\n", resultado_final);

    return 0;
}

