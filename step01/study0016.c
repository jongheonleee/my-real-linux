#include <stdio.h>

int main(void) {

    FILE *stream;
    char str[64];
    char *s;
    int c;
    int n = sizeof(str);

    stream = fopen("sample.txt", "r");
    if (!stream) {
        perror("fopen");
        return 1;
    }

    s = str;

    while (--n > 0 && (c = fgetc(stream)) != EOF) {
        *s++ = (char)c;
    }

    *s = '\n';

    if (c == EOF) {
        if (feof(stream)) {
            printf("[EOF reached]\n");
        } else if (ferror(stream)) {
            perror("fgetc");
        }
    }

    printf("result string: \"%s\"\n", str);
    fclose(stream);
    return 0;
}