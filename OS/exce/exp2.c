#include <stdio.h>
#include <unistd.h>
int main(int argc, char*argv[]){
    printf("Para: %s\n", argv[0]);
    printf("The exp2 PID: %d", getpid());
}
