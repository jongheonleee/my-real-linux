#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int my_system(const char *cmd) {
    int status;
    pid_t pid;

    pid = fork();

    if (pid == -1) {
        return -1;
    } else if (pid == 0) {
        const *argv[4];

        argv[0] = "sh";
        argv[1] = "-C";
        argv[2] = cmd;
        argv[3] = NULL;
        execv("/bin/sh", argv);
        exit(-1);
    }

    if (waitpid(pid, &status, 0) == -1) {
        return -1;
    } else if (WIFEXITED (status)) {
        return WEXITSTATUS(status);
    }

    return -1;
}

int main(void) {
    int ret = my_system("ls -l");
    printf("\n the value of return: %d\n", ret);
    return 0;
}