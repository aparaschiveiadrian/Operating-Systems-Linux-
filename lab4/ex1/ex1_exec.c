#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *args[] = {"/bin/ls", NULL};  
    char *envp[] = {NULL};
    execve("/bin/ls", args, envp); 
    return 0;
}
