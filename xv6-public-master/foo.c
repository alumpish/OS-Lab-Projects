#include "types.h"
#include "user.h"

#define FORK_COUNT 4
#define LOOP_COUNT 1000000000

int main()
{
    for (int i = 0; i < FORK_COUNT; ++i)
    {
        int pid = fork();
        if (pid > 0)
            continue;
        if (pid == 0)
        {
            sleep(1000);

            for (int j = 0; j < 2 * i; ++j)
            {
                int x = 1;
                for (long k = 0; k < LOOP_COUNT; k++)
                    x += 1;
            }

            exit();
        }
    }
    
    for (int i = 0; i < FORK_COUNT; ++i)
        wait();

    exit();
}