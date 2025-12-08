#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define MAX_CARS 10


sem_t bridge_sem;


pthread_mutex_t print_mutex;


void* car_crossing(void* arg) {
    int car_id = *(int*)arg;

    
    sem_wait(&bridge_sem);

    
    pthread_mutex_lock(&print_mutex);
    printf("Car %d is entering the bridge...\n", car_id);
    pthread_mutex_unlock(&print_mutex);

    
    int crossing_time = rand() % 4 + 1;
    sleep(crossing_time);

    pthread_mutex_lock(&print_mutex);
    printf("Car %d has crossed the bridge in %d seconds.\n", car_id, crossing_time);
    pthread_mutex_unlock(&print_mutex);

    
    sem_post(&bridge_sem);

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    pthread_t cars[MAX_CARS];
    int car_ids[MAX_CARS];

    
    sem_init(&bridge_sem, 0, 3);

    
    pthread_mutex_init(&print_mutex, NULL);

    
    for (int i = 0; i < MAX_CARS; i++) {
        car_ids[i] = i + 1;
        pthread_create(&cars[i], NULL, car_crossing, &car_ids[i]);
        usleep(200000); 
    }

    
    for (int i = 0; i < MAX_CARS; i++) {
        pthread_join(cars[i], NULL);
    }

    
    sem_destroy(&bridge_sem);
    pthread_mutex_destroy(&print_mutex);

    return 0;
}
