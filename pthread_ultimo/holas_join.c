#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define NUM_HILOS 8

void *printHola (void *hilo_id)
{
long t;

t = (long)hilo_id;

printf("Hola desde el hilo %ld \n",t);
pthread_exit((void*)t);
}


int main ()
{
int i,j,k,rc;
long t;
void *status;
pthread_t arreglo_hilos[NUM_HILOS];
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);


for (t=0;t<NUM_HILOS;t++)
{

rc=pthread_create(&arreglo_hilos[t],&attr,printHola,(void*)t);
if (rc){printf("ERROR al crear el hilo %ld codigo %d \n",t,rc);
	exit(-1);}

}
pthread_attr_destroy(&attr);

for (t=0;t<NUM_HILOS;t++)
{
rc =pthread_join(arreglo_hilos[t],&status);
if (rc){printf("ERROR al unir el hilo %ld codigo %d \n",t,rc);
	exit(-1);}

printf("en Main: status %ld \n",(long)status);
}
printf("SAliendo \n");
pthread_exit(NULL);
return 0;
}
