// echoall.c
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char** argv)
{
    printf("--- echoall.c output ---\n"); // Added for clarity
    for(int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]); // ADDED '\n' here
    }
    printf("--- End of echoall.c output ---\n"); // Added for clarity
    return 0;
}
