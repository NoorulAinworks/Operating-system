/*
---------------------------------------------------------------
Name:        Noor ul Ain
Registration No:  23-NTU-CS-1221
Task Title:  Task 2 – Personalized Greeting Thread

-----
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>  // for strcpy

// Thread function prototype
void* greetingThread(void* arg);

int main() {
    pthread_t thread;     // Thread handle
    char name[50];        // User's name

    // Ask for user's name
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);

    // Remove newline character from input (if any)
    name[strcspn(name, "\n")] = '\0';

    // Display main thread message
    printf("\nMain thread: Waiting for greeting...\n");

    // Create the greeting thread and pass the name as argument
    int status = pthread_create(&thread, NULL, greetingThread, (void*)name);

    if (status != 0) {
        fprintf(stderr, "Error: Unable to create thread.\n");
        exit(1);
    }

    // Wait for the thread to finish
    pthread_join(thread, NULL);

    // Display completion message
    printf("Main thread: Greeting completed.\n");

    return 0;
}

// Thread function definition
void* greetingThread(void* arg) {
    char* userName = (char*)arg;
    printf("Thread says: Hello, %s! Welcome to the world of threads.\n", userName);

    pthread_exit(NULL);
}
