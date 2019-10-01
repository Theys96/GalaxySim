#include "nbody.h"
#include <stdio.h>

int main(int argc, char** argv) {
	
	Universe uni = newCircularUniverse(1000, 300, 35);
	
	int size = 800;

	char filename[20];
	for (int i = 0; i < 500; i++) {
		sprintf(filename, "img/image%04d.pgm", i+1);
		renderUniverse(uni, filename, size, size, 0, 0, 1);
		iterateNaive(&uni, 0.02);
	}
}
