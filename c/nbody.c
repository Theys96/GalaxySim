#include <stdio.h>
#include <stdlib.h>
#include "bodies.h"


int main(int argc, char** argv) {
	Body a = newBody(0, 0, 0, 0, 0, 0, 10);
	Body b = newBody(10, 0, 0, 0, 0, 0, 10);

	double* f = calloc(3, sizeof(double));
	computeForce(a, b, f);
	printf("(%lf,%lf,%lf)\n", f[0], f[1], f[2]);
}
