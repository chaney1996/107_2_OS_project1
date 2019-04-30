#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule.h"
#include "process.h"

#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>


/* Last context switch time for RR scheduling */
static int t_last;

/* Current unit time */
static int ntime;

/* Index of running process. -1 if no process running */
static int running;

/* Number of finish Process */
static int finish_cnt;

/* Sort processes by ready time */
int cmp(const void *a, const void *b) {
	return ((struct Process *)a)->ready_time - ((struct Process *)b)->ready_time;
}

/* Return index of next process  */
int next_process(struct process *proc, int nproc, int policy)
{
	/* Non-preemptive */
	if (running != -1 && (policy == SJF || policy == FIFO))
		return running;

	int ret = -1;

	if (policy == PSJF || policy ==  SJF) {
		for (int i = 0; i < nproc; i++) {
			if (proc[i].pid == -1 || proc[i].t_exec == 0)
				continue;
			if (ret == -1 || proc[i].t_exec < proc[ret].t_exec)
				ret = i;
		}
	}

	else if (policy == FIFO) {
		for(int i = 0; i < nproc; i++) {
			if(proc[i].pid == -1 || proc[i].t_exec == 0)
				continue;
			if(ret == -1 || proc[i].t_ready < proc[ret].t_ready)
				ret = i;
		}
        }

	else if (policy == RR) {
		if (running == -1) {
			for (int i = 0; i < nproc; i++) {
				if (proc[i].pid != -1 && proc[i].t_exec > 0){
					ret = i;
					break;
				}
			}
		}
		else if ((ntime - t_last) % 500 == 0)  {
			ret = (running + 1) % nproc;
			while (proc[ret].pid == -1 || proc[ret].t_exec == 0)
				ret = (ret + 1) % nproc;
		}
		else
			ret = running;
	}

	return ret;
}

int FIFO_next_process(int n  ,struct Process proc[]){
	if (running != -1)
		return running;
	int ret = -1;
	for(int i = 0; i < n; i++) {
		if(proc[i].pid == -1 || proc[i].exec_time == 0)
			continue;
		if(ret == -1 || proc[i].ready_time < proc[ret].ready_time)
			ret = i;
	}
	return ret;
}

int RR_next_process(int n  ,struct Process proc[])
	const int q = 5;
	int ret = -1;

        if (running == -1) {
		for (int i = 0; i < n; i++) {
			if( proc[i].pid < 0)
				continue;
			if ( proc[i].exec_time > 0)
				return i;
		}
	}
	else if ((ntime - t_last) % q == 0)  {
		ret = (running + 1) % n;
		while (proc[ret].pid < 0 || proc[ret].exec_time == 0)
			ret = (ret + 1) % n;
	}
	else
		ret = running;
	return ret;
}

int PSJF_next_process(int n  ,struct Process proc[]){
	int ret = -1;
	for (int i = 0; i < n; i++) {
		if (proc[i].pid == -1 || proc[i].exec_time == 0)
			continue;
		if (ret == -1 || proc[i].exec_time < proc[ret].exec_time)
			ret = i;
	}
	return ret;
}


int SJF_next_process(int n  ,struct Process proc[]){
	if (running != -1)
		return running;
	int ret = -1;
	for (int i = 0; i < n; i++) {
		if (proc[i].pid == -1 || proc[i].exec_time == 0)
			continue;
		if (ret == -1 || proc[i].exec_time < proc[ret].exec_time)
			ret = i;
	}
}

int scheduling(struct Process *proc, int nproc, int policy)
{
	qsort(proc, nproc, sizeof(struct process), cmp);

	/* Initial pid = -1 imply not ready */
	for (int i = 0; i < nproc; i++)
		proc[i].pid = -1;

	/* Set single core prevent from preemption */
	proc_assign_cpu(0, PARENT_CPU);
	
	/* Set high priority to scheduler */
	proc_set_status( 0 , WAKE);
	
	/* Initial scheduler */
	ntime = 0;
	running = -1;
	finish_cnt = 0;
	
	while(1) {
		//fprintf(stderr, "Current time: %d\n", ntime);

		/* Check if running process finish */
		if (running != -1 && proc[running].exec_time == 0) {
		
#ifdef DEBUG
			fprintf(stderr, "%s finish at time %d.\n", proc[running].name, ntime);
#endif
			//kill(running, SIGKILL);
			waitpid(proc[running].pid, NULL, 0);
			printf("%s %d\n", proc[running].name, proc[running].pid);
			running = -1;
			finish_cnt++;

			/* All process finish */
			if (finish_cnt == nproc)
				break;
		}

		/* Check if process ready and execute */
		for (int i = 0; i < nproc; i++) {
			if (proc[i].t_ready == ntime) {
				proc[i].pid = proc_exec(proc[i]);
				proc_set_status( proc[i].pid , BLOCK);
#ifdef DEBUG
				fprintf(stderr, "%s ready at time %d.\n", proc[i].name, ntime);
#endif
			}

		}

		/* Select next running  process */
		int next = next_process(proc, nproc, policy);
		if (next != -1) {
			/* Context switch */
			if (running != next) {
				proc_set_status( proc[next].pid , WAKE);
				proc_set_status( proc[running].pid , BLOCK);
				running = next;
				t_last = ntime;
			}
		}

		/* Run an unit of time */
		proc_unit_time();
		if (running != -1)
			proc[running].t_exec--;
		ntime++;
	}

	return 0;
}
