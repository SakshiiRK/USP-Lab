/*2.a) Write a C program to display various details of a file using stat structure (Atleast 5 fields).*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<time.h>

int main(int argc,char** argv)
{
	if(argc<2)
	{
		printf("Usage %s <filename> ",argv[0]);
		return 1;
	}
	struct stat fs;
	if(stat(argv[1],&fs) ==-1)
	{
		perror("stat");
		return 1;
	}
	printf("File:%s\n",argv[1]);
	printf("File size:%lld\n",(long long)fs.st_size);
	printf("Permissions:%o\n",fs.st_mode & 07770);
	printf("number of links:%ld\n",(long)fs.st_nlink);
	printf("Last access time:%s\n",ctime(&fs.st_atime));
	printf("Last modified time:%s\n",ctime(&fs.st_mtime));
	printf("Last status change time:%s\n",ctime(&fs.st_ctime));
	return 0;
}
