#include "types.h"
#include "stat.h"
#include "user.h"

int main(void)
{
    int pid;

    pid = fork();
    if (pid == 0)
      sleep(100);
    else if (pid > 0) {
      printf(1, "Parent process (pid %d) has %d children.\n", getpid(), get_children_count());
      kill_first_child();
      sleep(50);
      printf(1, "After killing first child parent process (pid %d) has %d children.\n", getpid(), get_children_count());
      wait();
    }
    else
      printf(1, "fork failed\n");

    exit();
}
