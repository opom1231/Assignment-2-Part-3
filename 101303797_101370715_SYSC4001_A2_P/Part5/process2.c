#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

struct shared_data {
    int multiple;
    int counter;
    int turn;   
};

int main() {
    key_t key = ftok("sharedfile", 65);
    int shmid = shmget(key, sizeof(struct shared_data), 0666);
    struct shared_data *data = (struct shared_data*) shmat(shmid, NULL, 0);

    printf("Process 2: starting (PID = %d). Waiting for counter > 100\n", getpid());


    while (data->counter <= 100)
    {
        usleep(100000);
    }

    printf("Process 2: counter > 100.\n");
    data->turn = 2; 

    while (data->counter <= 500) {
        while (data->turn != 2){
            usleep(1000);
        }

        printf("Process 2: Counter = %d", data->counter);
        if (data->counter % data->multiple == 0){
            printf(" : %d is a multiple of %d", data->counter, data->multiple);
        }
        printf("\n");

        data->turn = 1;   
        usleep(100000);
    }

    printf("Process 2: Counter > 500.\nExiting.\n");
    shmdt(data);
    return 0;
}
