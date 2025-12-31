#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void) {
    FILE *stream;
    int fd;

    stream = fopen("/etc/manifest", "r");
    if (!stream) {
        perror("fopen /etc/manifest");
        printf("failed to fopen\n");
    } else {
        fclose(stream);
    }

    fd = open("temp.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open temp.txt");
        return 1;
    }

    write(fd, "Hello fdopen!\n", 14);

    lseek(fd, 0, SEEK_SET);

    stream = fdopen(fd, "r");
    if (!stream) {
        perror("fdopen");
        close(fd);
        return 1;
    }

    char buf[128];
    if (fgets(buf, sizeof(buf), stream)) {
        printf("the contents : %s", buf);
    }

    fclose(stream);
    return 0;
}