#include <Windows.h>
#include <profileapi.h>

#include <iostream>

LARGE_INTEGER startTime;
LARGE_INTEGER stopTime;
LARGE_INTEGER frequency;

int wmain(int argc, wchar_t *argv[]) {
	QueryPerformanceFrequency(&frequency);
	BOOL startOut = QueryPerformanceCounter(&startTime);
	DWORD pid = GetCurrentProcessId();
	BOOL stopOut = QueryPerformanceCounter(&stopTime);

	// std::cout << "PID: " << pid << std::endl;

	if (startOut == 0 || stopOut == 0) {
		std::cout << "Timing error" << std::endl;
		ExitProcess(1);
	}

	LARGE_INTEGER interval;
	interval.QuadPart = stopTime.QuadPart - startTime.QuadPart;
	interval.QuadPart *= 1000000000;
	interval.QuadPart /= frequency.QuadPart;

	std::cout << "System call time: " << interval.QuadPart * 0.001 << " us"
			  << std::endl;
	ExitProcess(0);
}