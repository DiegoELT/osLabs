#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

int bufferSize = 1024;
char prompt[] = "dlinaresOS $ "; 

//The different commands that were implemented.
char pwd[] = "pwd";
char cd[] = "cd";
char makedir[] = "mkdir";
char remov[] = "rm";
char eles[] = "ls";
char gato[] = "cat";
char nano[] = "nano";

void currentDirectory()
{
	if(!fork())
	{
		char directory[bufferSize];
       		getcwd(directory, bufferSize);
		printf("%s \n", directory);
		exit(0);
	}
	else
		wait(NULL);
}

void changeDirectory(char* directory)
{
	
	if(directory == NULL)
		chdir(getenv("HOME"));
	else	
	{
		if(chdir(directory) != 0)
			printf("Error locating directory (may not exist) \n");
	}	

}

void makeDirectory(char* name)
{
	if(!fork())
	{
		if(mkdir(name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0)
			printf("Invalid name of Directory (empty/already exists/reserved) \n");
		exit(0);
	}
	else
		wait(NULL);	
}

void removeFilesAndDirectories(char* name)
{
	if(!fork())
	{	
		if (unlink(name) != 0) //First check for files
		{
			if (rmdir(name) != 0) //Then check for directories
				printf("The file or directory doesn't exist \n");
		}
		exit(0);
	}
	else
		wait(NULL);	
}

void directoriesHere(char *name)
{
	if(!fork())
	{
		DIR* directory;
		struct dirent * sd;
	
		if(name == NULL)
			name = getcwd(name, bufferSize);

		directory = opendir(name);

		while((sd = readdir(directory)) != NULL)
		{
			if((sd -> d_name)[0] != '.')
				printf("%s \t", sd -> d_name);
		}
		printf("\n");
		closedir(directory);
		exit(0);
	}
	else
		wait(NULL);

}

void execCat(char* param)
{
	if(!fork())
	{
		char* parameters[] = {"/bin/sh","-c",NULL,NULL};
		char command[256] = "cat ";
		parameters[2] = command;
		strcat(command, param);

		execv(parameters[0],parameters);
		exit(0);
	}
	else
		wait(NULL);
}

void execNano(char* param)
{
	if(!fork())
	{
		char* parameters[] = {"/bin/nano", NULL, 0};
		parameters[1] = param;
		execv("/bin/nano",parameters);
		exit(0);
	}
	else
		wait(NULL);	
}

void doCommand(char* command)
{
	char* instruction = strtok(command, "  ");
	char* argument = strtok(NULL," ");

	if(!strcmp(instruction,pwd))
		currentDirectory();
	else if (!strcmp(instruction, cd))
		changeDirectory(argument);
	else if (!strcmp(instruction, makedir))
		makeDirectory(argument);
	else if (!strcmp(instruction, remov))
		removeFilesAndDirectories(argument);
	else if (!strcmp(instruction, eles))
		directoriesHere(argument);
	else if (!strcmp(instruction, gato))
		execCat(argument);
	else if (!strcmp(instruction, nano))
		execNano(argument);
	else if (!strcmp(instruction, "clear"))
		printf("\e[2J\e[H");
	else 
		printf("Following command does not exist: %s \n", command);
}

int main(int argc, char **argv)
{
	char commandLine[bufferSize];
	while(1)
	{
		printf("%s", prompt); //Write the prompt for each command.

		if( (fgets(commandLine, bufferSize, stdin) == NULL) && ferror(stdin) )
			perror("Error with fgets >n<");
		
		commandLine[strlen(commandLine)-1] = '\0';
		if(!strcmp(commandLine,"exit"))
			break;
		doCommand(commandLine);		
	}
	return 0;
}

