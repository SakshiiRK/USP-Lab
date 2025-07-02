/*12.a) Write a program to demonstrate the zombie state of a process and provide the solution for the
same.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        printf("Child process started. PID = %d\n", getpid());
        printf("Child process exiting.\n");
        exit(0);  // Important: child exits here
    }
    else
    {
        printf("Parent process. PID = %d, child PID = %d\n", getpid(), pid);
        sleep(5);  // Wait to let child exit and become zombie

        printf("\nChecking for zombie process:\n");
        system("ps -o pid,ppid,stat,cmd");

        // Now collect child to prevent zombie
        wait(NULL);
        printf("\nChild reaped. Zombie cleaned up.\n");
    }

    return 0;
}

