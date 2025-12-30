
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 16 

int main(void) {
    int fd;
    ssize_t ret;
    size_t len;
    char buf[BUF_SIZE];
    char *ptr;
    
    // open the file
    fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("it's start reading file\n");

    while((ret = read(fd, buf, BUF_SIZE)) != 0) {

        if (ret == -1) {
            if (errno == EINTR) {
                printf("read interrupted, retrying,,,\n");
                continue;
            }

            perror("read");
            break;
        }

         // print the number of bytes 
        printf("the number of byts: %zd\n", ret);

        ptr = buf;
        len = ret;

        while (len > 0) {
            ssize_t written = write(STDOUT_FILENO, ptr, len);

            if (written == -1) {
                perror("write");
                close(fd);
                return 1;
            }

            len -= written;
            ptr += written;
        }

        printf("\n================== chunk end =================\n");

    }

    if (ret == 0) {
        printf("\nEOF\n");
    }

    close(fd);
    return 0;
}