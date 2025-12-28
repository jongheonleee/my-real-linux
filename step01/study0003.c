#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void) {

    int fd;
    const char *path = "./test_creat";

    fd = creat(path, 0644);

    if (fd == -1) {
        perror("creat failed!!");
        return 1;
    }

    printf("it's success to creat file\n");
    printf("fd = %d\n", fd);
    printf("pwd = %s\n", path);

    const char *msg = "Hello from creat()!\n";
    write(fd, msg, 20);

    close(fd);
    return 0;

}