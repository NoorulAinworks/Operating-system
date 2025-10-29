/*
---------------------------------------------------------------
Name:        Noor ul Ain
Registration No:  23-NTU-CS-1221
Task Title:  Task 1 – Thread Information Display


*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>     // for sleep()
#include <time.h>       // for random seed

#define NUM_THREADS 5   // Number of threads to create

// Thread function prototype
void* threadFunction(void* arg);

int main() {
    pthread_t threads[NUM_THREADS];
    int threadNumbers[NUM_THREADS];
    int i;

    // Seed the random number generator
    srand(time(NULL));

    printf("Creating %d threads...\n\n", NUM_THREADS);

    // Create 5 threads
    for (i = 0; i < NUM_THREADS; i++) {
        threadNumbers[i] = i + 1;  // Store thread number (1–5)
        int status = pthread_create(&threads[i], NULL, threadFunction, &threadNumbers[i]);
        
        if (status != 0) {
            fprintf(stderr, "Error: Unable to create thread %d\n", i + 1);
            exit(1);
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nAll threads have completed execution.\n");
    return 0;
}

// Thread function definition
void* threadFunction(void* arg) {
    int threadNum = *(int*)arg;
    pthread_t threadID = pthread_self();

    // Generate random sleep time between 1–3 seconds
    int sleepTime = (rand() % 3) + 1;

    printf("Thread %d started. Thread ID: %lu\n", threadNum, threadID);
    printf("Thread %d will sleep for %d second(s)...\n", threadNum, sleepTime);
    
    sleep(sleepTime); // Simulate some work

    printf("Thread %d completed after %d second(s).\n\n", threadNum, sleepTime);

    pthread_exit(NULL);
}
