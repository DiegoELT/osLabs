#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define NUM_HILOS 8

void *printHola (void *hilo_id)
{
long t;
t = (long)hilo_id;

printf("Hola desde el hilo %ld \n",t);
pthread_exit(NULL);
}


int main ()
{
int i,j,k,rc;
long t;
pthread_t arreglo_hilos[NUM_HILOS];

for (t=0;t<NUM_HILOS;t++)
{

rc=pthread_create(&arreglo_hilos[t],NULL,printHola,(void*)t);
if (rc){printf("ERROR al crear el hilo %ld codigo %d \n",t,rc);
	exit(-1);}

}


pthread_exit(NULL);
return 0;
}
