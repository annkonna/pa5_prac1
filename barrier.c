#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "barrier.h"

#define COUNT 100000
#define THREADS 9
#define OFFSET 0x1134A

struct Barrier {
    pthread_mutex_t lock;
    pthread_cond_t barrier;
    int nwaiting;
    int nthreads;
};

int value;
pthread_mutex_t ctrLock;

/*
 * barrier_wait() should do the following:
 * 1. The number of threads waiting on the barrier (nwaiting) must be incremented, 
 *    and compared against the number of threads the barrier is configured to wait for (nthreads)
 * 2. If nthread == nwaiting, the barrier condition has been met, and all threads should be released.
 *    Otherwise, the current thread should block until some thread satisfies that condition. 
 * 
 * Note 1: You must use lock to protect the state of the barrier, and barrier as the condition 
 *         variable on which the waiting threads block. 
 * Note 2: Your barrier implementation does not have to operate more than once. Once a barrier 
 *         has released its threads, its work is done.
 */
void barrier_wait(Barrier b) {
    pthread_mutex_lock(&b->lock);
    b->nwaiting += 1;
    if (b->nthreads == b->nwaiting){
        pthread_cond_broadcast(&b->barrier);
    }
    while (b->nthreads != b->nwaiting){
        pthread_cond_wait(&b->barrier, &b->lock);
    }
    pthread_mutex_unlock(&b->lock);
}


/* This thread will simply add COUNT to the global value, one at a
 * time. */
void *counter(void *arg) {
    barrier_wait(arg);
    for (int i = 0; i < COUNT; i++) {
        pthread_mutex_lock(&ctrLock);
        value++;
        pthread_mutex_unlock(&ctrLock);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    Barrier b = calloc(1, sizeof(struct Barrier));

    value = 0;
    pthread_mutex_init(&ctrLock, NULL);
    
    pthread_mutex_init(&b->lock, NULL);
    pthread_cond_init(&b->barrier, NULL);

    pthread_t t[THREADS];
    int result;

    b->nthreads = THREADS;
    b->nwaiting = 0;
    for (int i = 0; i < THREADS; i++) {
        if ((result = pthread_create(&t[i], NULL, counter, b)) != 0) {
            fprintf(stderr, "pthread_create: %s\n", strerror(result));
            return 1;
        }
    }

    /* Set the global value to OFFSET, as a place for the counting to
     * start.  If the threads above have already been released, this
     * will force a failure. */
    value = OFFSET;

    for (int i = 0; i < THREADS; i++) {
        pthread_join(t[i], NULL);
    }

    if (value == COUNT * THREADS + OFFSET) {
        printf("passed: value = %d, EXPECTED = %d\n", value, COUNT * THREADS + OFFSET);
    } else {
        printf("failed: value = %d, EXPECTED = %d\n", value, COUNT * THREADS + OFFSET);
        return 1;
    }

    return 0;
}
