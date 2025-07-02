#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>
#include<fcntl.h>

void remove_empty(const char* directory)
{
	struct dirent* entry;
	DIR* dp;
	dp = opendir(directory);
	if(dp ==NULL)
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

		off_t size = lseek(fd,0,SEEK_END);

		if(size == 0)
		{
			if(unlink(path) == 0)
			{
				printf("Removed files:%s\n",path);
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
		
