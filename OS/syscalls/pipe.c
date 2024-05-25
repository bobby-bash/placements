#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];
    const char *message = "Hello from parent";

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        close(pipefd[1]); // Close the write end
        read(pipefd[0], buffer, BUFFER_SIZE);
        printf("Child received: %s\n", buffer);
        close(pipefd[0]);
    } else { // Parent process
        close(pipefd[0]); // Close the read end
        printf("Sending message to child");
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]);
        wait(NULL); // Wait for child process to finish
    }

    return 0;
}

