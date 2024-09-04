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
	cmd += L" child";  // otroku dodamo argument, da ne izvedemo neskoncne zanke

	BOOL created =
		CreateProcessW(NULL, (LPWSTR)cmd.c_str(), NULL, NULL, FALSE, 0, NULL,
					   NULL, (LPSTARTUPINFOW)&si, (LPPROCESS_INFORMATION)&pi);

	if (!created) {
		std::cout << "Failed to create process" << std::endl;
		ExitProcess(1);
	}

	BOOL startOut = QueryPerformanceCounter(&startTime);
	TerminateProcess(pi.hProcess, 0);
	BOOL stopOut = QueryPerformanceCounter(&stopTime);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

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