#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


extern int syscalls_count[25]; // assuming there are 25 system calls in xv6

int
sys_find_most_callee(void)
{
  int i, max_calls = 0, most_called_syscall = 0;
  for (i = 0; i < 25; i++) {
    if (syscalls_count[i] > max_calls) {
      max_calls = syscalls_count[i];
      most_called_syscall = i;
    }
  }
  return most_called_syscall;
}

int
sys_get_children_count(void)
{
  return myproc()->children_count;
}

int
sys_kill_first_child(void)
{
  return kfc();
}

int
sys_change_scheduling_queue(void)
{
  int queue_number, pid;
  if(argint(0, &pid) < 0 || argint(1, &queue_number) < 0)
    return -1;

  if(queue_number < ROUND_ROBIN || queue_number > FCFS)
    return -1;

  return change_queue(pid, queue_number);
}

int
sys_set_lottery_ticket(void) {
  int pid, tickets;
  if(argint(0, &pid) < 0 || argint(1, &tickets) < 0)
    return -1;

  if (tickets < 0)
    return -1;

  return set_lottery_ticket(pid, tickets);
}

int
sys_print_process_info(void)
{
  print_process_info();
  return 0;
}