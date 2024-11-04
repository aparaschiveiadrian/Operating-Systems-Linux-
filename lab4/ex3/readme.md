# Exercise 3 - Collatz Conjecture for Multiple Numbers

**Filename**: `ncollatz.c`

**Description**: This program tests the Collatz conjecture for multiple numbers, each in a separate child process. The parent process uses `fork()` to create a new child for each input number. Each child process calculates and prints the Collatz sequence for its assigned number. The parent process waits for each child to finish in sequence.

## Requirements
For each input number, a separate process should be created using `fork()`. Each child process will compute the Collatz sequence for a unique number passed as an argument and then terminate. The parent process waits for each child to complete before moving on to the next.

## Compilation
To compile the program, run:
```bash
gcc ncollatz.c -o ncollatz
```
## Run:
```bash
./ncollatz 9 16 25 36
```
## Expected output
```bash
Starting parent 6202
9: 9 28 14 7 22 11 34 17 52 26 13 40 20 10 5 16 8 4
2 1.
36: 36 18 9 28 14 7 22 11 34 17 52 26 13 40 20 10 5
16 8 4 2 1.
Done Parent 6202 Me 40018
Done Parent 6202 Me 30735
16: 16 8 4 2 1.
25: 25 76 38 19 58 29 88 44 22 11 34 17 52 26 13 40
20 10 5 16 8 4 2 1.
Done Parent 6202 Me 13388
Done Parent 6202 Me 98514
Done Parent 58543 Me 6202
```
