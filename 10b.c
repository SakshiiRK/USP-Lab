#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();

    if (pid1 == 0) {
        // Child 1
        printf("Child 1 (PID: %d) sleeping for 2s...\n", getpid());
        sleep(2);
        exit(10);
    }

    pid_t pid2 = fork();

    if (pid2 == 0) {
        // Child 2
        printf("Child 2 (PID: %d) sleeping for 5s...\n", getpid());
        sleep(5);
        exit(20);
    }

    // Parent process
    int status;
    pid_t finished = wait(&status);  // wait() waits for any child
    printf("Parent: Child with PID %d finished with exit code %d (via wait)\n",
           finished, WEXITSTATUS(status));

    finished = waitpid(pid2, &status, 0);  // specifically wait for child 2
    printf("Parent: Child with PID %d finished with exit code %d (via waitpid)\n",
           finished, WEXITSTATUS(status));

    return 0;
}

