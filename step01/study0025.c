#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {

    int fd;
    struct stat st;
    void *p;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    if (fstat(fd, &st) < 0) {
        perror("fstat");
        close(fd);
        return 1;
    }

    p = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    write(STDOUT_FILENO, p, st.st_size);
    munmap(p, st.st_size);
    close(fd);

    return 0;
}