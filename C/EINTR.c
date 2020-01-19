#include <unistd.h>
#include <errno.h>
#define BUF_SIZE 100
char buf[BUF_SIZE];

int main()
{
    int cnt;
    while ((cnt = read(0, buf, BUF_SIZE)) == -1 &&  errno == EINTR)
        continue;
    if (cnt == -1) /* read() failed with other than EINTR */
        printf("read error\n");
    return 0;
}