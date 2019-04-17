#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *printHola( void *id_hilo)
{
long hilo_id;
hilo_id=(long)id_hilo;
printf("Hola desde el hilo %ld \n",hilo_id);
pthread_exit(NULL);
}


int main()
{
int i,j,k,rc;
long t;
pthread_t hilo0,hilo1,hilo2,hilo3,hilo4,hilo5,hilo6,hilo7;

t=0;
rc=pthread_create(&hilo0,NULL,printHola,(void*)t);
if(rc){printf("ERROR creando el hilo %ld codigo %d \n",t,rc);
	exit(-1);}
t=1;
rc=pthread_create(&hilo0,NULL,printHola,(void*)t);
if(rc){printf("ERROR creando el hilo %ld codigo %d \n",t,rc);
	exit(-1);}

t=2;
rc=pthread_create(&hilo0,NULL,printHola,(void*)t);
if(rc){printf("ERROR creando el hilo %ld codigo %d \n",t,rc);
	exit(-1);}

t=3;
rc=pthread_create(&hilo0,NULL,printHola,(void*)t);
if(rc){printf("ERROR creando el hilo %ld codigo %d \n",t,rc);
	exit(-1);}

t=4;
rc=pthread_create(&hilo0,NULL,printHola,(void*)t);
if(rc){printf("ERROR creando el hilo %ld codigo %d \n",t,rc);
	exit(-1);}

t=5;
rc=pthread_create(&hilo0,NULL,printHola,(void*)t);
if(rc){printf("ERROR creando el hilo %ld codigo %d \n",t,rc);
	exit(-1);}

t=6;
rc=pthread_create(&hilo0,NULL,printHola,(void*)t);
if(rc){printf("ERROR creando el hilo %ld codigo %d \n",t,rc);
	exit(-1);}

t=7;
rc=pthread_create(&hilo0,NULL,printHola,(void*)t);
if(rc){printf("ERROR creando el hilo %ld codigo %d \n",t,rc);
	exit(-1);}

pthread_exit(NULL);
return 0;
}
