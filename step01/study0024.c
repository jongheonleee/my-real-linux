#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>

#define MAX_EVENTS 64 


int main(void) {

    struct epoll_event *events;
    struct epoll_event event;
    int nr_events, epfd;

    epfd = epoll_create1(0);
    if (epfd < 0) {
        perror("epoll_create1");
        return 1;
    }

    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event) < 0) {
        perror("epoll_ctl");
        close(epfd);
        return 1;
    }

    events = malloc(sizeof(struct epoll_event) * MAX_EVENTS);
    if (!events) {
        perror("malloc");
        close(epfd);
        return 1;
    }

    printf("waitting epoll_wait\n");

    nr_events = epoll_wait(epfd, events, MAX_EVENTS, -1);
    if (nr_events < 0) {
        perror ("epoll_wait");
        free (events);
        close(epfd);
        return 1;
    }

    for (int i=0; i<nr_events; i++) {
        printf("event=%0x%x on fd=%d\n",
            events[i].events,
            events[i].data.fd
        );

        if (events[i].data.fd == STDIN_FILENO) {
            char buf[128];
            int n = read(STDIN_FILENO, buf, sizeof(buf) - 1);

            if (n > 0) {
                buf[n] = '\0';
                printf("input: %s\n", buf);
            }
        }
    }

    free(events);
    close(epfd);
    return 1;
}