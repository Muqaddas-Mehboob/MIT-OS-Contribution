#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int fibonacci(int n){
    if(n<=1){
        return 1;
    }
    else {
        return (fibonacci(n-2) + fibonacci(n-1));
    }
}


int main(int argc, char *argv[]) {
  int pid = getpid();
  struct procinfo info;
  getprocinfo(pid, &info);
  printf("CPU time: %d | Created: %d | Total ticks: %d | Times scheduled: %d\n",
         info.cputime, info.creation_time, info.total_cpu_ticks, info.times_scheduled);
  printf("CPU-bound process started. PID = %d\n", pid);
  printf("CPU-bound process (PID = %d) completed\n", pid);

  int start = uptime(); 
  printf("Start time: %d\n", start);
  for (int i = 1; i <= 40; i++) {  
    printf("%d: %d\n", i, fibonacci(i));
  }
  int end = uptime();
  int total = end - start;
  printf("CPU-bound process (PID = %d) completed\n", pid);
  printf("Total elapsed ticks of CPU Bound: %d\n", total);
  getprocinfo(pid, &info);
  printf("(CPU PERFORMANCE METRICS): CPU time: %d | Created: %d | Total ticks: %d | Times scheduled: %d\n",
         info.cputime, info.creation_time, info.total_cpu_ticks, info.times_scheduled);
  exit(0);
}
