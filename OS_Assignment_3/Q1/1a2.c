#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include<unistd.h>
#include <stdlib.h>


#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[5];
sem_t mutex;
sem_t forks[5];

// void print_cur_state(){
//     printf("0:%d 1:%d 2:%d 3:%d 4:%d\n", state[0], state[1], state[2], state[3], state[4]);
// }


void* phil(void* num)
{
    while (1)
    {
        int* i = (int*)num;
        int n = *i;
        // printf("%d\n", n);
        sem_wait(&mutex);
        // printf("%d\n", n);

        sem_wait(&forks[n]);
        sem_wait(&forks[(n + 1) % 5]);
        printf("Philosopher %d acquired fork %d and fork %d\n", n, n, (n + 1) % 5);

        printf("Philosopher %d is eating\n", n);
        state[n] = 1;
        // print_cur_state();
        sleep(5);

        sem_post(&forks[n]);
        sem_post(&forks[(n + 1) % 5]);
        printf("Philosopher %d kept fork %d and fork %d\n", n, n, (n + 1) % 5);
        
        sem_post(&mutex);
        printf("Philosopher %d is thinking\n", n);
        state[n] = 0;
        // print_cur_state();
        sleep(1);
    }
}

int main()
{
    int i;
    pthread_t p[5];
    sem_init(&mutex, 0, 4);
    for (i = 0; i < 5; i++)
        sem_init(&forks[i], 0, 1);

    for (i = 0; i < 5; i++){
        int *arg = malloc(sizeof(*arg));
        *arg = i;

        pthread_create(&p[i], NULL, phil, arg);
    }
        
    for (i = 0; i < 5; i++)
        pthread_join(p[i], NULL);

    return 0;
}