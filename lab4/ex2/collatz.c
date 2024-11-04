#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
void collatz_rec(int n)
{
	printf(" %d", n);
	if(n==1)
	{
		printf(".\n");
		return ;
	}
	if(n%2 == 0)
	{
		collatz_rec(n/2);
	}
	else
	{
		collatz_rec(n*3+1);
	}
		
}
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		const char *msg = "Un singur argument!\n";
		write(STDERR_FILENO, msg, strlen(msg));
		return 1;
	}
	
	int n = atoi(argv[1]);
	
	pid_t pid = fork();
	
	if(pid<0)
	{
		return errno;
	}
	else if(pid == 0)
	{
		printf("%d:", n);
		collatz_rec(n);
		return 0;
	}
	else
	{
		wait(NULL);
		printf("Child %d finished", pid);
	}
}
