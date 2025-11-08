#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int counter = 0; // spec says "initialize a counter at 0, then decrement"
    printf("Process 2 (PID=%d) started. Counting down\n", getpid());
    while (1) {
        printf("Process 2: Counter = %d", counter);
        if (counter % 3 == 0) printf(" : %d is a multiple of 3", counter);
        printf("\n");
        counter--;       // decrement each cycle
        usleep(50000);
    }
}
