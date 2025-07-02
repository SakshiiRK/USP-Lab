/*1.b) Write a C program to create a child process and show how parent and child processes will share
the text file and justify that both parent and child shares the same file offset.*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc,char **argv)
{
	if(argc<2)
	{
		printf("Usage %s<filename>",argv[0]);
		return 1;
	}
	int fd = open(argv[1],O_RDONLY);
	if(fd< 0)
	{
		perror("open");
		return 1;
	}
	pid_t pid = fork();
	if(pid<0)
	{
		perror("fork");
		return 1;
	}
	else if(pid ==0)
	{
		char buff[10];
		read(fd,buff,5);
		buff[5] = '\0';
		printf("Child reads : %s\n",buff);
	}
	else
	{
		wait(NULL);
		char buff[10];
                read(fd,buff,5);
                buff[5] = '\0';
                printf("Parent reads : %s\n",buff);
	}
	close(fd);
	return 0;
}



