# 107_2_OS_project1

## Add System Call

##### 1、copy kernel_files/sys_proc_time.c to linux/kernel/sys_proc_time.c

##### 2、add in linux/kernel/Makefile:
<pre><code>obj -y += sys_proc_time.o</code></pre>

##### 3、add in linux/include/linux/syscall.h:
<pre><code>asmlinkage int sys_proc_time(int start, unsigned long *start_sec,
                            unsigend long *start_nsec, unsigned long *end_sec, 
                            unsigned long *end_nsec, int *pid) 
</code></pre>

##### 4、add in linux/arch/x86/entry/syscalls/syscall_64.tbl:
<pre><code>345 common proc_time sys_proc_time</code></pre>

##### 5、Comfigure and Compile Kernel
<pre><code>make bzImage -j 4</code></pre>
<pre><code>sudo make install -j 4</code></pre>

## Compile & Execution ("Linux" is recommended , "Windows" may cause compile errors.)
<pre><code>make all</code></pre>
<pre><code>./main < test_data.txt</code></pre>


#### main.c
> 將input資料寫入成多個 process，並根據輸入的 schedule policy 選擇 "schedule.h" 中不同的 function.

#### process
> 定義 process structure、CPU指定、設定 process 的 priority等等.

#### schedule
> 依據 schedule policy 在不同的 process 中選擇，給予接下來要執行的 process 最高 priority。


