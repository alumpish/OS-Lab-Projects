#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"

static int find_fibonacci_number(int n) {
    if (n <= 0) 
        return -1;

    if (n == 1)
        return 0;

    if (n == 2) 
        return 1;

    return find_fibonacci_number(n - 1) + find_fibonacci_number(n - 2);
}

int
sys_find_fibonacci_number(void) {
    return find_fibonacci_number(myproc()->tf->ebx);
}