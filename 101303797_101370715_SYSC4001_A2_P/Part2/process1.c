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
        execl("./process2", "process2", NULL);
        perror("exec failed");
        exit(1);
    }
    else {
        int counter = 0;
        printf("Process 1 (PID=%d) started. Counting up\n", getpid());
        while (1) {
            printf("Cycle %d\n", counter);
            printf("Process 1: Counter = %d", counter);
            if (counter % 3 == 0) printf(" : %d is a multiple of 3", counter);
            printf("\n");
            counter++;
            usleep(50000);
        }
    }
}
