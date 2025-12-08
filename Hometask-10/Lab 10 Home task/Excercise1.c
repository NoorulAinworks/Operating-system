#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define N 3          
#define TOTAL 8    

sem_t rooms;         
int occupied = 0;   
pthread_mutex_t lock;

void* person(void* num)
{
    int id = *(int*)num;

   
    sem_wait(&rooms);

    pthread_mutex_lock(&lock);
    occupied++;
    printf("Person %d entered | Occupied Rooms: %d\n", id, occupied);
    pthread_mutex_unlock(&lock);

    
    sleep(rand() % 3 + 1);

    pthread_mutex_lock(&lock);
    occupied--;
    printf("Person %d left | Occupied Rooms: %d\n", id, occupied);
    pthread_mutex_unlock(&lock);

    
    sem_post(&rooms);

    return NULL;
}

int main()
{
    pthread_t p[TOTAL];
    int ids[TOTAL];

    sem_init(&rooms, 0, N);       
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < TOTAL; i++)
    {
        ids[i] = i + 1;
        pthread_create(&p[i], NULL, person, &ids[i]);
        sleep(1);   
    }

    for (int i = 0; i < TOTAL; i++)
    {
        pthread_join(p[i], NULL);
    }

    sem_destroy(&rooms);
    pthread_mutex_destroy(&lock);

    return 0;
}
