
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(void) {
    int fd;
    ssize_t nr;
    int ret;
    const char *data = "fsync vs fdatasync example\n";

    fd = open("sync_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    nr = write(fd, data, strlen(data));
    if (nr == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("[INFO] done write (%zd bytes)\n", nr);
    printf("[INFO] not writting on disk!\n");


    printf("[INFO] calling fsync \n");
    ret = fsync(fd);
    if (ret == -1) {
        perror("fsync");
        close(fd);
        return 1;
    }

    printf("[INFO] done fsync");
    close(fd);
    return 0;
}