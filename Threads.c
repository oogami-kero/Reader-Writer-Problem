/*Kero Lee - CS3600 Homework 2
  Program to implement threads*/

#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>

// define array size and thread macros
#define MAX_THREADS 4
#define ARRAY_SIZE 40

// define array
int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
			14 ,15, 16, 17, 18, 19, 20, 21, 22, 23, 
			24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 
			34, 35, 36, 37, 38, 39, 40};
int sum[4] = { 0 };
int partition = 0;
int arrays = 0;
  
void* sum_of_array_elements(void* arg) {
	// split array into 4 partitions
	int thread_part = partition++;
  
	for (int i = thread_part * (ARRAY_SIZE / 4); i < (thread_part + 1) * (ARRAY_SIZE / 4); i++)
		sum[thread_part] += a[i];
}
  
int main() {
  
	pthread_t threads[MAX_THREADS];
  
	// create 4 threads
	for (int i = 0; i < MAX_THREADS; i++)
		pthread_create(&threads[i], NULL, sum_of_array_elements, (void*)NULL);
  
	// when threads complete, join 
	for (int i = 0; i < MAX_THREADS; i++)
		pthread_join(threads[i], NULL);
  
	// get sum
	for (int i = 0; i < MAX_THREADS; i++)
		arrays += sum[i];
	
	printf("Threads have finished tasks successfully\n");
	printf("The total sum of the given array is: %d\n",arrays);
  
	return 0;
}
