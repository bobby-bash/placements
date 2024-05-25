#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void file_management() {
    int fd = open("example.txt", O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("open");
        return;
    }
    const char *text = "Hello, System Calls!\n";
    if (write(fd, text, strlen(text)) < 0) {
        perror("write");
    }
    close(fd);
}

void process_control() {
    pid_t pid = fork();
    if (pid == 0) {
        execl("/bin/ls", "ls", (char *)0);
        perror("execl");
        exit(1);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
    }
}

void device_management() {
    int fd = open("/dev/tty", O_WRONLY);
    if (fd < 0) {
        perror("open");
        return;
    }
    const char *text = "Writing to terminal.\n";
    if (write(fd, text, strlen(text)) < 0) {
        perror("write");
    }
    close(fd);
}

void information_maintenance() {
    struct timeval tv;
    if (gettimeofday(&tv, NULL) < 0) {
        perror("gettimeofday");
        return;
    }
    printf("Current time: %ld seconds and %ld microseconds\n", tv.tv_sec, tv.tv_usec);

    struct utsname buffer;
    if (uname(&buffer) < 0) {
        perror("uname");
        return;
    }
    printf("System name: %s\n", buffer.sysname);
    printf("Node name: %s\n", buffer.nodename);
    printf("Release: %s\n", buffer.release);
    printf("Version: %s\n", buffer.version);
    printf("Machine: %s\n", buffer.machine);
}

int main() {
    printf("File Management System Call:\n");
    file_management();
    printf("\nProcess Control System Call:\n");
    process_control();
    printf("\nDevice Management System Call:\n");
    device_management();
    printf("\nInformation Maintenance System Call:\n");
    information_maintenance();

    return 0;
}

