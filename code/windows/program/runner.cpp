#include <Windows.h>

#include <iostream>

DWORD WINAPI ThreadFunction(LPVOID lpParam);
int fib(int n);

int wmain(int argc, wchar_t *argv[]) {
	STARTUPINFOW si = {sizeof(si)};
	PROCESS_INFORMATION pi = {};

	// Create process
	if (!CreateProcessW(L".\\task_manager.exe", NULL, NULL, NULL, FALSE, 0,
						NULL, NULL, (LPSTARTUPINFOW)&si,
						(LPPROCESS_INFORMATION)&pi)) {
		printf("Failed to create process\n");
		ExitProcess(1);
	}

	// Wait for process to finish
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Get kernel and user time
	FILETIME creationTime, exitTime, kernelTime, userTime;
	GetProcessTimes(pi.hProcess, &creationTime, &exitTime, &kernelTime,
					&userTime);
	SYSTEMTIME kernelSysTime, userSysTime;
	FileTimeToSystemTime(&kernelTime, &kernelSysTime);
	FileTimeToSystemTime(&userTime, &userSysTime);
	printf("Kernel time: %02d.%03d s\n", kernelSysTime.wSecond,
		   kernelSysTime.wMilliseconds);
	printf("User time: %02d.%03d s\n", userSysTime.wSecond,
		   userSysTime.wMilliseconds);
	// printf("Kernel time: %d us\n", kernelTime.dwLowDateTime / 10);
	// printf("User time: %d s\n", userTime.dwLowDateTime / 10);

	// Close process handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	ExitProcess(0);
}
