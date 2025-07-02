/*6.b) Consider the last 100 bytes as a region. Write a C program to check whether the region is locked
or not. If the region is locked, print pid of the process which has locked. If the region is not locked,
lock the region with an exclusive lock, read the last 50 bytes and unlock the region.*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc,char** argv)
{
	if(argc < 2)
	{
		perror("Error");
		return -1;
	}
	struct flock f;
	f.l_type = F_WRLCK;
	f.l_whence = SEEK_END;
	f.l_len = 100;
	f.l_start  = -100;
	int fd = open(argv[1],O_RDWR);
	if(fd < 0)
	{
		perror("open");
		return -1;
	}
	int size;
	size = lseek(fd,0,SEEK_END);
	printf("Size of the file : %d\n",size);

	printf("Checking whether file is locked: \n");
	if(fcntl(fd,F_GETLK,&f) == -1)
	{
		printf("Error during getting lock\n");
	}
	if(f.l_type != F_UNLCK)
	{
		printf("File is already locked so pid is : %d\n",f.l_pid);
	}
	else
	{
		 f.l_type = F_WRLCK;
        	fcntl(fd,F_SETLK,&f);
	lseek(fd,-50,SEEK_END);
	char buf[51];
	read(fd,buf,50);
	buf[50] = '\0';
	printf("Content %s\n",buf);
	f.l_type = F_UNLCK;
	fcntl(fd,F_SETLK,&f);
	}
	return 0;
}

