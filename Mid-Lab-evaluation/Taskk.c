
//Write a C program that calculates array sum using multiple threads:

 

// 1.  Create an array of 20 integers: {1, 2, 3, ..., 20}

// 2.  Create 4 threads, each calculating sum of 5 elements:   Thread 1: elements 0-4 (sum of 1 to 5)

   // Thread 2: elements 5-9 (sum of 6 to 10)

  // Thread 3: elements 10-14 (sum of 11 to 15)

  // Thread 4: elements 15-19 (sum of 16 to 20)

// Pass the starting index and count to each thread using a structure:

// 4.  Each thread prints its partial sum

//  Main thread collects all return values and calculates total sum //
                         // Name: Noor ul Ain//
                         //Reg no: 23-NTU-CS-1221//
                         //BSSE-A//
                         //5th semester//
                         //Submitted to sir Nasir//----
#include <stdio.h>
#include <pthread.h>

#define sIZE 20
#define thread_count 4

int arr[sIZE];
    
typedef struct {
    int Start;
     int end;
          int sum;
} ThreadData;
                          
void* calculating_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->sum = 0;


    for (int i = data->Start; i <= data->end; i++) {
                   data->sum += arr[i];
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[thread_count];
    ThreadData threadData[thread_count];
    int totalsum = 0;            

    for (int i = 0; i < sIZE; i++)
        arr[i] = i + 1;

    for (int i = 0; i < thread_count; i++) {
        threadData[i].Start = i * 5;
        threadData[i].end = (i * 5) + 4;
        pthread_create(&threads[i], NULL, calculating_sum, &threadData[i]);
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
        printf("Thread handling elements %d to %d: Partial Sum = %d\n",
               threadData[i].Start, threadData[i].end, threadData[i].sum);
        totalsum += threadData[i].sum;
    }

   printf("\ntotal sum of array=%d\n",totalsum);
}


//this program is is created to calculate the sum of 20 integers present in the  array
//four threads have been used here
//these threads are running concurrently
//then the main function collects the results from threads and adds it into Totalsum variable