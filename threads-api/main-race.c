#include <stdio.h>

#include "common_threads.h"

// The data race from the report on the shared variable balance is reported and correctly points to 2 balance++ lines in main and worker. It also shows the accesses are writes fom different threads, provides stack traces for each access and indicates no lock is held during the updates.

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int balance = 0;

void* worker(void* arg) {
    pthread_mutex_lock(&m);
    balance++;
    pthread_mutex_unlock(&m);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);

    pthread_mutex_lock(&m);
    balance++;
    pthread_mutex_unlock(&m);
    
    Pthread_join(p, NULL);
    return 0;
}
