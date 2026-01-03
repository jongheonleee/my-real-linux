
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {

    int status;
    pid_t pid;

    pid = waitpid(1742, &status, WNOHANG);

    if (pid == -1) {
        perror("waitpid");
    } else {
        printf("pid = %d\n", pid);

        if (WIFEXITED(status)) {
            printf("Normal termination with exit status = %d\n", WEXITSTATUS (status));

            if (WIFSIGNALED (status)) {
                printf("Killed by signal=%d%s\n", WTERMSIG (status), WCOREDUMP (status) ? " (dumped core)" : "");
            }
        }
    }

    return 0;

}