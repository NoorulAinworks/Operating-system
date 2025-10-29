/*
---------------------------------------------------------------
Name:        Noor ul Ain
Registration No:  23-NTU-CS-1221
Task Title:  Task 3 – Number Info Thread

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread function prototype
void* numberInfoThread(void* arg);

int main() {
    pthread_t thread;   // Thread handle
    int number;         // Number entered by the user

    // Get input from the user
    printf("Enter an integer: ");
    scanf("%d", &number);

    // Create the thread and pass the number as argument
    int status = pthread_create(&thread, NULL, numberInfoThread, (void*)&number);
    if (status != 0) {
        fprintf(stderr, "Error: Unable to create thread.\n");
        exit(1);
    }

    // Wait for the thread to finish execution
    pthread_join(thread, NULL);

    // Print completion message
    printf("Main thread: Work completed.\n");

    return 0;
}

// Thread function definition
void* numberInfoThread(void* arg) {
    int num = *(int*)arg;  // Retrieve integer argument

    // Compute square and cube
    int square = num * num;
    int cube = num * num * num;

    // Display results
    printf("\nThread: Number = %d\n", num);
    printf("Thread: Square = %d\n", square);
    printf("Thread: Cube   = %d\n\n", cube);

    pthread_exit(NULL);
}
