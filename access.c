#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    printf("Checking access for file: %s\n", argv[1]);

    if (access(argv[1], F_OK) == 0) printf("File exists.\n");
    if (access(argv[1], R_OK) == 0) printf("Readable.\n");
    if (access(argv[1], W_OK) == 0) printf("Writable.\n");
    if (access(argv[1], X_OK) == 0) printf("Executable.\n");

    return 0;
}

