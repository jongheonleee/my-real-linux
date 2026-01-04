
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <stdbool.h>

int shared_data = 0;
bool ready_flag = false;
bool quit_flag = false;

bool producer_not_ready() {
    return !ready_flag;
}

bool time_to_quit() {
    return quit_flag;
}

void process_data() {
    printf("[consumer] handling data: %d\n", shared_data);
    ready_flag = false;
}

void* consumer_thread(void* arg) {
    printf("consuming ... \n");

    do {
        while (producer_not_ready() && !time_to_quit()) {
            sched_yield();
        }

        if (time_to_quit()) {
            break;
        }

        process_data();


    } while (!time_to_quit());

    printf("end of consuming...\n");
    return NULL;
}

void* producer_thread(void* arg) {
    for (int i=1; i<=5; i++) {
        sleep(1); // taken time to create data
        shared_data = 1 * 100;
        printf("[producer] data: %d, complete to create!\n", shared_data);
        ready_flag = true;

        while (ready_flag) {
            sched_yield();
        }
    }

    quit_flag = false;
    return NULL;

}

int main() {
    pthread_t producer, consumer;

    pthread_create(&consumer, NULL, consumer_thread, NULL);
    pthread_create(&producer, NULL, producer_thread, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    printf("end of main program!!\n");
    return 0;
}
