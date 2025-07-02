/*2.b) Write a C program to simulate system function.*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int my_sys(const char *command)
{
	if(command == NULL)
	{
		return 1;
	}
	pid_t pid = fork();
	if(pid<0)
	{
		perror("fork");
		return 1;
	}
	else if(pid == 0)
	{
		execl("/bin/sh","sh","-c",command,(char*)NULL);
		perror("execl");
		exit(EXIT_FAILURE);
	}
	else
	{
		int st;
		if(waitpid(pid,&st,0)==-1)
		{
			return -1;
		}
		if(WIFEXITED(st))
		{
			return WEXITSTATUS(st);
		}
		else
		{
			return 1;
		}
	}
}

int main()
{
	printf("Executing ls -li\n");
	int res = my_sys("ls -li");
	if(res == -1)
	{
		printf("error");
	}
	else
	{
		printf("exited with status %d",res);
	}
	return 0;
}

