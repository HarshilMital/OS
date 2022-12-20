#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>

pthread_mutex_t forks[5];


void *phil(void *arg) {
    int* n = (int*)arg;
    // printf("%d\n", arg);
    while(1){

        // Philosopher is thinking
        printf("Philosopher %d is thinking\n", *n + 1);
        sleep(5);

        // Try to acquire forks
        if (*n % 2 == 0){
            pthread_mutex_lock(&forks[*n]);
            pthread_mutex_lock(&forks[(*n + 1) % 5]);
        }
        else{
            pthread_mutex_lock(&forks[(*n + 1) % 5]);
            pthread_mutex_lock(&forks[*n]);
        }
        

        // Philosopher is eating
        printf("Philosopher %d is eating with fork %d and %d\n", *n + 1, *n + 1, *n + 2);
        sleep(5);

        // Release forks
        pthread_mutex_unlock(&forks[*n]);
        pthread_mutex_unlock(&forks[(*n + 1) % 5]);
    }
}


int main(int argc, char* argv[]){
    pthread_t p[5];
    for (int i = 0; i < 5; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    for (int i = 0; i < 5; i++){
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&p[i], NULL, phil, arg); 
    }
    for (int i = 0; i < 5; i++){
        pthread_join(p[i], NULL);
    }
    for (int i = 0; i < 5; i++){
        pthread_mutex_destroy(&forks[i]);
    }
    return 0;
}