#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

void allocar_arreglo(int tamano);
void imprimir(int tamano,int *arreglo);
void llenar_arreglo(int tamano,int *arreglo);
void calcular_mult(int *arreglo1, int *arreglo2, int *arreglo3,int tamano);
int *arreglo1;
int *arreglo2;
int *arreglo3;


int main()
{
int i,j,k,tamano_arr;

struct timeval start;
struct timeval finish;
long compTime;
double Time;

printf("Hola Bienvenidos \n");
printf("Cual es el tamano de los vectores ?\n");
scanf("%d",&tamano_arr);
printf("El numero de elementos de cada vector  es %d \n",tamano_arr);

allocar_arreglo(tamano_arr); //Separamos espacio en la memoria dinamica para todos los arreglos

llenar_arreglo(tamano_arr,arreglo1);
imprimir(tamano_arr,arreglo1);
llenar_arreglo(tamano_arr,arreglo2);
imprimir(tamano_arr,arreglo2);

gettimeofday(&start,0); // Toma el tiempo antes de llamar a la funcion que calcula la suma
calcular_mult(arreglo1,arreglo2,arreglo3,tamano_arr);

gettimeofday(&finish,0);//Toma el tiempo que se demoro en hacer la suma
compTime=(finish.tv_sec - start.tv_sec)*1000000; // El tiempo en sec
compTime=compTime+(finish.tv_usec - start.tv_usec); //El tiempo en usec
Time=(double)compTime; //Tiempo Total
printf("El tiempo que se demoro fue %f Secs \n",(double)Time/1000000.0);//Imprime el tiempo 
imprimir(tamano_arr,arreglo3);
printf("FIN\n");
return 0;
}


void allocar_arreglo(int tamano)
{
arreglo1=(int*)malloc(tamano*sizeof(int));
arreglo2=(int*)malloc(tamano*sizeof(int));
arreglo3=(int*)malloc(tamano*sizeof(int));

}

void llenar_arreglo(int tamano,int *arreglo)
{
int i;
for (i=0;i<tamano;i++)
        {
        arreglo[i]=rand()%10;
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

void calcular_mult(int *arreglo1, int *arreglo2, int *arreglo3,int tamano)

{
int i;
for (i=0;i<tamano;i++)
{
	arreglo3[i]=arreglo1[i]*arreglo2[i];
}
}

