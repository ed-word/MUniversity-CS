#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>

#define numPhil 5
sem_t forks[numPhil];
sem_t mutex;
pthread_t philosopher[numPhil];
int philID[numPhil];

void *dine(void *i)
{
	int *num = i, flag=0;
	int id = *num;
	printf("Philosopher %d: Thinking\n",id);

	while(1)
	{
		//Philosopher acquires mutex lock before picking up fork
		sem_wait(&mutex);

		//Left fork
		flag = sem_trywait(&forks[id]);					
		if(flag==-1)	//Failed to lock fork, release mutex lock
		{
			sem_post(&mutex);
			continue;
		}
		printf("Philosopher %d: Picked up left fork\n",id);

		//Right fork
		flag = sem_trywait(&forks[(id+1)%numPhil]);		
		if(flag==-1)	//Failed to lock fork, release mutex lock & left fork
		{
			sem_post(&forks[id]);
			printf("Philosopher %d: Failed to get right fork, kept left fork\n",id);
			sem_post(&mutex);
			continue;
		}

		printf("Philosopher %d: Has both left & right forks\n",id);
		printf("Philosopher %d: Eating\n",id);

		//Release locks and forks
		sem_post(&mutex);
		sem_post(&forks[id]);
		sem_post(&forks[(id+1)%numPhil]);
		break;
	}
	printf("Philosopher %d: Finished eating, now thinking\n",id);
	pthread_exit(NULL);
}

int main()
{
	int i,id;
	for(i=0;i<numPhil;i++)
		philID[i] = i;

	sem_init(&mutex,1,1);
	for(i=0;i<numPhil;i++)
		sem_init(&forks[i],1,1);
	
	for(i=0;i<numPhil;i++)
		pthread_create(&philosopher[i],NULL,&dine,&philID[i]);

	for(i=0;i<numPhil;i++)
		pthread_join(philosopher[i],NULL);

	return 0;
}