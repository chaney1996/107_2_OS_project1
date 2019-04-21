#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/timekeeping.h>


asmlinkage int sys_proc_time(int start, unsigned long *start_sec,
                            unsigend long *start_nsec, unsigned long *end_sec, 
                            unsigned long *end_nsec, int *pid)
{
    struct timespec proc_time;
    getnstimeofday(&proc_time);
    if(start){
        *start_sec = proc_time.tv_sec;
        *start_nsec = proc_time.tv_nsec;
    }else{
        *end_sec = proc_time.tv_sec;
        *end_nsec = proc_time.tv_nsec;

        printk("[project1] %d %lu.%09lu %lu.%09lu\n", *pid, 
        *start_sec, *start_nsec, *end_sec, *end_nsec);
    }
    
    return 0;
}