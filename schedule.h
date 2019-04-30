#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_


#include "process.h"



int FIFO_next_process(int , struct Process*);

int RR_next_process(int , struct Process* );

int SJF_next_process(int , struct Process* );

int PSJF_next_process(int , struct Process*);

#define FIFO	1
#define RR	2
#define SJF	3
#define PSJF	4

/* Return next process to run */
//int next_process(struct process *proc, int nproc, int policy);

/* Running scheduler */
int scheduling(struct process *proc, int nproc, int policy);



#endif
