#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "schedule.h"




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
    int policy;

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
        policy = FIFO;
    }
    else if(strcmp(policy , "RR") == 0)
    {
        /* TODO */
        policy = RR;
    }
    else if(strcmp(policy , "SJF") == 0)
    {
        /* TODO */
        policy = SJF;
    }
    else if(strcmp(policy , "PSJF") == 0)
    {
        /* TODO */
        policy = PSJF;
    }
    else
    {
        printf("Policy doesn't exist.\n");
        return -1;
    }
    scheduling(proc, process_num, policy);

    return 0;
}
