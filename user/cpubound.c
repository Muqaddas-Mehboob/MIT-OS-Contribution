#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int pid = getpid();
  printf("CPU-bound process started. PID = %d\n", pid);
  int start = uptime();
  printf("CPUBEGIN ticks = %d\n", start);
  int iters = 5000; // default workload
  if (argc > 1)
    iters = atoi(argv[1]);
  // Simulate CPU-heavy computation
  volatile unsigned long x = 1;
  for (int i = 0; i < iters; i++)
    x = x * 1103515245 + 12345;
  int end = uptime();
  printf("CPUEND ticks = %d\n", end);
  printf("CPU-bound process (PID = %d) completed\n", pid);
  printf("Total elapsed ticks = %d\n", end - start);
  exit(0);
}
