#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


int main(void) {
    int fd;
    off_t ret;
    char buf[32];

    fd = open("lseek_test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }



    ret = lseek(fd, 0, SEEK_CUR);
    if (ret == (off_t) - 1) {
        perror("lseek(SEEK_CUR)");
        close(fd);
        return 1;
    }
    printf("[INFO] file's offset: %ld\n", (long)ret);

    ret = lseek(fd, (off_t)1825, SEEK_SET);
    if (ret == (off_t)-1) {
        perror("lseek(SEEK_SET)");
        close(fd);
        return 1;
    }

    printf("[INFO] after move, file's offset: %ld\n", (long)ret);

    ssize_t nr = read(fd, buf, sizeof(buf) - 1);
    if (nr == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    if (nr == 0) {
        printf("[INFO] reach out EOF\n");
    } else {
        buf[nr] = '\n';
        printf("[INFO] losing data (%zd bytes): \"%s\"\n", nr, buf);
    }

    close(fd);
    return 0;
}