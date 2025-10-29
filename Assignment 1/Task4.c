/*
---------------------------------------------------------------
Name:        Noor ul Ain
Registration No:  23-NTU-CS-1221
Task Title:  Task 4 – Thread Return Values (Factorial Calculation)

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread function prototype
void* factorialThread(void* arg);

int main() {
    pthread_t thread;   // Thread handle
    int number;         // User input
    void* result;       // Pointer to hold thread return value

    // Input from user
    printf("Enter a number: ");
    scanf("%d", &number);

    // Create the thread and pass the number as an argument
    int status = pthread_create(&thread, NULL, factorialThread, (void*)&number);
    if (status != 0) {
        fprintf(stderr, "Error: Unable to create thread.\n");
        exit(1);
    }

    // Wait for the thread to complete and collect its return value
    pthread_join(thread, &result);

    // Retrieve the factorial value
    long long* factorialResult = (long long*)result;

    // Display result
    printf("Main thread: Factorial result received = %lld\n", *factorialResult);

    // Free dynamically allocated memory
    free(factorialResult);

    return 0;
}

// Thread function definition
void* factorialThread(void* arg) {
    int num = *(int*)arg;  // Retrieve number passed from main
    long long* factorial = malloc(sizeof(long long));  // Dynamic memory to return result

    if (factorial == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        pthread_exit(NULL);
    }

    *factorial = 1;  // Initialize factorial result

    printf("Thread: Calculating factorial of %d...\n", num);

    for (int i = 1; i <= num; i++) {
        *factorial *= i;
    }

    printf("Thread: Factorial of %d = %lld\n", num, *factorial);

    // Return the result pointer
    pthread_exit((void*)factorial);
}
