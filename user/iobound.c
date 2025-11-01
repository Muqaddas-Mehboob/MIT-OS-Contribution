#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#define FILENAME "io_test.txt"
#define ITERATIONS 100

int main() {
  int pid = getpid();
  struct procinfo info;
  getprocinfo(pid, &info);
  printf("CPU time: %d | Created: %d | Total ticks: %d | Times scheduled: %d\n",
         info.cputime, info.creation_time, info.total_cpu_ticks, info.times_scheduled);
  printf("I/O-bound process started. PID = %d\n", pid);
  int start = uptime();

  int fd = open(FILENAME, O_CREATE | O_WRONLY);
  if (fd < 0) {
    printf("iobound: failed to open file\n");
    exit(1);
  }

  char buf[32] = "This is a small I/O write test\n";
  
  for (int i = 0; i < ITERATIONS; i++) {
    printf("\nIO Operation iteration # %d\n", i);
    // Perform a small write each time (I/O operation)
    if (write(fd, buf, strlen(buf)) != strlen(buf)) {
      printf("iobound: write failed at iteration %d\n", i);
      close(fd);
      exit(1);
    }

    // Simulate short delay to mimic I/O latency
    sleep(1);
  }
  close(fd);

  int end = uptime();
  printf("I/O-bound process (PID = %d) completed\n", pid);
  printf("Total elapsed ticks of IO bound = %d\n", end - start);
  getprocinfo(pid, &info);
  printf("(IO PERFORMANCE METRICS):CPU time: %d | Created: %d | Total ticks: %d | Times scheduled: %d\n",
         info.cputime, info.creation_time, info.total_cpu_ticks, info.times_scheduled);
  exit(0);
}

