#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat st;

    if (stat(argv[1], &st) == -1) {
        perror("stat");
        return 1;
    }

    printf("File: %s\n", argv[1]);

    if (S_ISREG(st.st_mode))
        printf("Type: Regular file\n");
    else if (S_ISDIR(st.st_mode))
        printf("Type: Directory\n");
    else if (S_ISLNK(st.st_mode))
        printf("Type: Symbolic link\n");
    else if (S_ISCHR(st.st_mode))
        printf("Type: Character device\n");
    else if (S_ISBLK(st.st_mode))
        printf("Type: Block device\n");
    else if (S_ISFIFO(st.st_mode))
        printf("Type: FIFO (named pipe)\n");
    else if (S_ISSOCK(st.st_mode))
        printf("Type: Socket\n");
    else
        printf("Type: Unknown\n");

    return 0;
}

