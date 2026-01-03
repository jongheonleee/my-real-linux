#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    } else if (pid != 0) {
        exit(EXIT_SUCCESS);
    }

    if (setsid() == -1) {
        perror("setsid");
        return -1;
    }

    return 0;
}