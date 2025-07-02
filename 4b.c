/*4.b) Write a C program to
i. To create a child process.
ii. The child should execute an interpreter file by passing a few arguments
iii. Create an interpreter file that has the path of echoall.c file and pass one argument
iv. Create echoall.c file which prints the arguments received from both child process and
interpreter file.*/



#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>


int main()
{
	pid_t pid = fork();
	if(pid<0)
	{
		perror("Error");
	}
	else if(pid == 0 )
	{
		if(execl("./interpreter","interpreter","myarg1","myarg2","myarg4",(char*)NULL)<0)
		{
			printf("Error\n");
		}
		
	}
	return 0;
}

