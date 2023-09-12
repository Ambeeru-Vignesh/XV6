#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "fcntl.h"
//#include "stdio.h"  
//#include "string.h" 

int sys_uniq(void) {
 /*   int file;

    if (argint(0, &file) < 0)
        return -1;

    char currentChar;
    char curr_line[256];
    char prev_line[256] = "";
    int lineIndex = 0;

    while (read(file, &currentChar, 1) > 0) {
        if (currentChar == '\n') {
            curr_line[lineIndex] = '\0';
            if (strcmp(curr_line, prev_line) != 0) {
                printf(1, "%s\n", curr_line);
                strcpy(prev_line, curr_line);
            }
            lineIndex = 0;
        } else {
            curr_line[lineIndex++] = currentChar;
        }
    }

    close(file);*/
    return 0;
}


int
sys_hello(void) {
   cprintf("Hello world\n");
   return 0;
}

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
