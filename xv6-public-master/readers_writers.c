#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define NREADERS 3
#define NWRITERS 2

#define WRT 0
#define MUTEX 1
#define PRINT_MUTEX 2

#define ATOMIC(x)             \
    sem_acquire(PRINT_MUTEX); \
    x;                        \
    sem_release(PRINT_MUTEX);

void init_sems()
{
    sem_init(WRT, 1, "wrt");
    sem_init(MUTEX, 1, "mtx");
    sem_init(PRINT_MUTEX, 1, "prmtx");
}

void reader(int id)
{
    int i = 5;
    while (i--)
    {
        ATOMIC(printf(1, "Reader %d want to access readcount\n", id))
        sem_acquire(MUTEX);
        modvar(1);
        ATOMIC(printf(1, "Reader %d increased readcount to %d\n", id, getvar()))
        if (getvar() == 1)
        {
            ATOMIC(printf(1, "Reader %d want to get WRT\n", id))
            sem_acquire(WRT);
        }
        sem_release(MUTEX);

        ATOMIC(printf(1, "Reader %d Read\n", id))

        sem_acquire(MUTEX);
        modvar(-1);
        ATOMIC(printf(1, "Reader %d decreased readcount to %d\n", id, getvar()))

        if (getvar() == 0)
        {
            ATOMIC(printf(1, "Reader %d Released WRT\n", id))
            sem_release(WRT);
        }
        sem_release(MUTEX);

        sleep(10);
    }
}

void writer(int id)
{
    int i = 5;
    while (i--)
    {
        ATOMIC(printf(1, "Writer %d want to get WRT\n", id))
        sem_acquire(WRT);
        ATOMIC(printf(1, "Writer %d Wrote\n", id))
        sem_release(WRT);

        sleep(10);
    }
}

void start()
{
    for (int i = 0; i < NREADERS; i++)
    {
        if (fork() == 0)
        {
            reader(i);
            exit();
        }
    }

    sleep(100);

    for (int i = 0; i < NWRITERS; i++)
    {
        if (fork() == 0)
        {
            writer(i);
            exit();
        }
    }

    for (int i = 0; i < NREADERS + NWRITERS; i++)
        wait();
}

int main(void)
{
    // modvar(1);

    init_sems();
    start();
    exit();
}
