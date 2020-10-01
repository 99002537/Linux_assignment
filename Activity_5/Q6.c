#include <stdio.h>
#include <pthread.h>
#include <string.h>
#define MAX_ARRAY 20
#define MAX_THREAD 5
int arr[] = { 1, 3, 6, 9, 12, 20, 26, 31, 39, 43, 52, 64, 77, 90, 101, 134, 158, 199, 224, 250}; 
int sum[5] = { 0 }; 
int m = 0; 
void * sum_of_array(void* arg) 
{ 
    int thread_part = m++; 
    for (int i = thread_part * (MAX_ARRAY / 5); i < (thread_part + 1) * (MAX_ARRAY / 4); i++) {
        sum[thread_part] += arr[i]; 
    }
} 
 
int main() 
{ 
  int total_sum = 0;
    pthread_t threads[MAX_THREAD]; 
    for (int i = 0; i < MAX_THREAD; i++){ 
        pthread_create(&threads[i], NULL, sum_of_array, (void*)NULL);
        }  
    for (int i = 0; i < MAX_THREAD; i++){
        pthread_join(threads[i], NULL); }
    for (int i = 0; i < MAX_THREAD; i++) {
        total_sum += sum[i]; }
    printf("sum is %d\n",total_sum);
return 0; 
} 