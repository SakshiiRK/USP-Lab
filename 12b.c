/*12.b) Write a C program to perform the following operations
i)
ii)
iii)
To create a child and parent process with the use of an echoall file.
The Child should execute a process that prints the user defined values of environment
variables
The Parent should execute a process that prints default values for the environment
variables.*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

int main()
{
	pid_t pid = fork();
	char * env[] = {
		"USER=unknown",
		"PATH=/tmp",
		NULL
	};
	if(pid <0)
	{
		printf("Error");
		return -1;
	}
	else if(pid ==0)
	{
		if(execle("./echoall2","echoall2","myarg1","myarg2",(char*)NULL,env)<0)
		{
			perror("Error");
		}
	}else
	{
		if(waitpid(pid,NULL,0)<0)
		{
			perror("Error");
		}
		if(execlp("./echoall2","echoall2","only 1 arg",(char*)NULL)<0)
		{
			printf("Error");
		}
	}
	return 0;
}
