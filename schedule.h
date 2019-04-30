#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

#include "process.h"


#define FIFO 0
#define RR 1
#define SJF 2
#define PSJF 3



int FIFO_next_process(int , struct Process*);

int RR_next_process(int , struct Process* );

int SJF_next_process(int , struct Process* );

int PSJF_next_process(int , struct Process*);


/* Return next process to run */
//int next_process(struct process *proc, int nproc, int policy);

/* Running scheduler */
int scheduling(struct Process *proc, int nproc, int policy);


#endif
