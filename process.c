#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "process.h"
#include "schedule.h"
#include <unistd.h> //for system call


/* assign process to specified CPU core_number */
int assign_CPU(int pid , int core_number)
{
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(core_number , &set);
    
    if(sched_setaffinity(pid , sizeof(set) , &set) == -1) // if error occurs
    {
        perror("sched_setaffinity");
        exit(EXIT_FAILURE);
    }

    return 0;

}



int process_execute(Process proc)
{
    struct timespec start, end;
    int current_pid;
    int pid = fork();
    if(pid < 0){
        perror("fork error:");
        return -1;
    }
    if(pid == 0){ //child process
        current_pid = getpid();
        syscall(345, 1, &start.tv_sec, &start.tv_nsec, &end.tv_sec, &end.tv_nsec, &current_pid);
        for (int i = 0; i < proc.exec_time; i++) {
			exec_unit_time();
		}
        syscall(345, 0, &start.tv_sec, &start.tv_nsec, &end.tv_sec, &end.tv_nsec, &current_pid);
    }
    return 0;
}


int proc_block(int pid)
{
	struct sched_param param;
	
	/* SCHED_IDLE should set priority to 0 */
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_IDLE, &param);
	
	if (ret < 0) {
		perror("sched_setscheduler");
		return -1;
	}

	return ret;
}

int proc_wakeup(int pid)
{
	struct sched_param param;
	
	/* SCHED_OTHER should set priority to 0 */
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_OTHER, &param);
	
	if (ret < 0) {
		perror("sched_setscheduler");
		return -1;
	}

	return ret;
}

