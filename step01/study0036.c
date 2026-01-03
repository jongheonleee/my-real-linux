#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/resource.h>
#include <time.h>
#include <string.h>

void write_log(const char *msg) {
    FILE *fp = fopen("/tmp/mydaemon.log", "a");
    if (fp == NULL) {
        return;
    }

    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    timestamp[strlen(timestamp) - 1] = '\0';
    
    fprintf(fp, "[%s] %s\n", timestamp, msg);
    fclose(fp);
}

int main (void) {
    pid_t pid;
    struct rlimit rl;
    int i;

    pid = fork();
    if (pid < 0 ) {
        return -1;
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    if (setsid() == -1) {
        return -1;
    }

    if (chdir("/") == -1) {
        return -1;
    }

    if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
        return -1;
    }

    if (rl.rlim_max == RLIM_INFINITY) {
        rl.rlim_max = 1024;
    }

    for (i=0; i<(int)rl.rlim_max; i++) {
        close(i);
    }

    int fd = open("/dev/null", O_RDWR);
    if (fd != -1) {
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
    }

    write_log("Daemon started successfully!!");

    while (1) {
        write_log("Daemon is running!!...");
        sleep(30);
    }

    return 0;
}