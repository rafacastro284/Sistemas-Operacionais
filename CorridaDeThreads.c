#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 100
#define MAX_COUNT 100

pthread_barrier_t barrier;
pthread_mutex_t lock;

int vencedor = -1;

void* corrida(void* arg) {
    int id = *(int*)arg;
    int contador = 0;

    //essa barreira espera todas as threads ficarem prontas
    pthread_barrier_wait(&barrier);

    while (contador < MAX_COUNT) {
        contador++;

            pthread_mutex_lock(&lock);
            printf("Thread %d -> %d\n", id, contador);
            pthread_mutex_unlock(&lock);

        usleep(rand() % 1000); // simula velocidades diferentes

        //verifica se há um vencedor, se sim, a thread sai
        pthread_mutex_lock(&lock);
        if (vencedor != -1) {
            pthread_mutex_unlock(&lock);
            pthread_exit(NULL);
        }

        if (contador == MAX_COUNT && vencedor == -1) {
            vencedor = id;
        }
        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, corrida, &ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    pthread_barrier_destroy(&barrier);

    printf("Corrida finalizada! A thread que venceu foi: %d\n", vencedor);

    return 0;
}