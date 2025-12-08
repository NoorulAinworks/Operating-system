#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define WORKERS 3
#define TASKS 10

sem_t workerPool;

void* task(void* num)
{
    int id = *(int*)num;

    
    sem_wait(&workerPool);

    printf("Task %d is being processed by a worker\n", id);

    
    sleep(rand() % 2 + 1);

    printf("Task %d is finished\n", id);

    
    sem_post(&workerPool);

    return NULL;
}

int main()
{
    pthread_t t[TASKS];
    int ids[TASKS];

    
    sem_init(&workerPool, 0, WORKERS);

    for (int i = 0; i < TASKS; i++)
    {
        ids[i] = i + 1;
        pthread_create(&t[i], NULL, task, &ids[i]);
        sleep(1);  
    }

    for (int i = 0; i < TASKS; i++)
    {
        pthread_join(t[i], NULL);
    }

    sem_destroy(&workerPool);

    return 0;
}
