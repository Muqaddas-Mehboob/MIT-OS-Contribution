#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
  int pid = getpid();
  printf("I/O-bound process started. PID = %d\n", pid);
  int start = uptime();
  printf("CPUBEGIN ticks = %d\n", start);
  // Simulate an I/O-bound workload — frequent sleep
  for (int i = 0; i < 5; i++) {
    printf("I/O-bound iteration %d\n", i);
    sleep(10);   // sleep for 10 ticks (~100 ms)
  }
  int end = uptime();
  printf("CPUEND ticks = %d\n", end);
  printf("I/O-bound process (PID = %d) completed\n", pid);
  printf("Total elapsed ticks = %d\n", end - start);
  exit(0);
}
