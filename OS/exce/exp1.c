#include <stdio.h>
#include <unistd.h>

int main(){
    printf("Inside the exp1\n");
    printf("exp1 PID = %d\n", getpid());
    execv("exp2", {"hello", "world", NULL});
    printf("Back to exp1\n");
}
