# 107_2_OS_project1

## Add System Call
##### 1. Download and extract kernel, take [[OS-HW1]](https://docs.google.com/presentation/d/1KwS9PuGZxLXQ9IEYJE7KUhnz3bHohJLWOH-CRGZkC40/edit#slide=id.p25) as reference
<pre><code>take the newest vision for example
$wget https://www.kernel.org/pub/linux/kernel/v5.x/linux-5.0.10.tar.xz (Download on https://www.kernel.org/)
$tar Jxvf linux-5.0.10.tar.xz
</code></pre>
##### 2. copy  kernel_files/sys_proc_time.c  to  linux-x.x.x/kernel/sys_proc_time.c

##### 3. add in linux-x.x.x/kernel/Makefile:
<pre><code>obj-y += sys_proc_time.o</code></pre>

##### 4. add in linux-x.x.x/include/linux/syscalls.h:
<pre><code>asmlinkage int sys_proc_time(int start, unsigned long *start_sec,
                            unsigned long *start_nsec, unsigned long *end_sec, 
                            unsigned long *end_nsec, int *pid);
</code></pre>

##### 5. add in linux-x.x.x/arch/x86/entry/syscalls/syscall_64.tbl:
<pre><code>345 common proc_time sys_proc_time</code></pre>

##### 6. create .config and first time kernel compilation
<pre><code>$cd linux-x.x.x
$make menuconfig
</code></pre>
> ... if 'make menuconfig' error ... <br>
> $sudo apt-get install libncurses5-dev libncursesw5-dev <br>
> $sudo apt-get install flex bison <br>
<pre><code>$make bzImage
$sudo make modules
$sudo make modules_install
$sudo make install
$sudo mkinitramfs -o /boot/initrd.img-4.14.25
'''reboot'''</code></pre>

##### 7. Comfigure and Compile Kernel (4 = number of cores)
<pre><code>$make -j4 bzImage
$sudo make -j4 install</code></pre>

## Compile & Execute this project
##### Linux is recommended , Windows may cause compile errors at fork() or other system calls.
<pre><code>$make main
$./main < test_data.txt</code></pre>


#### main.c
> 將input資料寫入成多個 process，並根據輸入的 schedule policy 選擇 "schedule.h" 中不同的 function.

#### process
> 定義 process structure、CPU指定、設定 process 的 priority等等.
<pre><code>#define exec_unit_time()   { volatile unsigned long i; for(i=0;i<1000000UL;i++); }
#define CHILD_CPU 1
#define PARENT_CPU 0
int assign_CPU(int pid , int core_number);  //assign process to specified CPU core_number.
int process_execute(Process proc);          //execute while process is ready.
int proc_set_status(pid_t pid , int mod);   //set_priority </code></pre>
#### schedule
> 依據 schedule policy 在不同的 process 中選擇，給予接下來要執行的 process 最高 priority。


