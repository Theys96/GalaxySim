#include "nbody.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printTimestamp() {
	time_t ltime = time(NULL);
	printf("%s\n",asctime(localtime(&ltime)));
}

int main(int argc, char** argv) {
	
	int n = 1000;
	int size = 800;
	int nframes = 500;

	Universe uni = newCircularUniverse(1000, 300, 35);

	printf("\nGalaxySim n-body simulation v0.0\n");
	printTimestamp();

	printf("Specifications:\n");
	printf("\tn = %d\n", n);
	printf("\timage dimensions = %dx%d\n", size, size);
	printf("\tframes = %d\n", nframes);
	printf("\n");

	char filename[20];
	clock_t t0, t1;
	double timeRendering = 0, timeComputing = 0;
	for (int i = 0; i < nframes; i++) {
		sprintf(filename, "img/image%04d.pgm", i+1);

		t0 = clock();
		renderUniverse(uni, filename, size, size, 0, 0, 1);
		t1 = clock();
		timeRendering += (double)(t1 - t0) / CLOCKS_PER_SEC;

		t0 = clock();
		iterateNaive(&uni, 0.02);
		t1 = clock();
		timeComputing += (double)(t1 - t0) / CLOCKS_PER_SEC;
	}

	printf("Done.\n");
	printf("Time used rendering images and saving them to file:\n");
	printf("\t%.3fs total for %d frames\n", timeRendering, nframes);
	printf("\t%.3fms on average\n", timeRendering / nframes * 1000 );
	printf("\n");
	printf("Time used updating the universe state:\n");
	printf("\t%.3fs total for %d frames\n", timeComputing, nframes);
	printf("\t%.3fms on average\n", timeComputing / nframes * 1000 );
	printf("\n");
}
