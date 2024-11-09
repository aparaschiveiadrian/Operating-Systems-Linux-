# Exercise 1 - Collatz Conjecture for Multiple Numbers USING SHARED MEMORY

**Filename**: `shmcollatz.c`

**Description**: This program tests the Collatz conjecture for multiple numbers, each in a separate child process. The parent process uses `fork()` to create a new child for each input number. Each child process calculates and prints the Collatz sequence for its assigned number. The parent process waits for each child to finish in sequence.

**Implementation**: We start from a single parent process, we create a child process for each input number and we write the result somewhere in the shared memory. The parent will create the object of shared memory using shm_open(3) and ftruncate(2), then we will load the whole space for results reading using mmap(2).
We implement a convention where the memory is split equally for child processes. We also use shm_unlin and munmap for free'ing the used resources.

## Requirements
For each input number, a separate process should be created using `fork()`. Each child process will compute the Collatz sequence for a unique number passed as an argument and then terminate. The parent process waits for each child to complete before moving on to the next.

## Compilation
To compile the program, run:
```bash
gcc shmcollatz.c -o shmcollatz
```
## Run:
```bash
./shmcollatz 9 16 25 36
```
## Expected output
```bash
Starting parent 75383
Done Parent 75383 Me 59702
Done Parent 75383 Me 3281
Done Parent 75383 Me 33946
Done Parent 75383 Me 85263
9: 9 28 14 7 22 11 34 17 52 26 13 40 20 10 5 16 8 4
2 1.
16: 16 8 4 2 1.
25: 25 76 38 19 58 29 88 44 22 11 34 17 52 26 13 40
20 10 5 16 8 4 2 1.
36: 36 18 9 28 14 7 22 11 34 17 52 26 13 40 20 10 5
16 8 4 2 1.
Done Parent 96028 Me 75383
```
