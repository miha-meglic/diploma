#define _GNU_SOURCE

#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static int ThreadFunction(void* arg);

struct timespec startTime;
struct timespec stopTime;

void handler(int signo, siginfo_t* info, void* context) {
	if (signo == SIGUSR1 && getpid() != gettid()) {
		exit(0);
	}
}

int main() {
	struct sigaction act = {0};
	act.sa_sigaction = &handler;
	if (sigaction(SIGUSR1, &act, NULL) == -1) {
		printf("Failed to set SIGUSR1 handler\n");
		exit(1);
	}

	// Allocate stack for child task.
	const int STACK_SIZE = 65536;
	char* stack = malloc(STACK_SIZE);
	if (!stack) {
		perror("malloc");
		exit(1);
	}

	int startOut = clock_gettime(CLOCK_MONOTONIC, &startTime);
	int tid = clone(ThreadFunction, stack + STACK_SIZE,
					CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SYSVSEM |
						CLONE_SIGHAND | CLONE_THREAD,
					NULL);
	int stopOut = clock_gettime(CLOCK_MONOTONIC, &stopTime);

	if (tid == -1) {
		printf("Failed to create thread\n");
		exit(1);
	}

	kill(getpid(), SIGUSR1);

	if (startOut == -1 || startOut == -1) {
		printf("Timing error\n");
		exit(1);
	}

	long interval = (stopTime.tv_nsec - startTime.tv_nsec) / 1000 +
					(stopTime.tv_sec - startTime.tv_sec) * 1000000;

	printf("System call time: %ld us\n", interval);
	exit(0);
}

static int ThreadFunction(void* arg) {
	nanosleep((const struct timespec[]){{5, 0}}, NULL);
	return 0;
}