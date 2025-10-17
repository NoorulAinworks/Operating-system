 #include <stdio.h>
 #include <pthread.h>
 //Passing Multiple Data
 typedef struct {
 float CGPA;
 char* message;
 } ThreadData;
 void* printData(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    printf("Thread  %f says: %s\n", data->CGPA, data->message); 
    return NULL;
 }
 int main() {
    pthread_t t1, t2;
    ThreadData data1 = {3.01, "Noorulain"};
   
    pthread_create(&t1, NULL, printData, &data1);
   
    pthread_join(t1, NULL);
    
    printf("All threads done.\n");
    return 0;
 }