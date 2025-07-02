#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void print_bytes(int fd, int count) {
    char buffer[256] = {0};
    int bytes = read(fd, buffer, count);
    if (bytes > 0) {
        write(STDOUT_FILENO, buffer, bytes);  // Print to console
        write(STDOUT_FILENO, "\n", 1);
    } else {
        printf("Unable to read bytes.\n");
    }
}

int main() {
    int fd = open("sample.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    printf("1. First 20 characters:\n");
    lseek(fd, 0, SEEK_SET);
    print_bytes(fd, 20);

    printf("2. From 10th byte (SEEK_SET):\n");
    lseek(fd, 10, SEEK_SET);
    print_bytes(fd, 20);

    printf("3. 10 bytes ahead from current (SEEK_CUR):\n");
    lseek(fd, 10, SEEK_CUR);
    print_bytes(fd, 20);

    printf("4. File size:\n");
    struct stat st;
    if (fstat(fd, &st) == 0) {
        printf("File size: %ld bytes\n", st.st_size);
    } else {
        perror("fstat");
    }

    close(fd);
    return 0;
}

