
#include <stdio.h>

int main(void) {

    char buf[BUFSIZ];

    setvbuf(stdout, buf, _IOFBF, BUFSIZ);
    printf("Arrr!\n");

    return 0;
}