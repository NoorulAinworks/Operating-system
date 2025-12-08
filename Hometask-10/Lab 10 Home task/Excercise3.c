#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define K 3        
#define STUDENTS 7 

sem_t computers;
pthread_mutex_t lock;
int pc[K];   

void* student(void* num)
{
    int id = *(int*)num;

    
    sem_wait(&computers);

    pthread_mutex_lock(&lock);

   
    int myPC = -1;
    for (int i = 0; i < K; i++)
    {
        if (pc[i] == 0)
        {
            pc[i] = id;
            myPC = i;
            break;
        }
    }

    printf("Student %d is using Computer %d\n", id, myPC + 1);

    pthread_mutex_unlock(&lock);

    
    sleep(rand() % 4 + 1);

    pthread_mutex_lock(&lock);

    printf("Student %d left Computer %d\n", id, myPC + 1);
    pc[myPC] = 0;   

    pthread_mutex_unlock(&lock);

    
    sem_post(&computers);

    return NULL;
}

int main()
{
    pthread_t s[STUDENTS];
    int ids[STUDENTS];

    sem_init(&computers, 0, K);
    pthread_mutex_init(&lock, NULL);

    
    for (int i = 0; i < K; i++)
        pc[i] = 0;

    for (int i = 0; i < STUDENTS; i++)
    {
        ids[i] = i + 1;
        pthread_create(&s[i], NULL, student, &ids[i]);
        sleep(1);
    }

    for (int i = 0; i < STUDENTS; i++)
        pthread_join(s[i], NULL);

    sem_destroy(&computers);
    pthread_mutex_destroy(&lock);

    return 0;
}
