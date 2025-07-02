#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char** argv) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process executes 'add' program
        printf("Child process (PID: %d) executing add...\n", getpid());
        execl("./add", "add", argv[1],argv[2], (char *)NULL);
        perror("exec failed");
        exit(1);
    } else {
        // Parent process waits
        printf("Parent process (PID: %d), waiting for child (PID: %d)...\n", getpid(), pid);
        wait(NULL);
        printf("Parent: Child has finished.\n");
    }

    return 0;
}

