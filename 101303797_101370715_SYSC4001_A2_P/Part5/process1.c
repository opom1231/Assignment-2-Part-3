#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

struct shared_data {
    int multiple;
    int Counter;
    int turn;  
};

int main() {
    pid_t pid;
    key_t key = ftok("sharedfile", 65);
    int shmid = shmget(key, sizeof(struct shared_data), 0666 | IPC_CREAT);
    struct shared_data *data = (struct shared_data*) shmat(shmid, NULL, 0);

    data->multiple = 3;
    data->Counter = 0;
    data->turn = 1; 

    pid = fork();
    if (pid < 0) { 
        perror("fork failed");
        exit(1); 
    }
    else if (pid == 0) {
        execl("./process2", "process2", NULL);
        perror("exec failed"); exit(1);
    } 
    else {
        printf("Process 1 started (PID = %d). Counting up\n", getpid());

        while (data->Counter <= 500) {
            while (data->Counter > 100 && data->turn != 1)
                usleep(1000);

            printf("Cycle %d\nProcess 1: Counter = %d", data->Counter, data->Counter);
            if (data->Counter % data->multiple == 0)
                printf(" : %d is a multiple of %d", data->Counter, data->multiple);
            printf("\n");

            data->Counter++;

            if (data->Counter > 100)
                data->turn = 2;    
            else
                data->turn = 1;  

            usleep(100000);
        }

        wait(NULL);
        printf("Process 1 reached 500.\nProcess 2 finished. Process 1 exiting.\n");
    }

    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
