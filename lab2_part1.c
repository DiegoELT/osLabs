#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/wait.h>

#define testNum 20

//Reminder. Read = 0, Write = 1

long pipetime[testNum];

void minFunction() {return;}

void messagePass(int testCase)
{
	char msg_Write, msg_Read;
	
	int dadToSon[2];
	int sonToDad[2];

	struct timeval startTotal, finishTotal, startRead, finishRead, startWrite, finishWrite;
	long totalTime, readTime, writeTime;

	pid_t pid; 

	if(pipe(dadToSon) == -1)
		printf("Dad to Son Pipe failed. \n");
	if(pipe(sonToDad) == - 1)
		printf("Son to Dad Pipe failed. \n");

	pid = fork();

	if(pid < 0)
		printf("Fork failed. \n");

	if(pid > 0) //If it is the parent
	{
		close(dadToSon[0]); close(sonToDad[1]);	

		gettimeofday(&startTotal, 0); gettimeofday(&startWrite,0);
		write(dadToSon[1], &msg_Write, 1);
		gettimeofday(&finishWrite, 0);
		
		close(dadToSon[1]);
		
		gettimeofday(&startRead, 0);
		read(sonToDad[0], &msg_Read, 1);
		gettimeofday(&finishRead, 0); gettimeofday(&finishTotal,0);

		totalTime = (finishTotal.tv_usec - startTotal.tv_usec);
		readTime = (finishRead.tv_usec - startRead.tv_usec);
		writeTime = (finishWrite.tv_usec - startWrite.tv_usec);

		pipetime[testCase] = (totalTime - readTime - writeTime)/2;
	}

	else
	{
		close(dadToSon[1]); close(sonToDad[0]);
		read(dadToSon[0], &msg_Read, 1);
		write(sonToDad[1], &msg_Write, 1);
		close(sonToDad[1]);

		exit(0);
	}
}


int main()
{
	struct timeval start, finish;

	long comptime = 0;

	for(int i = 0; i < 20; i++)
	{
		gettimeofday(&start, 0);
		minFunction();
		gettimeofday(&finish, 0);
		comptime += (finish.tv_usec - start.tv_usec);
	}
	printf("Meaningless function time: %Le Secs\n", (long double)comptime/20000000.0);
	comptime = 0;

	for(int i = 0; i < 20; i++)
	{		
		gettimeofday(&start, 0);
		getpid();
		gettimeofday(&finish, 0);
		comptime += (finish.tv_usec - start.tv_usec);
	}

	printf("get_pid() time: %Le Secs\n", (long double)comptime/20000000.0);
	comptime = 0;

	for(int i = 0; i < 20; i++)
		messagePass(i);

	for(int i = 0; i < 20; i++)
	{
		comptime += pipetime[i];
	}

	printf("Context Switch time: %Le Secs \n", (long double)comptime/20000000.0);
}
