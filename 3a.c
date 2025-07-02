/*3.b) Write a C program to implement ls –li command which list the files in a specified directory. Your
program should Print 5 attributes of files.*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<fcntl.h>
#include<time.h>
#include<sys/stat.h>
int main(int argc,char** argv)
{
	struct dirent* d;
	DIR* dp ;
	const char* dps;
	if(argc >1)
	{
		dps = argv[1];
	}
	else
	{
		dps = ".";
	}

	dp = opendir(dps);

	struct stat st;

	if(dp)
	{
		while(d = readdir(dp))
		{
			stat(d->d_name,&st);
			printf("%ld %o %d %d %s %s\n",st.st_ino,st.st_mode,st.st_uid,st.st_gid,ctime(&st.st_atime),d->d_name);
		}
	}
}
