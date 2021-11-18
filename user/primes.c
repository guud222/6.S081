#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void primes(int nums[])
{
    int p[2];
    pipe(p);
    int f = nums[0];
    printf("prime %d\n", f);
    for(int i = 0; nums[i]; i++)
        if(nums[i] % f != 0)
        {
            write(p[1], (char*)&nums[i], 4);
        }
    close(p[1]);
    if(fork() == 0)
    {
        int n;
        int cnt = 0;
        char buf[4];
        while(1)
        {
            n = read(p[0], buf, sizeof buf);
            if(n == 0)
                break;
            nums[cnt++] = *((int*)buf);
            nums[cnt] = 0;
        }
        if(cnt)
            primes(nums);
        exit(0);
    }
    else
        wait(0);
}

int main(int argc, char **argv)
{
    int nums[300];
    for(int i = 0; i <= 33; i++)
        nums[i] = i + 2;
    primes(nums);
    exit(0);
}
