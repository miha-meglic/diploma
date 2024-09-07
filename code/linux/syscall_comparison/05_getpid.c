#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

struct timespec startTime;
struct timespec stopTime;

int main() {
	int startOut = clock_gettime(CLOCK_MONOTONIC, &startTime);
	pid_t pid = getpid();
	int stopOut = clock_gettime(CLOCK_MONOTONIC, &stopTime);

	// printf("PID: %d\n", pid);

	if (startOut == -1 || stopOut == -1) {
		printf("Timing error\n");
		exit(1);
	}

	long interval = (stopTime.tv_nsec - startTime.tv_nsec) +
					(stopTime.tv_sec - startTime.tv_sec) * 1000000000;

	printf("System call time: %f us\n", interval * 0.001);
	exit(0);
}
