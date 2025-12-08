#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_DOWNLOADS 3
#define TOTAL_FILES 8

sem_t downloadSlots;

void* download(void* num)
{
    int id = *(int*)num;

    
    sem_wait(&downloadSlots);

    printf("Download %d started\n", id);

    
    sleep(rand() % 5 + 1);

    printf("Download %d finished\n", id);

    
    sem_post(&downloadSlots);

    return NULL;
}

int main()
{
    pthread_t d[TOTAL_FILES];
    int ids[TOTAL_FILES];

    sem_init(&downloadSlots, 0, MAX_DOWNLOADS);  

    for (int i = 0; i < TOTAL_FILES; i++)
    {
        ids[i] = i + 1;
        pthread_create(&d[i], NULL, download, &ids[i]);
        sleep(1);   
    }

    for (int i = 0; i < TOTAL_FILES; i++)
    {
        pthread_join(d[i], NULL);
    }

    sem_destroy(&downloadSlots);

    return 0;
}
