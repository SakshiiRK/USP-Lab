#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc,char** argv)

{
	int fd;
	fd = open(argv[1],O_RDONLY);
	
	lseek(fd,0,SEEK_SET);
	printf("Reading starting 20 characters\n");
	char buf[1024];
	read(fd,buf,20);
	buf[20] = '\0';
	printf("20 characters:%s\n",buf);
	lseek(fd,10,SEEK_SET);
	read(fd,buf,20);
        buf[20] = '\0';
        printf("20 characters:%s\n",buf);
	lseek(fd,10,SEEK_CUR);
	read(fd,buf,20);
        buf[20] = '\0';
        printf("20 characters:%s\n",buf);
	
	int size;
        size = lseek(fd,0,SEEK_END);
        printf("Size : %d\n",size);

	return 0;
}

