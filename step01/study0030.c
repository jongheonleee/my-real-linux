#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(void) {

    pid_t pid;

    pid = fork();
    if (pid > 0) {
        printf("im the parent of pid=%d!\n", pid);
        wait(NULL);
        printf("end of program!!\n");
    } else if (!pid) {
        char *args[] = { "ls", "-l", NULL};
        int ret;

        ret = execv("/bin/ls", args);

        if (ret == -1) {
            perror("execv");
            exit (EXIT_FAILURE);
        }
        printf("im the child\n");
        
    } else if (pid == -1) {
        perror("fork");
    }   

    return 0;
}