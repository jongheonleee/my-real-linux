#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


// if u run this?, "gcc study0001.c -o study0001 && ./study0001"
int main(void) {
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    printf("파일 열기 성공 (fd=%d)\n", fd);

    const char *msg = "Hello fsync world!\n";
    write(fd, msg, strlen(msg));
    printf("파일에 데이터 write 완료\n");

    if (fsync(fd) == -1) {
        fprintf(stderr, "fsync 실패!\n");
        fprintf(stderr, "errno: %s\n", strerror(errno));
    } else {
        printf("fsync 성공: 디스크에 데이터가 실제로 기록됨\n");
    }

    close(fd);
    printf("파일 닫기 완료\n");

    return 0;
}