/*11.a) Write a program to differentiate between dup and dup2 functions.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd1, fd2, fd3, fd4;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd1 = open(argv[1], O_RDWR);
    if (fd1 < 0)
    {
        perror("open fd1");
        exit(EXIT_FAILURE);
    }

    fd2 = dup(fd1);  // Duplicates fd1 to lowest available fd
    printf("fd1 = %d, fd2 = %d\n", fd1, fd2);

    fd3 = open("sample.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (fd3 < 0)
    {
        perror("open fd3");
        exit(EXIT_FAILURE);
    }

    fd4 = dup2(fd1, fd3);  // Forces fd1 to duplicate onto fd3
    printf("fd3 = %d, fd4 = %d (should be same)\n", fd3, fd4);

    write(fd1, "Hello using fd1\n", 17);
    write(fd2, "Hello using fd2\n", 17);
    write(fd4, "Hello using fd4\n", 17);

    close(fd1);
    close(fd2);
    close(fd3); // same as fd4

    return 0;
}

