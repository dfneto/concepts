#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int i;
    pid_t pid;

    // Create 2 child processes
    for (i = 0; i < 2; i++) {
        pid = fork();

        if (pid == -1) {
            // If fork() fails
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            printf("Child %d (PID: %d) started.\n", i + 1, getpid());

            // Simulate work by sleeping
            sleep(1 + i); // Sleep for 1 second for the first child, 2 for the second

            printf("Child %d (PID: %d) finished.\n", i + 1, getpid());
            exit(EXIT_SUCCESS); // Child process exits
        }
        // Parent process continues to next iteration to fork again or wait
    }

    // Parent process waits for all child processes to terminate
    while ((pid = wait(NULL)) > 0) {
        printf("Parent (PID: %d) detected child (PID: %d) termination.\n", getpid(), pid);
    }

    pq so imprime isso uma vez?
    printf("Parent (PID: %d) has no more child processes. Exiting.\n", getpid());
    return EXIT_SUCCESS;
}
