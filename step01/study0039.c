#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>

int main() {
    int ret;

    int crnt_nice = getpriority(PRIO_PROCESS, 0);
    printf("current nice's value: %d\n", crnt_nice);
    printf("add 10 on nice's...\n");

    errno = 0;
    ret = nice(10);

    if (ret == -1 && errno != 0) {
        perror("failed to call nice()");
        return -1;
    } else {
        printf("success!!, new nice's value: %d\n", ret);
    }

    printf("finally => (getpriority): %d\n", getpriority(PRIO_PROCESS, 0));
    return 0;
}