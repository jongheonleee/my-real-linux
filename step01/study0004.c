#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(void) {
    int fd;
    char buf[128];
    ssize_t n;

    fd = open("./read_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open for write!!");
        return 1;
    }

    write(fd, "Hello read() system call!!\n", 26);
    close(fd);

    fd = open("./read_test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open for read");
        return 1;
    }

    n = read(fd, buf, sizeof(buf) - 1);
    if (n == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    buf[n] = '\0';

    printf("the number of bytes for read(): %ld\n", n);
    printf("content: \n%s", buf);

    close(fd);
    return 0;
}