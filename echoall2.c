#include<stdio.h>
#include<stdlib.h>
extern char** environ;
int main(int argc,char** argv)
{
	for(int i=0;i<argc;i++)
	{
		printf("argv[%d] = %s\n",i,argv[i]);
	}
	for(int i=0;environ[i]!=NULL;i++)
	{
		printf("%s\n",environ[i]);
	}
	return 0;

}

