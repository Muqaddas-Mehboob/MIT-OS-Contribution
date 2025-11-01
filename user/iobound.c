// #include "kernel/types.h"
// #include "kernel/stat.h"
// #include "user/user.h"
// #include "kernel/fcntl.h"

// #define FILENAME "io_test.txt"
// #define ITERATIONS 100

// int main() {
//   int pid = getpid();
//   struct procinfo info;
//   getprocinfo(pid, &info);
//   printf("CPU time: %d | Created: %d | Total ticks: %d | Times scheduled: %d\n",
//          info.cputime, info.creation_time, info.total_cpu_ticks, info.times_scheduled);
//   printf("I/O-bound process started. PID = %d\n", pid);
//   int start = uptime();

//   int fd = open(FILENAME, O_CREATE | O_WRONLY);
//   if (fd < 0) {
//     printf("iobound: failed to open file\n");
//     exit(1);
//   }

//   char buf[32] = "This is a small I/O write test\n";
  
//   for (int i = 0; i < ITERATIONS; i++) {
//     printf("\nIO Operation iteration # %d\n", i);
//     // Perform a small write each time (I/O operation)
//     if (write(fd, buf, strlen(buf)) != strlen(buf)) {
//       printf("iobound: write failed at iteration %d\n", i);
//       close(fd);
//       exit(1);
//     }

//     // Simulate short delay to mimic I/O latency
//     sleep(1);
//   }
//   close(fd);

//   int end = uptime();
//   printf("I/O-bound process (PID = %d) completed\n", pid);
//   printf("Total elapsed ticks of IO bound = %d\n", end - start);
//   getprocinfo(pid, &info);
//   printf("(IO PERFORMANCE METRICS):CPU time: %d | Created: %d | Total ticks: %d | Times scheduled: %d\n",
//          info.cputime, info.creation_time, info.total_cpu_ticks, info.times_scheduled);
//   exit(0);
// }

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#define FILENAME "io_test.txt"
#define ITERATIONS 100

int main() {
    int pid = getpid();
    struct procinfo info;

    printf("I/O-bound process started. PID = %d\n", pid);

    // Initial process info
    getprocinfo(pid, &info);
    printf("(IO PERFORMANCE METRICS): CPU time: %d | Created: %d | Total ticks: %d | Times scheduled: %d\n",
           info.total_cpu_ticks, info.creation_time, info.total_cpu_ticks, info.times_scheduled);

    int start = uptime();

    // Open file
    int fd = open(FILENAME, O_CREATE | O_WRONLY);
    if (fd < 0) {
        printf("iobound: failed to open file\n");
        exit(1);
    }

    char buf[32] = "I/O write test\n";

    for (int i = 0; i < ITERATIONS; i++) {
        // Write to file
        write(fd, buf, strlen(buf));

        // Print progress every 10 iterations
        if (i % 10 == 0) {
            printf("I/O-bound: completed %d/%d writes\n", i, ITERATIONS);
        }

        // Small busy wait to simulate I/O latency
        for (int j = 0; j < 1000; j++);
    }

    close(fd);
    int end = uptime();

    // Final process info
    getprocinfo(pid, &info);
    printf("I/O-bound process (PID = %d) completed\n", pid);
    printf("Total elapsed ticks = %d\n", end - start);
    printf("(IO PERFORMANCE METRICS): CPU time: %d | Created: %d | Total ticks: %d | Times scheduled: %d\n",
           info.total_cpu_ticks, info.creation_time, info.total_cpu_ticks, info.times_scheduled);

    // Cleanup
    unlink(FILENAME);
    exit(0);
}

