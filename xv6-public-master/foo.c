#include "types.h"
#include "user.h"

#define FORK_COUNT 4

int main()
{
    for (int i = 0; i < FORK_COUNT; ++i)
    {
        int pid = fork();
        if (pid > 0)
            continue;
        if (pid == 0)
        {
            // printf(1, "Process %d started\n", getpid());
            sleep(1000);

            for (int j = 0; j < 2 * i; ++j)
            {
                int x = 1;
                for (long k = 0; k < 1000000000; ++k)
                    x += 1;
            }

            // printf(1, "Process %d finished\n", getpid());
            exit();
        }
    }
    
    for (int i = 0; i < FORK_COUNT; ++i)
        wait();

    exit();
}