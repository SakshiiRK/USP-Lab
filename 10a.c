#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid > 0) {
        // Parent exits
        printf("Parent exiting. Daemon PID: %d\n", pid);
        exit(0);
    }

    // Child continues to become a daemon
    umask(0);                       // Reset file mode creation mask
    setsid();                       // Create new session
    chdir("/");                     // Change working directory

    // Close all standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Daemon code - write to a file periodically
    while (1) {
        int fd = open("/tmp/daemon_log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd != -1) {
            write(fd, "Daemon is running...\n", 22);
            close(fd);
        }
        sleep(5);
    }

    return 0;
}

