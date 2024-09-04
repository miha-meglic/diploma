#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

struct timespec startTime;
struct timespec stopTime;

int main() {
	pid_t pid = fork();

	if (pid == -1) {
		printf("Failed to create process\n");
		exit(1);
	}

	if (pid == 0) {
		nanosleep((const struct timespec[]){{5, 0}}, NULL);
		exit(0);
	}

	int startOut = clock_gettime(CLOCK_MONOTONIC, &startTime);
	kill(pid, SIGKILL);
	int stopOut = clock_gettime(CLOCK_MONOTONIC, &stopTime);

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
