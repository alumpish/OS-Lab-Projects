#include "types.h"
#include "user.h"

#define CHUNK_SIZE 4096

void display_help()
{
    printf(1, "usage: memtest <arg>\n");
    printf(1, "args:\n");
    printf(1, "  stack\n");
    printf(1, "  heap\n");
    printf(1, "  both\n");
}

void recursive(int count)
{
    if (count % 100000 == 0)
        printf(1, "stack: %d\n", count);
    recursive(count + 1);
    printf(1, "End");
}

void heap()
{
    int *ptr;

    for (int i = 0;; i++)
    {
        ptr = (int *)sbrk(CHUNK_SIZE);

        if (ptr == (int *)-1)
        {
            printf(2, "Memory allocation failed. Exiting...\n");
            exit();
        }

        if (i % 10000 == 0)
            printf(1, "Heap: %d\n", i);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        display_help();
        exit();
    }
    if (!strcmp(argv[1], "stack"))
    {
        recursive(1);
    }
    else if (!strcmp(argv[1], "heap"))
    {
        heap();
    }
    else if (!strcmp(argv[1], "both"))
    {
        if (fork() == 0)
            recursive(1);
        else
            heap();
    }
    else
        display_help();
    exit();
}