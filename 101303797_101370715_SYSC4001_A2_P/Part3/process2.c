#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int counter = 0;

    printf("Process 2 started (PID = %d). Counting down\n", getpid());

    while (counter > -500) {

        printf("Process 2: Counter = %d", counter);
        if (counter % 3 == 0)
            printf(" : %d is a multiple of 3", counter);
        printf("\n");

        counter--;
        usleep(100000);
    }

    printf("Process 2 reached -500\nExiting.\n");
    return 0;
}
