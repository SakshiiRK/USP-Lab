#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    mode_t old_mask = umask(0022);  // Set new umask and save old one

    int fd = creat("testing.txt", 0666);  // Create file with rw-rw-rw-
    if (fd < 0) {
        perror("creat");
        return 1;
    }
    close(fd);

    printf("File 'testing.txt' created with umask 022 (should be rw-r--r--)\n");

    // Now change permission using chmod
    if (chmod("testing.txt", 0777) == -1) {
        perror("chmod");
        return 1;
    }

    printf("Permissions of 'testing.txt' changed to 0777 (rwxrwxrwx)\n");

    // Restore old umask
    umask(old_mask);

    return 0;
}

