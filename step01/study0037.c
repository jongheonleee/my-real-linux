
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>

void* thread_function(void* arg) {

    char* thread_name = (char*)arg;

    for (int i=0; i<5; i++) {
        printf("%s thread's working ... (%d/5)\n", thread_name, i+1);
        printf("  [!] %s thread's yeild cpu\n", thread_name);
        sched_yield();
        printf("  [~] %s thread's get time\n", thread_name);
        usleep(100000);
    }

    return NULL;
}


int main() {

    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread_function, "Thread A");
    pthread_create(&t2, NULL, thread_function, "Thread B");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("done all working\n");
    return 0;
}