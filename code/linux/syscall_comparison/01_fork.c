#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

struct timespec startTime;
struct timespec stopTime;

int main() {
	int startOut = clock_gettime(CLOCK_MONOTONIC, &startTime);
	pid_t pid = fork();
	int stopOut = clock_gettime(CLOCK_MONOTONIC, &stopTime);

	if (pid == -1) {
		printf("Failed to create process\n");
		exit(1);
	}

	if (pid == 0) {
		exit(0);
	}

	wait(NULL);

	if (startOut == -1 || startOut == -1) {
		printf("Timing error\n");
		exit(1);
	}

	long interval = (stopTime.tv_nsec - startTime.tv_nsec) / 1000 +
					(stopTime.tv_sec - startTime.tv_sec) * 1000000;

	printf("System call time: %ld us\n", interval);
	exit(0);
}
