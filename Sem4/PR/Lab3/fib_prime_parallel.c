#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#include "fib_prime_functions.h"

#define RANGE_START 1
#define RANGE_END 1000000000
#define NUM_PROCESSES 7

// Function to fork a leaf process and wait for its result
int fork_leaf(int start, int end) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Leaf process: count Fibonacci primes and exit with result

        printf("\t\\_Leaf process (PID: %d) (PPID: %d) started.\n", getpid(), getppid());

        int result = count_fibonacci_primes(start, end);
        exit(result);
    } else {
        // Parent process: wait for child and return its result
        int status;
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
}

// Function to fork a child process which then forks two leaf processes
int fork_child(int start, int end) {
    pid_t child_pid = fork();

    if (child_pid < 0){
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (child_pid == 0) {
        // Child process: count Fibonacci primes and exit with result

        printf("\\_Child process (PID: %d) (PPID: %d) started.\n", getpid(), getppid());

        int range_size = (end - start) / 3;

        // Child 1 spawns leaf_1_1 and leaf_1_2
        int leaf_1_count = fork_leaf(start, start + range_size - 1);
        int leaf_2_count = fork_leaf(start + range_size, start + 2 * range_size - 1);

        // Child 1 also computes its own range
        int child_self_count = count_fibonacci_primes(start + 2 * range_size, start + 3 * range_size - 1);
        
        int child_total = leaf_1_count + leaf_2_count + child_self_count;
        exit(child_total);
    } else {
        // Parent process: wait for child and return its result
        int status;
        waitpid(child_pid, &status, 0);
        return WEXITSTATUS(status);
    }
}

int main() {
    clock_t start_time = clock();

    int range_size = (RANGE_END - RANGE_START + 1) / NUM_PROCESSES;
    int total_count = 0;

    printf("Root process (PID: %d) started.\n", getpid());

    // Root process spawns child_1 and child_2
    int child_1_count = 0, child_2_count = 0;

    // Gather results from child_1 and child_2
    child_1_count = fork_child(RANGE_START, RANGE_START + 3 * range_size);
    child_2_count = fork_child(RANGE_START + 3 * range_size, RANGE_START + 6 * range_size);

    // Root also computes its own range
    int root_self_count = count_fibonacci_primes(RANGE_START + 6 * range_size, RANGE_START + 7 * range_size);

    // Finish result
    total_count = root_self_count + child_1_count + child_2_count;

    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Total Fibonacci primes found: %d\n", total_count);
    printf("Execution time: %.2f seconds\n", elapsed_time);

    return 0;
}
