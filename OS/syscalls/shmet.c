#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666|IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*)0, 0);

    if (fork() == 0) { // Child process
        sleep(1); // Wait for parent to write
        printf("Child read: %s\n", str);
        shmdt(str);
    } else { // Parent process
        const char *message = "Hello from parent";
        strcpy(str, message);
        printf("Parent wrote: %s\n", str);
        shmdt(str);
        wait(NULL); // Wait for child process to finish
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}

