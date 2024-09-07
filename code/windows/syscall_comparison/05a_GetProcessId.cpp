#include <Windows.h>
#include <profileapi.h>

#include <iostream>

LARGE_INTEGER startTime;
LARGE_INTEGER stopTime;
LARGE_INTEGER frequency;

int wmain(int argc, wchar_t *argv[]) {
	if (argc > 1) {
		// Child process
		Sleep(5000);
		ExitProcess(0);
	}

	QueryPerformanceFrequency(&frequency);

	STARTUPINFOW si = {sizeof(si)};
	PROCESS_INFORMATION pi = {};

	std::wstring cmd = argv[0];
	cmd += L" child";

	if (!CreateProcessW(NULL, (LPWSTR)cmd.c_str(), NULL, NULL, FALSE, 0, NULL,
						NULL, (LPSTARTUPINFOW)&si,
						(LPPROCESS_INFORMATION)&pi)) {
		std::cout << "Failed to create process" << std::endl;
		ExitProcess(1);
	}

	BOOL startOut = QueryPerformanceCounter(&startTime);
	DWORD pid = GetProcessId(pi.hProcess);
	BOOL stopOut = QueryPerformanceCounter(&stopTime);

	// std::cout << "PID: " << pid << std::endl;

	TerminateProcess(pi.hProcess, 0);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

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