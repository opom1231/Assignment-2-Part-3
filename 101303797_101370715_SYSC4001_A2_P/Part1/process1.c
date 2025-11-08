#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        int counter2 = 0;
        printf("Process 2 (PID=%d) started. Counting up forever\n", getpid());
        while (1) {
            printf("Process 2: %d\n", counter2++);
            usleep(50000); 
        }
    }
    else {
        
        int counter1 = 0;
        printf("Process 1 (PID=%d) started. Counting up forever\n", getpid());
        while (1) {
            printf("Process 1: %d\n", counter1++);
            usleep(50000); 
        }
    }
}
