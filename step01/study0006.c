#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 16 

int main(void) {
    int fd;
    char buf[BUFSIZE];
    ssize_t nr;

    fd = open("test.txt", O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    start:
        nr = read(fd, buf, BUFSIZE);

        if (nr == -1) {
            if (errno == EINTR) {
                printf("[INFO] read interrupted by signal (EINTR), retrying...\n");
                goto start;
            }

            if (errno == EAGAIN) {
                printf("[INFO] no data available now (EAGAIN), try again later\n");
                sleep(1);   // 바쁜 루프 방지
                goto start;
            }

            perror("read");
            close(fd);
            return 1;
        }

        if (nr == 0) {
            printf("[INFO] EOF reached\n");
            close(fd);
            return 0;
        }

        printf("[INFO] read %zd bytes: ", nr);
        write(STDOUT_FILENO, buf, nr);
        printf("\n");

        goto start; 

    return 0;
}