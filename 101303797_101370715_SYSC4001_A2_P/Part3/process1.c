#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int counter = 0;

    pid = fork(); 

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
        printf("Process 1 started (PID = %d). Counting up\n", getpid());

        while (counter <= 500) {
            printf("Cycle %d\n", counter);
            printf("Process 1: Counter = %d", counter);
            if (counter % 3 == 0)
                printf(" : %d is a multiple of 3", counter);
            printf("\n");

            counter++;
            usleep(100000);
        }

        wait(NULL);  // wait for process 2 to finish
        printf("Process 2 finished.\nProcess 1 exiting.\n");
    }

    return 0;
}
