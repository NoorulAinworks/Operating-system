/*
---------------------------------------------------------------
Name:        Noor ul Ain
Registration No:  23-NTU-CS-1221
Task Title:  Task 5 – Struct-Based Thread Communication

 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Structure Definition
typedef struct {
    int student_id;
    char name[50];
    float gpa;
} Student;

// Structure for thread return value
typedef struct {
    int is_deans_list;  // 1 if eligible, 0 otherwise
} Result;

// Thread function prototype
void* studentThread(void* arg);

int main() {
    pthread_t threads[3];     // Array to hold 3 thread identifiers
    Student students[3];      // Array of student structures
    Result* results[3];       // Pointers to hold thread return values
    int deanCount = 0;        // Counter for Dean's List students

    // Initialize student data
    students[0].student_id = 101;
    strcpy(students[0].name, "Ali");
    students[0].gpa = 3.7;

    students[1].student_id = 102;
    strcpy(students[1].name, "Sara");
    students[1].gpa = 3.2;

    students[2].student_id = 103;
    strcpy(students[2].name, "Bilal");
    students[2].gpa = 3.9;

    printf("=== Student Database System ===\n\n");

    // Create threads for each student
    for (int i = 0; i < 3; i++) {
        int status = pthread_create(&threads[i], NULL, studentThread, (void*)&students[i]);
        if (status != 0) {
            fprintf(stderr, "Error: Unable to create thread %d\n", i + 1);
            exit(1);
        }
    }

    // Wait for threads to finish and collect results
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], (void**)&results[i]);
        if (results[i]->is_deans_list == 1)
            deanCount++;
        free(results[i]);  // Free dynamically allocated memory from thread
    }

    // Display Dean's List count
    printf("Main thread: %d student(s) made the Dean’s List.\n", deanCount);

    return 0;
}

// Thread function definition
void* studentThread(void* arg) {
    Student* s = (Student*)arg;
    Result* res = malloc(sizeof(Result));

    if (res == NULL) {
        fprintf(stderr, "Memory allocation failed in thread.\n");
        pthread_exit(NULL);
    }

    printf("Student ID: %d\n", s->student_id);
    printf("Name: %s\n", s->name);
    printf("GPA: %.2f\n", s->gpa);

    // Check Dean's List eligibility
    if (s->gpa >= 3.5) {
        printf("Status: Dean’s List ✅\n\n");
        res->is_deans_list = 1;
    } else {
        printf("Status: Not on Dean’s List ❌\n\n");
        res->is_deans_list = 0;
    }

    pthread_exit((void*)res);
}
