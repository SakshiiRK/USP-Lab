/*1.a) Write a C program to display the file content in reverse order using lseek
system call.*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc,char *argv[])
{
	if(argc <2)
	{
		printf("Usage %s<filename>",argv[0]);
	}
	int fd = open(argv[1],O_RDONLY);
	if(fd<0)
	{
		perror("Error during opening of file");
	}
	int filesize = lseek(fd,0,SEEK_END);
	if(filesize < 0)
	{
		perror("Erro");
	}
	for(int i=1;i<=filesize;i++)
	{
		lseek(fd,-i,SEEK_END);
		char c;
		if(read(fd,&c,1)!=1)
		{
			perror("read");
		}
		putchar(c);
	}
	printf("\n");
	return 0;
}
	
