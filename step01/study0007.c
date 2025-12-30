#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(void) {
    // step1 
    const char *buf = "My ship is solid!";
    ssize_t nr;

    nr = write(STDOUT_FILENO, buf, strlen (buf));

    if (nr == -1) {
        perror("write");
        return 1;
    }

    printf("the number of bytes: %zd\n", nr);

    // step2 
    unsigned long word = 1720;
    size_t count = sizeof(word);
    size_t written = 0;
    unsigned char *ptr = (unsigned char *)&word;

    int fd = STDOUT_FILENO;

    while (written < count){
        nr = write(fd, ptr + written, count - written);

        if (nr == -1) {
            if (errno == EINTR) {
                printf("[INFO] write interrupted, retryinh,,,\n");
                continue;
            }

            perror("write");
            return 1;
        }

        if (nr == 0) {
            printf("[WARN] write returned 0, stopping\n");
            break;
        }

        printf("[INFO] write() returned %zd bytes\n", nr);
        written += nr;
    }
    
    if (written == count) {
        printf("[INFO] allbytes (%zu bytes)\n", written);
    } else {
        printf("[WARN] (%zu / %zu bytes)\n", written, count);
    }

    return 0;
}