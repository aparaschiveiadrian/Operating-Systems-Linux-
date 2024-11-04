#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
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
int main(int argc, char *argv[]) {
    if (argc < 2) {
        char *msg = "Trebuie minim un argument.\n";
        write(STDERR_FILENO, msg, strlen(msg));
        return 1;
    }

    printf("Starting parent %d\n", getpid());

    for (int i = 1; i < argc; i++) {
        int n = atoi(argv[i]);

        pid_t pid = fork();
        if (pid < 0) 
        {
            return errno;
        } 
        else if (pid == 0) 
        {
            printf("%d:",n);
            collatz_rec(n); 
            printf("Done Parent %d Me %d\n", getppid(), getpid());
            return 0;
        }
        else
        {
        	wait(NULL);
        	printf("Done Parent %d Me %d\n", getppid(), getpid());
        }
        
    }

    
    
    
    return 0;
}

