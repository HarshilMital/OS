#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>

// typedef struct __myarg_t { 
//     int a;
//     int b;
// } myarg_t;

typedef struct __myret_t { 
    int x;
} myret_t;

void *mythread(void *arg) {
    // myarg_t *m = (myarg_t *) arg;
    // printf("%d %d\n", m->a, m->b);
    myret_t *r = malloc(sizeof(myret_t));
    // r->x = 1;
    // r->y = 2;
    int a = 1;
    int b = 2;
    r->x = a + b;
    return (void *) r;
}
int main(int argc, char *argv[]) {
    int rc;
    pthread_t p;
    myret_t *m;
    // myarg_t args;
    // args.a = 10;
    // args.b = 20;
    pthread_create(&p, NULL, mythread, NULL); 
    pthread_join(p, (void**) &m); 
    printf("returned %d\n", m->x); 
    return 0;
}