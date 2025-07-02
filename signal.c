#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void handle(int sn)
{
	printf("\n Caught sigint %d\n",sn);
	struct sigaction sa;
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if(sigaction(SIGINT,&sa,NULL) <0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}
int main()
{
	struct sigaction sa;
	sa.sa_handler = handle;
        sa.sa_flags = 0;
        sigemptyset(&sa.sa_mask);
        if(sigaction(SIGINT,&sa,NULL) <0)
        {
                perror("Error");
                exit(EXIT_FAILURE);
        }
	while(1)
	{
		printf("press  ctrl+c to trigger\n");
		pause();
	}}


