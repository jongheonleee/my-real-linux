#include <stdio.h>
#include <errno.h>

int main(void) {
    FILE *stream;
    char buf[64];
    size_t nr;

    stream = fopen("sample.bin", "rb");
    if (!stream) {
        perror("fopen");
        return 1;
    }

    nr = fread(buf, 1, sizeof(buf), stream);
    if (nr == 0) {
        if (feof(stream)) {
            printf("[EOF] no data read\n");
        } else if (ferror(stream)) {
            perror("fread");
        }
    } else {
        printf("read %zu bytes:\n", nr);
        fwrite(buf, 1, nr, stdout);
        printf("\n");
    }

    fclose(stream);
    return 0;
}