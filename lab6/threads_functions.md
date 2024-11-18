
# Understanding Threads in Computing

## POSIX Threads: Key Functions

### 1. **`pthread_create`**
This function is used to create a new thread within a program.

#### Syntax:
```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
```

#### Parameters:
- **`pthread_t *thread`**: A pointer to a variable of type `pthread_t`. This variable will hold the identifier of the created thread.
- **`const pthread_attr_t *attr`**: A pointer to thread attributes. Use `NULL` for default attributes.
- **`void *(*start_routine)(void *)`**: A pointer to the function that the thread will execute. This function must take a `void *` argument and return a `void *`.
- **`void *arg`**: A pointer to the argument that will be passed to the `start_routine` function. Pass `NULL` if no argument is needed.

#### Return Value:
- Returns `0` on success.
- On failure, returns a non-zero error code.

#### Example:
```c
void *print_message(void *message) {
    printf("%s\n", (char *)message);
    return NULL;
}

pthread_t thread;
if (pthread_create(&thread, NULL, print_message, "Hello, Thread!")) {
    perror("Error creating thread");
}
```

---

### 2. **`pthread_join`**
This function waits for a specific thread to terminate and retrieves its return value.

#### Syntax:
```c
int pthread_join(pthread_t thread, void **retval);
```

#### Parameters:
- **`pthread_t thread`**: The thread identifier of the thread to wait for.
- **`void **retval`**: A pointer to a pointer where the thread’s exit value (returned by `pthread_exit`) will be stored. Pass `NULL` if you do not need the return value.

#### Return Value:
- Returns `0` on success.
- On failure, returns a non-zero error code.

#### Notes:
- Only threads created by `pthread_create` can be joined.
- `pthread_join` acts like `wait` in process management, ensuring that the parent thread does not proceed until the specified thread has terminated.

#### Example:
```c
pthread_t thread;
void *result;

if (pthread_create(&thread, NULL, print_message, "Joining Thread")) {
    perror("Error creating thread");
}

if (pthread_join(thread, &result)) {
    perror("Error joining thread");
}
```

---

### 3. **`pthread_exit`**
This function is used by a thread to terminate its execution explicitly and optionally return a value to the thread that joined it.

#### Syntax:
```c
void pthread_exit(void *retval);
```

#### Parameters:
- **`void *retval`**: A pointer to the value that the thread wishes to return. This value can be retrieved by another thread using `pthread_join`.

#### Notes:
- If the main thread calls `pthread_exit`, other threads will continue to run until they finish.
- If `pthread_exit` is not called explicitly and the thread function returns, the return value is used as the exit value.

#### Example:
```c
void *compute_sum(void *arg) {
    int *num = (int *)arg;
    int *sum = malloc(sizeof(int)); // Return value must be dynamically allocated
    *sum = *num + 10;              // Example computation
    pthread_exit(sum);
}

pthread_t thread;
void *result;

int value = 5;
if (pthread_create(&thread, NULL, compute_sum, &value)) {
    perror("Error creating thread");
}

if (pthread_join(thread, &result)) {
    perror("Error joining thread");
}

printf("Sum: %d\n", *(int *)result);
free(result); // Free the allocated memory
```

---

## Summary of Usage
- **`pthread_create`**: Starts a new thread, executing the specified function.
- **`pthread_join`**: Waits for a thread to complete and optionally retrieves its return value.
- **`pthread_exit`**: Ends a thread’s execution and optionally provides a return value to the thread that joined it.

By using these functions together, you can efficiently manage multiple threads, share resources, and synchronize their execution within a process.
