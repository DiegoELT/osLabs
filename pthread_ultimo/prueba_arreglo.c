#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

void allocar_arreglo(int tamano);
void imprimir(int tamano,int *arreglo);
void llenar_arreglo(int tamano);
void calcular_suma(int tamano);
int *arreglo1;
long suma_total;


int main()
{
int i,j,k,tamano_arr;

struct timeval start;
struct timeval finish;
long compTime;
double Time;

suma_total=0;
printf("Hola Bienvenidos \n");
printf("Cual es el tamano del arreglo ?\n");
scanf("%d",&tamano_arr);
printf("El numero de elementos del arreglo es %d \n",tamano_arr);


allocar_arreglo(tamano_arr);
llenar_arreglo(tamano_arr);
imprimir(tamano_arr,arreglo1);
gettimeofday(&start,0); // Toma el tiempo antes de llamar a la funcion que calcula la suma


calcular_suma(tamano_arr);
gettimeofday(&finish,0);//Toma el tiempo que se demoro en hacer la suma
compTime=(finish.tv_sec - start.tv_sec)*1000000; // El tiempo en sec
compTime=compTime+(finish.tv_usec - start.tv_usec); //El tiempo en usec
Time=(double)compTime; //Tiempo Total
printf("El tiempo que se demoro fue %f Secs \n",(double)Time/1000000.0);//Imprime el tiempo 
printf("La suma total es %ld \n",suma_total);

printf("FIN\n");
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


void imprimir(int tamano,int *arreglo)
{
int i;
for (i=0;i<tamano;i++)
        {printf("%d\n",arreglo[i]);
        }
printf("Acabo imprimir\n");
}

void calcular_suma(int tamano)
{
int i;
for (i=0;i<tamano;i++)
	{
	suma_total += arreglo1[i];
	}

}

