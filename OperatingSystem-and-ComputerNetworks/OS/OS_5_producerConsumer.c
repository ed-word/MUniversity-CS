#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>

#define bufferSize 10
int buffer[bufferSize];

sem_t full;
sem_t empty;
sem_t mutex;
int read=0;
int write=0;

int p,c;

void *produce(void *ppp)
{
	int x;
	for(int i=0;i<p;i++)
	{
		printf("Enter value to produce: ");
		scanf("%d",&x);

		sem_wait(&empty);		
		sem_wait(&mutex);
		buffer[(write++)%bufferSize] = x;
		sem_post(&mutex);
		sem_post(&full);
	}
	pthread_exit(NULL);
}

void *consume(void *ppp)
{
	int x;
	for(int i=0;i<c;i++)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		x = buffer[(read++)%bufferSize];
		printf("\nConsumed Value: %d\n",x);
		sem_post(&mutex);
		sem_post(&empty);
	}
	pthread_exit(NULL);
}

int main()
{
	pthread_t prodThread;
	pthread_t consThread;

	sem_init(&full,1,0);
	sem_init(&empty,1,bufferSize);
	sem_init(&mutex,1,1);

	printf("Enter number of objects to produce: ");
	scanf("%d",&p);
	printf("Enter number of objects to consume: ");
	scanf("%d",&c);

	pthread_create(&prodThread,NULL,&produce,NULL);
	pthread_create(&consThread,NULL,&consume,NULL);

	pthread_join(prodThread,NULL);
	pthread_join(consThread,NULL);

	return 0;
}