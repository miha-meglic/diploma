#include <Windows.h>
#include <profileapi.h>

#include <iostream>

LARGE_INTEGER startTime;
LARGE_INTEGER stopTime;
LARGE_INTEGER frequency;

int wmain(int argc, wchar_t *argv[]) {
	QueryPerformanceFrequency(&frequency);
	// Zajem trenutnega casa pred zacetkom funkcije
	BOOL startOut = QueryPerformanceCounter(&startTime);

	// -- Tu vstavimo funkcijo, ki jo zelimo meriti -- //

	// Zajem trenutnega casa po koncu funkcije
	BOOL stopOut = QueryPerformanceCounter(&stopTime);

	// -- Tu pocistimo zacasne vire -- //

	// Preverimo, ce je prislo do napake pri merjenju casa
	if (startOut == 0 || stopOut == 0) {
		std::cout << "Timing error" << std::endl;
		ExitProcess(1);
	}

	// Izracunamo cas, ki je pretekel med zacetkom in koncem funkcije
	LARGE_INTEGER interval;
	interval.QuadPart = stopTime.QuadPart - startTime.QuadPart;
	interval.QuadPart *= 1000000;
	interval.QuadPart /= frequency.QuadPart;

	// Izpisemo rezultat
	std::cout << "System call time: " << interval.QuadPart << " us"
			  << std::endl;
	ExitProcess(1);
}