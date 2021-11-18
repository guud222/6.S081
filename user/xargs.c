#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char *myargv[32];
    char buf[512];
    char tmp[512];
    int idx = 0;
    int cnt = 0;
    int n = 0;
    for(int i = 1; i < argc; i++)
        myargv[cnt++] = argv[i];
    while(1)
    {
        n = read(0, buf, sizeof buf);
        if(n == 0)
            break;
        for(int i = 0; i < n; i++)
            if(buf[i] == ' ' || buf[i] == '\n')
            {
                tmp[idx] = 0;
                myargv[cnt] = (char *)malloc(idx);
                for(int j = 0; j <= idx; j++)
                    myargv[cnt][j] = tmp[j];
                myargv[++cnt] = 0;
                if(buf[i] == '\n')
                {
                    if(fork() == 0)
                        exec(argv[1], myargv);
                    else
                        wait(0);
                    cnt = argc - 1;
                }
                idx = 0;
            }
            else
                tmp[idx++] = buf[i];
    }
    exit(0);
}
