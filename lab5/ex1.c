#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>    
#include <fcntl.h>  
#include <sys/wait.h>

// COLLATZ
void collatz_sequence(int num, char *buffer, int size) 
{
    char temp[size];
    while (num != 1) {
        sprintf(temp, "%d ", num);
        strcat(buffer, temp);
        if (num % 2 == 0)
            num /= 2;
        else
            num = 3 * num + 1;
    }
    strcat(buffer, "1.\n");
}

// MAIN
int main(int argc, char *argv[])
{
    // PARAMETERS
    if(argc < 2) 
    {
        char *msg = "./shmcollatz numar1 numar2 numar3 ... (minim un numar)\n";
        write(2, msg, strlen(msg));
        return 1;
    }
    
    // SHM OPEN
    char *shm_name = "myshm";
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if(shm_fd < 0) 
    {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }
    
    // FTRUNCATE
    int numbers_to_calculate = argc - 1;
    int page_size = getpagesize();
    int memory_per_number = page_size; 
    
    
    size_t shm_size = numbers_to_calculate * memory_per_number;

    if (ftruncate(shm_fd, shm_size) < 0) 
    {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    // FORK
    pid_t pid = getpid();
    printf("Starting parent %d\n", pid);
    
    for (int i = 1; i <= numbers_to_calculate; i++) 
    {
        pid = fork();
        
        if (pid < 0) 
        {
            perror(NULL);
            shm_unlink(shm_name);
            return errno;
        }
        else if (pid == 0) 
        { 
            int number = atoi(argv[i]);
            
            
            char *shm_ptr = mmap(0, memory_per_number, PROT_WRITE, MAP_SHARED, shm_fd, (i - 1) * memory_per_number);
            if (shm_ptr == MAP_FAILED)
            {
                perror(NULL);
                return errno;
            }
            sprintf(shm_ptr, "%d: ", number); 
            collatz_sequence(number, shm_ptr + strlen(shm_ptr), memory_per_number); 
            munmap(shm_ptr, memory_per_number); 
            printf("Done Parent %d Me %d\n", getppid(), getpid());
            exit(0); 
        }
        else
        {
        	wait(NULL);
        }
    }

    char *shm_ptr = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED)
    {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }
    
    for (int i = 1; i <= numbers_to_calculate; i++) 
    {
        printf("%s", shm_ptr + (i - 1) * memory_per_number);
    }

    munmap(shm_ptr, shm_size);
    shm_unlink(shm_name);

    printf("Done Parent %d Me %d\n", getppid(), getpid());
    return 0;
}
