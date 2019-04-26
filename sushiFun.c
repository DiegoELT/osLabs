#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define threadNum 5
#define maki 20
#define chewing 4
#define sleepTime 10

long int totalTime = 0;
int counted = 0; //Check if time has been added this iteration.
int printed = 0;
int chopsticks[] = {1,1,1,1,1};
int makis[] = {20,20,20,20,20}; 
int onlyOne[] = {0,0,0,0,0};

static pthread_barrier_t barrier;
pthread_mutex_t chopstickLock;

void restartMakis()
{
	for(int i = 0; i < threadNum; i++)
		makis[i] = maki;
}

void restartChopsticks()
{
	for(int i = 0; i < threadNum; i++)
		chopsticks[i] = 1;
	for(int i = 0; i < threadNum; i++)
		onlyOne[i] = 0;
	counted = 0;
	printed = 0;
}

int makisDone()
{
	for(int i = 0; i < threadNum; i++)
	{
		if(makis[i])
			return 0;
	}
	return 1;
}

int allOne()
{
	for(int i = 0; i < threadNum; i++)
	{
		if(!onlyOne[i])
			return 0;
	}
	return 1;
}

void printMak()
{
	for(int i = 0; i < threadNum; i++)
		printf("%d ", makis[i]);
	printf("\n");
}


void * eatSushi(void * threadID)
{	
	int ID;
	int i = 0;
	ID = *(int*)threadID;
	int chopsticksAIndex;
	int chopsticksBIndex;
	while(!makisDone())
	{
		restartChopsticks();
		pthread_barrier_wait(&barrier);	
		chopsticksAIndex = -1; //Not being held
		chopsticksBIndex = -1;

		//Try to reach first chopstick
		
		if(makis[ID])
		{
		pthread_mutex_lock(&chopstickLock);
			for(i = 0; i < threadNum; i++)
			{
				if(chopsticks[i])
				{
					chopsticks[i] = 0;
					chopsticksAIndex = i;
					onlyOne[ID] = 1;
					break;
				}
			}
		pthread_mutex_unlock(&chopstickLock);
	
		if(chopsticksAIndex != -1) //If he found a first one, he can try for a second one.
		{
			pthread_mutex_lock(&chopstickLock);
			for(i; i < threadNum; i++)
			{
				if(chopsticks[i])
				{
					chopsticks[i] = 0;
					chopsticksBIndex = i;
					break;
				}
			}
			pthread_mutex_unlock(&chopstickLock);
		}
		}

		pthread_barrier_wait(&barrier);

		if(allOne()) continue; //When all have tried picking, if all one, it loops to the next iteration.

		if(chopsticksAIndex != -1 && chopsticksBIndex != -1)
		{
			makis[ID] -= 1;
			if(!counted)
			{
				totalTime += chewing;
				counted = 1;
			}
			printf("El filosofo %d esta comiendo con los palitos %d y %d \n", ID, chopsticksAIndex, chopsticksBIndex);
		}

		else
			printf("El filosofo %d esta charlando. \n", ID);
		
		pthread_barrier_wait(&barrier);
		
		//Print how the meal is going.

		pthread_mutex_lock(&chopstickLock);
		if(!printed)
		{
			printed = 1;
			printf("Dinner currently goes like\n");
			printMak();
		}
		pthread_mutex_unlock(&chopstickLock);
		usleep(sleepTime);
	}

}

int main()
{
	printf("Philosophers Dining\n");	
	pthread_t philosophers[threadNum];
	pthread_barrier_init(&barrier, NULL, threadNum);
	
	for(int k = 0; k < 20; k++)
	{
		for(int j = 0; j < threadNum; j++)
		{
			int *tid;
			tid = (int*) malloc(sizeof(int));
			*tid = j;
			pthread_create(&philosophers[j], NULL, eatSushi, (void*) tid);
		}

		for(int i = 0; i < threadNum; i++)
			pthread_join(philosophers[i], NULL);

		restartMakis();
	}

	printf("Tiempo promedio de cena: %f horas. \n", (double)(totalTime/(60.0 * 20.0)));
	return 0;
}
