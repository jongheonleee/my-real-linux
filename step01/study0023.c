#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>

int main(void) {
    int epfd;
    int fd = STDIN_FILENO;
    struct epoll_event event;
    int ret;

    epfd = epoll_create1(0);
    if (epfd < 0) {
        perror("epoll_create1");
        return 1;
    }

    event.data.fd = fd;
    event.events = EPOLLIN;

    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
    if (ret < 0) {
        perror("epoll_ctl ADD");
        return 1;
    }

    printf("register STDIN in EPOLLIN\n");

    event.events = EPOLLIN | EPOLLET;
    ret = epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &event);
    if (ret < 0) {
        perror("epoll_ctl MOD");
        return 1;
    }

    printf("modify STDIN event\n");
    close(epfd);
    return 0;
}