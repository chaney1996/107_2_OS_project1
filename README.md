# 107_2_OS_project1


#### Compile & Execution
<pre><code>make all</code></pre>
<pre><code>./main < test_data.txt</code></pre>


#### main.c
> 將input資料寫入成多個 process，並根據選擇的 schedule policy 選擇 "schedule.h" 中不同的 function.

#### process
> 定義 process structure、CPU指定、設定 process 的 priority等等.

#### schedule
> 依據 schedule policy 在不同的 process 中選擇，給予接下來要執行的 process 最高 priority。
