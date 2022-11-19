#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include <assert.h>

#define BILLION 1000000000L


void countA(){
    long int i = 1;
    while (i <= 4294967296){
        i++;
    }
}
void countB(){
    long int j = 1;
    while (j <= 4294967296){
        j++;
    }
}
void countC(){
    long int k = 1;
    while (k <= 4294967296){
        k++;
    }
}


void *Thr_A(void *arg) {
    // myret_t *r = malloc(sizeof(myret_t));
    printf("Starting Thread A\n");
    uint64_t diff;
	struct timespec start, end;

	/* measure monotonic time */
	clock_gettime(CLOCK_MONOTONIC, &start);	/* mark start time */
	countA();	/* do stuff */
	clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed time(A) = %llu nanoseconds\n", (long long unsigned int) diff);
}

void *Thr_B(void *arg) {
    // myret_t *r = malloc(sizeof(myret_t));
    printf("Starting Thread B\n");
    uint64_t diff;
	struct timespec start, end;

	/* measure monotonic time */
	clock_gettime(CLOCK_MONOTONIC, &start);	/* mark start time */
	countB();	/* do stuff */
	clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed time(B) = %llu nanoseconds\n", (long long unsigned int) diff);
}

void *Thr_C(void *arg) {
    // myret_t *r = malloc(sizeof(myret_t));
    printf("Starting Thread C\n");
    uint64_t diff;
	struct timespec start, end;

	/* measure monotonic time */
	clock_gettime(CLOCK_MONOTONIC, &start);	/* mark start time */
	countC();	/* do stuff */
	clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed time(C) = %llu nanoseconds\n", (long long unsigned int) diff);
}
int main(int argc, char* argv[]){
    pthread_t A;
    pthread_t B;
    pthread_t C;

    pthread_attr_t tattrA;
    pthread_attr_t tattrB;
    pthread_attr_t tattrC;

    pthread_attr_setschedpolicy(&tattrA, SCHED_OTHER);
    pthread_attr_setschedpolicy(&tattrB, SCHED_RR);
    pthread_attr_setschedpolicy(&tattrC, SCHED_FIFO);
    // myret_t *m;
    pthread_create(&A, &tattrA, Thr_A, NULL); 
    pthread_create(&B, &tattrB, Thr_B, NULL);
    pthread_create(&C, &tattrC, Thr_C, NULL);

    pthread_join(A, NULL); 
    pthread_join(B, NULL);
    pthread_join(C, NULL);
    // printf("returned %d\n", m->x); 
    return 0;
}