#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd;
    char buf[101]; // for 100 bytes + null terminator
    struct flock fv;

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Set up the lock region: last 100 bytes of the file
    off_t filesize = lseek(fd, 0, SEEK_END);
    if (filesize == -1 || filesize < 100) {
        fprintf(stderr, "File must be at least 100 bytes.\n");
        close(fd);
        exit(EXIT_FAILURE);
    }

    fv.l_type = F_WRLCK;
    fv.l_whence = SEEK_END;
    fv.l_start = -100;
    fv.l_len = 100;

    printf("Press Enter to set lock...\n");
    getchar();

    printf("Trying to acquire lock...\n");
    if (fcntl(fd, F_SETLK, &fv) == -1) {
        perror("Lock failed");
        fcntl(fd, F_GETLK, &fv);
        printf("File is locked by process PID: %d\n", fv.l_pid);
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Lock acquired.\n");

    // Move to last 50 bytes
    if (lseek(fd, -50, SEEK_END) == -1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    int n = read(fd, buf, 50);
    if (n == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    buf[n] = '\0';  // Null-terminate the string
    printf("Data from last 50 bytes:\n%s\n", buf);

    printf("Press Enter to unlock...\n");
    getchar();

    // Unlock
    fv.l_type = F_UNLCK;
    fv.l_whence = SEEK_END;
    fv.l_start = -100;
    fv.l_len = 100;
    if (fcntl(fd, F_SETLK, &fv) == -1) {
        perror("Unlock failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Unlocked.\n");
    close(fd);
    return EXIT_SUCCESS;
}

