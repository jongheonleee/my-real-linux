#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(void) {

    printf("before exec new process (pid: %d)\n", getpid());

    int result = execl("/bin/ls", "ls", "-l", NULL);

    if (result == -1) {
        fprintf(stderr, "failed to call execl: %s\n", strerror(errno));

    }

    char *args[] = {"ls", "-a", "-l", NULL};
    printf("try to calling execvp...\n");

    execvp(args[0], args);
    perror("failed to call execvp");
    return 0;
}

