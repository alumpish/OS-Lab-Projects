#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "shm.h"

#define NREADERS 3
#define NWRITERS 2

#define WRT 0
#define MUTEX 1
#define PRINT_MUTEX 2

readcount = 0;


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
        sem_acquire(MUTEX);
        readcount++;
        // ATOMIC(printf(1, "%d readcount %d\n", id, readcount));
        if (readcount == 1)
        {
            sem_acquire(WRT);
        }
        sem_release(MUTEX);

        ATOMIC(printf(1, "Reader %d: Read\n", id))

        sem_acquire(MUTEX);
        readcount--;
        // printf(1, "Reader %d won't read\n", id);
        if (readcount == 0)
            sem_release(WRT);
        sem_release(MUTEX);

        sleep(10);
    }
}

void writer(int id)
{
    int i = 5;
    while (i--)
    {
        sem_acquire(WRT);

        ATOMIC(printf(1, "Writer %d: Wrote\n", id))

        sem_release(WRT);

        sleep(500);
    }
}

void start()
{
    int i;

    for (i = 0; i < NREADERS; i++)
    {
        if (fork() == 0)
        {
            reader(i);
            exit();
        }
    }

    for (i = 0; i < NWRITERS; i++)
    {
        if (fork() == 0)
        {
            writer(i);
            exit();
        }
    }

    for (i = 0; i < NREADERS + NWRITERS; i++)
        wait();
}

int main(void)
{
    init_sems();
    start();
    exit();
}
