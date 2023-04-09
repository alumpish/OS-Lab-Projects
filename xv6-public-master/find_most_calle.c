#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int pid = mostcalled();
    printf(1, "Most called systemcall is: %d\n", pid);
    exit();
}