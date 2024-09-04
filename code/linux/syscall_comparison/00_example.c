#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct timespec startTime;
struct timespec stopTime;

int main() {
	// Zajem trenutnega casa pred zacetkom funkcije
	int startOut = clock_gettime(CLOCK_MONOTONIC, &startTime);

	// -- Tu vstavimo funkcijo, ki jo zelimo meriti -- //

	// Zajem trenutnega casa po koncu funkcije
	int stopOut = clock_gettime(CLOCK_MONOTONIC, &stopTime);

	// -- Tu pocistimo zacasne vire -- //

	// Preverimo, ce je prislo do napake pri merjenju casa
	if (startOut == -1 || stopOut == -1) {
		printf("Timing error\n");
		exit(1);
	}

	// Izracunamo cas, ki je pretekel med zacetkom in koncem funkcije
	long interval = (stopTime.tv_nsec - startTime.tv_nsec) / 1000 +
					(stopTime.tv_sec - startTime.tv_sec) * 1000000;

	// Izpisemo rezultat
	printf("System call time: %ld us\n", interval);
	exit(0);
}
