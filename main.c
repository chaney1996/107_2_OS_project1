#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "schedule.h"

//要先見個queue存嗎


/* define comparison for quicksort*/
int cmp(const void *a , const void *b)
{
    Process c = *(Process *)a;
    Process d = *(Process*)b;
    if(c.ready_time<d.ready_time)
        return -1;
    else if(c.ready_time == d.ready_time)
        return 0;
    else
        return 1;
}



int main()
{
    char policy[5];
    int process_num , i;

    /* read in schedule policy and process number */
    scanf("%s", policy);
    scanf("%d", &process_num);

    /* Create process array */
    Process *proc = (Process*)malloc(process_num * sizeof(Process));
    for(i = 0 ; i < process_num ; i++)
    {
        scanf("%s %d %d",proc[i].name , &proc[i].ready_time , &proc[i].exec_time);
    }

    /* sorting process by ready time */
    qsort(proc , process_num , sizeof(Process) , cmp);


    if(strcmp(policy , "FIFO") == 0)
    {
        printf("FIFO has been read.\n");
        /* TODO */
        // FIFO_scheduling(proc);
    }
    else if(strcmp(policy , "RR") == 0)
    {
        /* TODO */
        // RR_scheduling();
    }
    else if(strcmp(policy , "SJF") == 0)
    {
        /* TODO */
        // SJF_scheduling();
    }
    else if(strcmp(policy , "PSJF") == 0)
    {
        /* TODO */
        // PSJF_scheduling();
    }
    else
    {
        printf("Policy doesn't exist.\n");
        return -1;
    }
    

    return 0;
}
