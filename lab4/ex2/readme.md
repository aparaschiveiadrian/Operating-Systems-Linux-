# Exercise 2 - Collatz Rule

**Filename**: `collatz.c`

**Description**: This program generates the sequence for the Collatz conjecture, given a single integer as input. The parent process creates a child process that computes and prints the sequence until it reaches 1.

## Compilation
Compile:
```bash
gcc collatz.c -o collatz
```
To run(where n is the integer):
```bash
./collatz n

```
Expected form of output
```bash
24: 24 12 6 3 10 5 16 8 4 2 1.
Child 52923 finished

```
