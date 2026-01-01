#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10 

int main(void) {
    int epfd;
    struct epoll_event ev, events[MAX_EVENTS];

    epfd = epoll_create1 (0);
    if (epfd < 0) {
        perror("epoll_create1");
        return 1;
    }

    ev.events = EPOLLIN;
    ev.data.fd = STDIN_FILENO;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev) < 0) {
        perror("epoll_ctl");
        return 1;
    }
    printf("waitting for press buttons!!\n");

    int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
    if (nfds < 0) {
        perror("epoll_wait");
        return 1;
    }

    for (int i=0; i<nfds; i++) {
        if (events[i].data.fd == STDIN_FILENO) {
            char buf[128];
            int n = read(STDIN_FILENO, buf, sizeof(buf) - 1);
            buf[n] = '\0';
            printf("you press => : %s\n", buf);
        }
    }

    close(epfd);
    return 0;
}