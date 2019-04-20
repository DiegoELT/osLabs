#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define MAX 6

int rowsA, columnsA, rowsB, columnsB, threadNumber;
int **matrixA, **matrixB, **matrixC;

int ** allocateMatrix(int rows, int columns)
{
	int * values = (int *) malloc(rows * columns * sizeof(int));

	int ** valuePointer = (int **) malloc(rows * sizeof(int*));
	
	//Use rows for allocating the pointers.

	for(int i = 0; i < rows; i++)
		valuePointer[i] = &values[i*columns];

	return valuePointer;
}

void randomizeMatrix(int **matrix, int rows, int columns)
{
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
			matrix[i][j] = rand() % MAX;
	}
}

void printMatrix(int **matrix, int rows, int columns)
{
	for(int i = 0; i < rows; i++)	
	{
		for(int j = 0; j < columns; j++)
		{
			printf("%d", matrix[i][j]);
			putchar(' ');
		}
		putchar('\n');
	}
}

void * matrixMultiplicator(void * parameters)
{
	int division, threadID, threadStartRow, threadEndRow, sum;
	threadID = *(int *)(parameters);
	division = rowsA/threadNumber;

	threadStartRow = threadID * division;
	threadEndRow = (threadID + 1) * division;

	for(int i = threadStartRow; i < threadEndRow; i++)
	{
		for(int j = 0; j < columnsB; j++)
		{
			sum = 0;
			for(int k = 0; k < columnsA; k++)
				sum += matrixA[i][k] * matrixB[k][j];
			matrixC[i][j] = sum;
		}
	}
}

int main()
{
	srand(time(0));
	printf("Inserte el numero de threads a utilizarse \n");
	scanf("%d",&threadNumber);
	do
	{
		printf("Inserte el numero de rows de la matriz A \n");
		scanf("%d", &rowsA);
		printf("Inserte el numero de columns de la matriz A \n");
		scanf("%d", &columnsA);
		printf("Inserte el numero de rows de la matriz B \n");
		scanf("%d", &rowsB); 
		printf("Inserte el numero de columns de la matriz B \n");
		scanf("%d", &columnsB);
		if(columnsA != rowsB || rowsA % threadNumber)
			printf("La combinacion de rows y columns no es valida \n");
	}while(columnsA != rowsB || rowsA % threadNumber);

	struct timeval start, finish;
	long totalTime;
	pthread_t * threads;

	threads = (pthread_t *) malloc(threadNumber * sizeof(pthread_t));
	matrixA = allocateMatrix(rowsA, columnsA); 
	matrixB = allocateMatrix(rowsB, columnsB);
	matrixC = allocateMatrix(rowsA, columnsB); //matrix m*n
	
	randomizeMatrix(matrixA, rowsA, columnsA); randomizeMatrix(matrixB, rowsB, columnsB);
 	printf("Matriz A generada: \n");
	printMatrix(matrixA, rowsA, columnsA);
	printf("Matriz B generada: \n");
	printMatrix(matrixB, rowsB, columnsB);

	//Una vez alocadas las matrices, se empieza a tomar el tiempo.
	
	gettimeofday(&start, NULL);

	for(int i = 0; i < threadNumber; i++)
	{
		int * threadID;
		threadID = (int *) malloc(sizeof(int));
		*threadID = i;
		//Create a thread with a respective number.

		pthread_create(&threads[i], NULL, matrixMultiplicator, (void*)threadID);
	}

	for(int i = 0; i < threadNumber; i++)
		pthread_join(threads[i], NULL);

	gettimeofday(&finish, NULL);

	printf("Matriz C resultante: \n");
	printMatrix(matrixC, rowsA, columnsB);

	totalTime = (finish.tv_usec - start.tv_usec);
	printf("Execution time: '%Le' Secs \n", (long double)totalTime/1000000.0);
}
