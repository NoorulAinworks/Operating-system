#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define STATIONS 2
#define CARS 8

sem_t washStations;
pthread_mutex_t lock;
int waiting = 0;   

void* car(void* num)
{
    int id = *(int*)num;

    pthread_mutex_lock(&lock);
    waiting++;
    printf("Car %d is waiting | Queue: %d\n", id, waiting);
    pthread_mutex_unlock(&lock);

   
    sem_wait(&washStations);

    pthread_mutex_lock(&lock);
    waiting--;
    printf("Car %d is being washed | Queue: %d\n", id, waiting);
    pthread_mutex_unlock(&lock);

    
    sleep(3);

    printf("Car %d has finished washing\n", id);

  
    sem_post(&washStations);

    return NULL;
}

int main()
{
    pthread_t c[CARS];
    int ids[CARS];

    sem_init(&washStations, 0, STATIONS);
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < CARS; i++)
    {
        ids[i] = i + 1;
        pthread_create(&c[i], NULL, car, &ids[i]);
        sleep(1);   
    }

    for (int i = 0; i < CARS; i++)
        pthread_join(c[i], NULL);

    sem_destroy(&washStations);
    pthread_mutex_destroy(&lock);

    return 0;
}
