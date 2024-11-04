# Exercise 2 - Copy contents from source to destination

**Files**:
- `ex1.c`: Main program file that creates a child process.
- `ex1_exec.c`: Helper file that the child process executes to list directory contents.

**Description**: This program creates a new process using `fork()`. The parent process prints its PID and the child's PID, then waits for the child to finish. The child process uses `execve` to list the contents of the current directory.

## Compilation
To compile both files, run:
```bash
gcc ex1.c -o ex1_output
gcc ex1_exec.c -o ex1_exec_output
```
To run
```bash
./ex1_output
```
Expected form of output
```bash
My PID =41875 , Child PID =62668
Makefile collatz.c forkls.c so-lab-4.tex
collatz forkls ncollatz.c
Child 62668 finished
```
