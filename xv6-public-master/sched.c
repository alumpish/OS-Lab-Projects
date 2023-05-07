#include "types.h"
#include "user.h"

void display_help()
{
    printf(1, "usage: sched command [arg...]\n");
    printf(1, "Commands and Arguments:\n");
    printf(1, "  info\n");
    printf(1, "  set_queue <pid> <new_queue>\n");
    printf(1, "  set_tickets <pid> <tickets>\n");
}

void display_process_info()
{
    print_process_info();
}

void set_process_queue(int pid, int new_queue)
{
    if (pid < 1)
    {
        printf(1, "Invalid pid\n");
        return;
    }
    if (new_queue < 1 || new_queue > 3)
    {
        printf(1, "Invalid queue\n");
        return;
    }
    int res = change_scheduling_queue(pid, new_queue);
    if (res < 0)
        printf(1, "Error changing queue\n");
    else
        printf(1, "Queue changed successfully\n");
}

void set_process_tickets(int pid, int tickets)
{
    if (pid < 1)
    {
        printf(1, "Invalid pid\n");
        return;
    }
    if (tickets < 0)
    {
        printf(1, "Invalid tickets\n");
        return;
    }
    int res = set_lottery_ticket(pid, tickets);
    if (res < 0)
        printf(1, "Error setting tickets\n");
    else
        printf(1, "Tickets set successfully\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        display_help();
        exit();
    }
    if (!strcmp(argv[1], "info"))
        display_process_info();
    else if (!strcmp(argv[1], "set_queue"))
    {
        if (argc < 4)
        {
            display_help();
            exit();
        }
        set_process_queue(atoi(argv[2]), atoi(argv[3]));
    }
    else if (!strcmp(argv[1], "set_tickets"))
    {
        if (argc < 4)
        {
            display_help();
            exit();
        }
        set_process_tickets(atoi(argv[2]), atoi(argv[3]));
    }
    else
        display_help();
    exit();
}
