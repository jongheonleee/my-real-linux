
#include <stdio.h>
#include <errno.h>

int main(void) {
    FILE *stream;
    int c;

    stream = fopen("sample.txt", "r");
    if (!stream) {
        perror("fopen");
        return 1;
    }

    while (1) {
        c = fgetc(stream);

        if (c == EOF) {

            if (feof(stream)) {
                printf("\n[EOF] end of file reached\n");
            } else if (ferror(stream)) {
                perror("fgetc");
            }
            break;
        }

        printf("c = '%c' (0x%02x)\n", c, c);
    }

    fclose(stream);
    return 0;
}