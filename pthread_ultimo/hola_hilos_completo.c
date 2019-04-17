#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define NUM_HILOS 8

int contador_hilos;

void *printHola (void *thread_num )
{
long hilo;
double contador_local;
hilo=(long)thread_num;
//printf("Desde el hilo %ld , el contador es %d \n",hilo, contador_hilos);

printf("Hola Mundo desde el hilo %ld \n",hilo);
pthread_exit((void*)hilo);

}

int main()
{
int i,j,k,rc;
long t;
void *status;
pthread_attr_t attr;
contador_hilos=0;
pthread_t hilos[NUM_HILOS];

pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

printf("Bienvenidos a Holas \n");

for (t=0;t<NUM_HILOS;t++)
{
//printf("Creando el hilo %ld \n",t);
rc = pthread_create(&hilos[t],&attr,printHola,(void*)t);
if (rc){printf("ERROR, codigo %d \n",rc);
 	exit(-1);}
}

pthread_attr_destroy(&attr);

for (t=0;t<NUM_HILOS;t++)
{
rc = pthread_join(hilos[t],&status);

if (rc){printf("ERROR, codigo %d \n",rc);
 	exit(-1);}
printf("Main: Acabo el hilo %ld con status %ld \n",t,(long)status);

}

printf("podemos continuar.......................\n");

pthread_exit(NULL);

return 0;
}
