
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(void) {

    int fd;
    int ret;
    const char *data = "fsync fallback example\n";

    fd = open("sync_fallback.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (write(fd, data, strlen(data)) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("[INFO] done write!!\n");

    ret = fsync(fd);
    if (ret == -1) {
        if (errno == EINVAL) {
            printf("[WARN] fsync not supported, trying fdatasync\n");

            if (fdatasync(fd) == -1) {
                perror("fdatasync");
                close(fd);
                return 1;
            }

            printf("[INFO] success fdataasync\n");
        } else {
            perror("fsync");
            close(fd);
            return 1;
        }
    } else {
        printf("[INFO] success fsync\n");
    }

    close(fd);
    return 0;
}