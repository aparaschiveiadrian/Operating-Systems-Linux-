#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        return errno;
    }
    if (pid == 0) {
        char *path = "./ex1_exec_output";
        char *args[] = {path, NULL};
        char *envp[] = {NULL};

        execve(path, args, envp);  

    } else {
        printf("My PID = %d, Child PID = %d\n", getpid(), pid);
        wait(NULL); 
        printf("Child %d finished\n", pid);
    }

    return 0;
}
