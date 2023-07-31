/* @CS3600

   @ Takehome program outline

   @ 03/03/22

   Donot change the given outline code

   @Your name: Kero Lee

   @Time taken for completing the program: 2 hours 20 minutes

----------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include <semaphore.h>


pthread_t tid;

pthread_t writerthreads[50], readerthreads[50];

sem_t x,y;		// initiate semaphore
int readercount = 0;
int writercount = 0;

void *reader(void* param)
{
	sem_wait(&x);
	readercount++;
	
	if(readercount == 1){
		sem_wait(&y);
	}
	
	sem_post(&x);
	
	printf("%d reader in CS to read\n", readercount);
	sleep(1);
	sem_wait(&x);
	readercount--;
	
	if(readercount == 0){
		sem_post(&y);
	}
	sem_post(&x);
	
	printf("%d Reader leaving CS\n", readercount+1);

	return NULL;
}

void *writer(void* param)

{
	sleep(2);
	sem_wait(&y);
	writercount++;
	printf("Writer [%d] writing in CS\n", writercount);
	sem_post(&y);
	return NULL;
}

int main()
{
	int r1, w1, i, j;
	sem_init(&x,0,1);
	sem_init(&y,0,1);
	
	printf("Enter the number of readers:");
	scanf("%d", &r1);
	
	printf("Enter the number of writers:");
	scanf("%d", &w1);

	printf("\n");

	for (i = 0; i < r1; i++)
	{
		pthread_create(&readerthreads[i], NULL, reader, NULL);
	}

	for (j = 0; j < w1; j++)
	{
		pthread_create(&writerthreads[j], NULL, writer, NULL);
	}

	for (i = 0; i < r1; i++)
	{
		pthread_join(readerthreads[i], NULL);
	}

	for (j = 0; j < w1; j++)
	{
		pthread_join(writerthreads[j], NULL);
	}

}