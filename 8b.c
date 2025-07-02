#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child PID: %d\n", getpid());
        execl("./access", "access", "hello.txt", (char *)NULL);
        perror("execl failed");
        exit(1);
    } else {
        // Parent process
        printf("Parent PID: %d waiting for child PID: %d\n", getpid(), pid);
        wait(NULL);
        printf("Child process completed.\n");
    }

    return 0;
}

