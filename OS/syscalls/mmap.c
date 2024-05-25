#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_PATH "mmapfile"
#define FILE_SIZE 1024

int main() {
    int fd = open(FILE_PATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    if (lseek(fd, FILE_SIZE-1, SEEK_SET) == -1) {
        close(fd);
        perror("Error calling lseek() to 'stretch' the file");
        exit(EXIT_FAILURE);
    }

    if (write(fd, "", 1) == -1) {
        close(fd);
        perror("Error writing last byte of the file");
        exit(EXIT_FAILURE);
    }

    char *map = mmap(0, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }

    if (fork() == 0) { // Child process
        sleep(1); // Wait for parent to write
        printf("Child read: %s\n", map);
        munmap(map, FILE_SIZE);
    } else { // Parent process
        const char *message = "Hello from parent";
        strncpy(map, message, FILE_SIZE);
        printf("Parent wrote: %s\n", map);
        munmap(map, FILE_SIZE);
        wait(NULL); // Wait for child process to finish
    }

    close(fd);
    unlink(FILE_PATH); // Cleanup the file
    return 0;
}

