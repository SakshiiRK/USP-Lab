/*7.b) C program to simulate copy command by accepting the filenames from command line. Report all
errors.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    int sd = open(argv[1], O_RDONLY);
    if (sd < 0)
    {
        perror("Error opening source file");
        return 1;
    }

    int dd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dd < 0)
    {
        perror("Error opening/creating destination file");
        close(sd);
        return 1;
    }

    char buf[1024];
    ssize_t n;

    while ((n = read(sd, buf, sizeof(buf))) > 0)
    {
        if (write(dd, buf, n) != n)
        {
            perror("Error writing to destination");
            close(sd);
            close(dd);
            return 1;
        }
    }

    if (n < 0)
    {
        perror("Error reading source file");
    }

    close(sd);
    close(dd);
    return 0;
}

