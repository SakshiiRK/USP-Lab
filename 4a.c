/*4.a) Write a C program to demonstrate the creation of soft links and the various properties of hard
links.*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc,char** argv)
{
	if(argc ==3)
	{
		if((link(argv[1],argv[2]))==0)
		{
			printf("Hard link is created");
		}
		else
		{
			printf("Hard link error");
		}
	}
	else if(argc == 4)
	{
		if((symlink(argv[2],argv[3])) ==0)
		{
			printf("Soft link is created");
		}
		else
		{
			printf("Soft link error");
		}
		}

	return 0;
}
