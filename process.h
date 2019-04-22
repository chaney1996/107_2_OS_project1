#ifndef _PROCESS_H_
#define _PROCESS_H_


#define exec_unit_time()   { volatile unsigned long i; for(i=0;i<1000000UL;i++); }

typedef struct _Process
{
    char name[4];
    int ready_time;
    int exec_time;

}Process;

int assign_CPU(int pid , int core_number);
int process_execute(Process proc);





#endif