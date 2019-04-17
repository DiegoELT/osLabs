#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define NUM_HILOS 4
int *arreglo1;
int suma_total;
int contador_hilos;

pthread_mutex_t mutex1;

struct datos
{
long thread_id;
int tamano;
};

struct datos datos_pasar[NUM_HILOS];

void allocar_arreglo(int tamano);
void llenar_arreglo(int tamano);
void imprimir(int tamano);

void *calcularSuma(void *parametros)
{
int i,j,k,lim_inf,lim_sup,tamanoA;
long t;
int contador_local;
int suma_parcial;
struct datos *mis_datos;
mis_datos=(struct datos*)parametros;
t=mis_datos->thread_id;
tamanoA=mis_datos->tamano;

lim_inf=t*(tamanoA/NUM_HILOS);
lim_sup=(t+1)*(tamanoA/NUM_HILOS);

pthread_mutex_lock(&mutex1);
contador_hilos++;
pthread_mutex_unlock(&mutex1);

do 
{
pthread_mutex_lock(&mutex1);
contador_local=contador_hilos;
pthread_mutex_unlock(&mutex1);
}
while (contador_local < NUM_HILOS -1 );

printf("Hilo %ld LIM inf %d , LIM sup %d \n",t,lim_inf,lim_sup);




suma_parcial=0;
for (i=lim_inf;i<lim_sup;i++)
	{
	suma_parcial += arreglo1[i];	
	}

pthread_mutex_lock(&mutex1);
suma_total += suma_parcial;
pthread_mutex_unlock(&mutex1);

pthread_exit((void*)t);
}


int main ()
{
int i,j,k,rc,tam_arreglo;
long t;
void *status;
pthread_t arreglo_hilos[NUM_HILOS]; //Indico que voy a usar arreglo de hilos
pthread_attr_t attr; //Declaro atributo
pthread_attr_init(&attr); // Inicializo atributo
pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE); //Hago que el atributo sea joinable
pthread_mutex_init(&mutex1,NULL);

printf("Cuantos elementos tiene el arreglo?\n");
scanf("%d",&tam_arreglo);
printf("El arreglo va a tener %d elementos \n",tam_arreglo); 

suma_total=0;
allocar_arreglo(tam_arreglo); //Llama funcion para alocar memoria dinamica
llenar_arreglo(tam_arreglo); //LLena el arreglo de numeros aleatorios
imprimir(tam_arreglo); //Imprimi el arreglo

for (t=0;t<NUM_HILOS;t++)
{
datos_pasar[t].thread_id=t;
datos_pasar[t].tamano=tam_arreglo;
rc=pthread_create(&arreglo_hilos[t],&attr,calcularSuma,(void*)&datos_pasar[t]);
printf("Creando hilo %ld \n",t);
if (rc){printf("ERROR al crear el hilo %ld codigo %d \n",t,rc);
	exit(-1);}

}

pthread_attr_destroy(&attr);
for (t=0;t<NUM_HILOS;t++)
{
rc=pthread_join(arreglo_hilos[t],&status);
if (rc){printf("ERROR,codigo %d \n",rc);
        exit(-1);
        }
printf("En la funcion main, ya acabo el hilo %ld con status %ld \n",t,(long)status);

}

printf("La suma final es %d \n",suma_total);
printf("Fin del programa \n");
pthread_mutex_destroy(&mutex1);
pthread_exit(NULL);
free(arreglo1);
return 0;

}


void allocar_arreglo(int tamano)
{
arreglo1=(int*)malloc(tamano*sizeof(int));
}

void llenar_arreglo(int tamano)
{
int i;
for (i=0;i<tamano;i++)
	{
	arreglo1[i]=rand()%20;
	}
}


void imprimir(int tamano)
{
int i;
for (i=0;i<tamano;i++)
	{printf("%d\n",arreglo1[i]);
	}
printf("Acabo imprimir\n");
}






