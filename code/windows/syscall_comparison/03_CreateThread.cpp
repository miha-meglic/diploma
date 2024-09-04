#include <Windows.h>
#include <profileapi.h>

#include <iostream>

DWORD WINAPI ThreadFunction(LPVOID lpParam);

LARGE_INTEGER startTime;
LARGE_INTEGER stopTime;
LARGE_INTEGER frequency;

int wmain(int argc, wchar_t *argv[]) {
	QueryPerformanceFrequency(&frequency);

	BOOL startOut = QueryPerformanceCounter(&startTime);
	HANDLE hThread = CreateThread(NULL, 0, ThreadFunction, NULL, 0, NULL);
	BOOL stopOut = QueryPerformanceCounter(&stopTime);

	if (hThread == NULL) {
		std::cout << "Failed to create thread" << std::endl;
		ExitProcess(1);
	}

	TerminateThread(hThread, 0);
	CloseHandle(hThread);

	if (startOut == 0 || stopOut == 0) {
		std::cout << "Timing error" << std::endl;
		ExitProcess(1);
	}

	LARGE_INTEGER interval;
	interval.QuadPart = stopTime.QuadPart - startTime.QuadPart;
	interval.QuadPart *= 1000000;
	interval.QuadPart /= frequency.QuadPart;

	std::cout << "System call time: " << interval.QuadPart << " us"
			  << std::endl;
	ExitProcess(0);
}

DWORD WINAPI ThreadFunction(LPVOID lpParam) {
	Sleep(5000);
	return 0;
}
