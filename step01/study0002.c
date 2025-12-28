
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>


int main(void) {
    int fd;
    const char *path = "./madagascar";

    fd = open(path, O_RDONLY | O_CREAT, 0644);

    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    printf("it's success to open the file\n");
    printf("fd: %d\n", fd);
    printf("path: %s\n", path);

    struct stat st;
    if (stat(path, &st) == 0) {
        printf("file's size: %ld bytes\n", st.st_size);
        printf("file's owner: %o\n", st.st_mode & 0777);
    }

    close(fd);
    printf("it's success to close the file");

    return 0;
}