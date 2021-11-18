#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
    int p[2];
    pipe(p);
    int pid = fork();
    if(pid == 0) {
        char s[2];
        read(p[0], s, 2);
        printf("%d: received ping\n", s[0]);
        exit(0);
    }else {
        char s[2] = {pid, 0};
        printf("%d\n", s[0]);
        write(p[1], s, 2);
        wait(0);
        pid = getpid();
        printf("%d: received pong\n", pid);
        exit(0);
    }
}
