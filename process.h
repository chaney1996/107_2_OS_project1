#ifndef _PROCESS_H_
#define _PROCESS_H_


#define exec_unit_time()   { volatile unsigned long i; for(i=0;i<1000000UL;i++); }

typedef struct _Process
{
    char name[32];
    int ready_time;
    int exec_time;
    pid_t pid;
}Process;

int assign_CPU(pid_t pid , int core_number);
int process_execute(Process proc);


#define CHILD_CPU 1
#define PARENT_CPU 0

enum { WAKE , BLOCK }

int proc_set_status(pid_t pid , int mod);


#endif
