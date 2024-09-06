#include <Windows.h>
#include <profileapi.h>

#include <iostream>

struct ThreadArgs {
	int n;
	int *result;
};

DWORD WINAPI ThreadFunction(LPVOID lpParam);
int fib(int n);

const int NOTEPAD_PROC_COUNT = 2;
const int THREAD_COUNT = 10;
const int FIB_N = 40;

LARGE_INTEGER startTime;
LARGE_INTEGER stopTime;
LARGE_INTEGER frequency;

int wmain(int argc, wchar_t *argv[]) {
	QueryPerformanceFrequency(&frequency);
	BOOL startOut = QueryPerformanceCounter(&startTime);

	for (int i = 0; i < 100; i++) {
		STARTUPINFOW si[NOTEPAD_PROC_COUNT];
		PROCESS_INFORMATION pi[NOTEPAD_PROC_COUNT];

		// Create notepad processes
		for (int i = 0; i < NOTEPAD_PROC_COUNT; i++) {
			ZeroMemory(&si[i], sizeof(si[i]));
			si[i].cb = sizeof(si[i]);
			ZeroMemory(&pi[i], sizeof(pi[i]));

			if (!CreateProcessW(L"C:\\Windows\\system32\\notepad.exe", NULL,
								NULL, NULL, FALSE, 0, NULL, NULL,
								(LPSTARTUPINFOW)&si[i],
								(LPPROCESS_INFORMATION)&pi[i])) {
				std::cout << "Failed to create process" << std::endl;
				ExitProcess(1);
			}

			// Print process ID
			std::cout << "Notepad #" << i << " PID: " << pi[i].dwProcessId
					  << std::endl;
		}

		// Create threads
		HANDLE threads[THREAD_COUNT];
		ThreadArgs args[THREAD_COUNT];
		int results[THREAD_COUNT];

		for (int i = 0; i < THREAD_COUNT; i++) {
			args[i].n = FIB_N;
			args[i].result = &results[i];
			DWORD threadId;
			threads[i] =
				CreateThread(NULL, 0, ThreadFunction, &args[i], 0, &threadId);

			if (threads[i] == NULL) {
				printf("Failed to create thread\n");
				ExitProcess(1);
			} else {
				// Print thread ID
				std::cout << "Thread #" << i << " TID: " << threadId
						  << std::endl;
			}
		}

		// Wait for all threads to finish
		WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, INFINITE);

		// Close thread handles
		for (int i = 0; i < THREAD_COUNT; i++) {
			CloseHandle(threads[i]);
			std::cout << "Thread #" << i << " result: " << results[i]
					  << std::endl;
		}

		// Terminate notepad processes and close process handles
		for (int i = 0; i < NOTEPAD_PROC_COUNT; i++) {
			TerminateProcess(pi[i].hProcess, 0);

			CloseHandle(pi[i].hProcess);
			CloseHandle(pi[i].hThread);
		}
	}

	BOOL stopOut = QueryPerformanceCounter(&stopTime);

	if (startOut == 0 || stopOut == 0) {
		std::cout << "Timing error" << std::endl;
		ExitProcess(1);
	}

	LARGE_INTEGER interval;
	interval.QuadPart = stopTime.QuadPart - startTime.QuadPart;
	interval.QuadPart *= 1000000;
	interval.QuadPart /= frequency.QuadPart;

	std::cout << "Process time: " << interval.QuadPart << " us" << std::endl;

	ExitProcess(0);
}

DWORD WINAPI ThreadFunction(LPVOID lpParam) {
	ThreadArgs *args = (ThreadArgs *)lpParam;

	*args->result = fib(args->n);

	ExitThread(0);
}

int fib(int n) {
	if (n <= 1) {
		return n;
	}
	return fib(n - 1) + fib(n - 2);
}
