#include "types.h"
#include "user.h"

int main(void)
{
    int pid;
    int i;

    for (i = 0; i < 3; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            // child process
            sleep(50);
            exit();
        }
    }

    printf(1, "Parent process (pid %d) has %d children.\n", getpid(), get_children_count());

    for (int i = 0; i < 3; ++i)
        wait();

    exit();
}
