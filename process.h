#ifndef _PROCESS_H_
#define _PROCESS_H_


#define exec_unit_time()   { volatile unsigned long i; for(i=0;i<1000000UL;i++); }

typedef struct _Process
{
    char name[4];
    int ready_time;
    int exec_time;
    pid_t pid;
}Process;

int assign_CPU(int pid , int core_number);
int process_execute(Process proc);


#define CHILD_CPU 1
#define PARENT_CPU 0

/* Set very low priority tp process */
int proc_block(int pid);

/* Set high priority to process */
int proc_wakeup(int pid);


#endif
