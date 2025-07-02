/*3.a) Write a C program to remove empty files from the given directory.*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<dirent.h>

void remove_empty(const char* directory)
{
	struct dirent* entry;
	DIR* dp;
	dp = opendir(directory);
	if(dp==NULL)
	{
		perror("opendir");
		return;
	}
	while((entry = readdir(dp))!=NULL)
	{
		if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
		{
			continue;
		}
		char path[1024];
		snprintf(path,sizeof(path),"%s/%s",directory,entry->d_name);
		int fd = open(path,O_RDONLY);
		if(fd ==-1)
		{
			perror("open");
			continue;
		}
		off_t sizel = lseek(fd,0,SEEK_END);
		if(sizel <0)
		{
			perror("lseek");
			continue;
		}
		if(sizel ==0)
		{
			if(unlink(path) == 0)
			{
				printf("Removed empty file %s\n",path);
			}
			else
			{
				perror("unlink");
			}
		}
	}
}
int main(int argc,char** argv)
{
	const char* directory = argv[1];
	remove_empty(directory);
	return 0;
}
