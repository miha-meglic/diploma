#define _GNU_SOURCE

#include <fcntl.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

struct ThreadArgs {
	int n;
	int* result;
};

static int ThreadFunction(void* arg);
int fib(int n);

const int EDITOR_PROC_COUNT = 2;
const int THREAD_COUNT = 10;
const int FIB_N = 40;

const int STACK_SIZE = 8192;

struct timespec startTime;
struct timespec stopTime;

int main() {
	int startOut = clock_gettime(CLOCK_MONOTONIC, &startTime);

	char* stacks[THREAD_COUNT];
	for (int i = 0; i < THREAD_COUNT; i++) {
		// Allocate stacks for child task.
		stacks[i] = malloc(STACK_SIZE);
		if (!stacks[i]) {
			printf("Failed to allocate stack\n");
			exit(1);
		}
	}

	for (int i = 0; i < 100; i++) {
		pid_t pids[EDITOR_PROC_COUNT];

		// Create gnome-text-editor processes
		for (int i = 0; i < EDITOR_PROC_COUNT; i++) {
			pids[i] = fork();

			if (pids[i] == -1) {
				printf("Failed to create process\n");
				exit(1);
			} else if (pids[i] == 0) {
				// Redirect stdout and stderr to /dev/null
				int null = open("/dev/null", O_WRONLY);
				dup2(null, 1);
				dup2(null, 2);
				close(null);

				// Start gnome-text-editor
				char* argv[] = {"/usr/bin/gnome-text-editor", NULL};
				extern char** environ;
				execve(argv[0], argv, environ);
				exit(1);
			}

			// Print process ID
			printf("Text Editor #%d PID: %d\n", i, pids[i]);
		}

		// Create threads
		pid_t tids[THREAD_COUNT];
		struct ThreadArgs args[THREAD_COUNT];
		int results[THREAD_COUNT];

		for (int i = 0; i < THREAD_COUNT; i++) {
			args[i].n = FIB_N;
			args[i].result = &results[i];

			tids[i] = clone(
				ThreadFunction, stacks[i] + STACK_SIZE,
				CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SYSVSEM | SIGCHLD,
				&args[i]);

			if (tids[i] == -1) {
				printf("Failed to create thread\n");
				exit(1);
			} else {
				// Print thread ID
				printf("Thread #%d TID: %d\n", i, tids[i]);
			}
		}

		// Wait for all threads to finish
		for (int i = 0; i < THREAD_COUNT; i++) {
			waitpid(tids[i], NULL, 0);
			printf("Thread #%d result: %d\n", i, results[i]);
		}

		// Terminate gnome-text-editor processes
		for (int i = 0; i < EDITOR_PROC_COUNT; i++) {
			kill(pids[i], SIGKILL);
			waitpid(pids[i], NULL, 0);
		}
	}

	// Free stacks
	for (int i = 0; i < THREAD_COUNT; i++) {
		free(stacks[i]);
	}

	int stopOut = clock_gettime(CLOCK_MONOTONIC, &stopTime);

	if (startOut == -1 || startOut == -1) {
		printf("Timing error\n");
		exit(1);
	}

	long interval = (stopTime.tv_nsec - startTime.tv_nsec) / 1000 +
					(stopTime.tv_sec - startTime.tv_sec) * 1000000;

	printf("Process time: %ld us\n", interval);

	exit(0);
}

static int ThreadFunction(void* arg) {
	struct ThreadArgs* args = (struct ThreadArgs*)arg;

	*args->result = fib(args->n);

	_exit(0);
}

int fib(int n) {
	if (n <= 1) {
		return n;
	}
	return fib(n - 1) + fib(n - 2);
}
