#include "bodies.h"
#include <stdlib.h>
#define G 1

double bodyDistance(Body a, Body b) {
   return sqrt(pow(b.x - a.x,2) + pow(b.y - a.y,2) + pow(b.z - a.z,2));
}

void computeForce(Body a, Body b, double fvec[3]) {
	float dist = bodyDistance(a,b);
	int f = G * a.mass * b.mass / dist;
	fvec[0] = (b.x - a.x)/dist * f;
	fvec[1] = (b.y - a.y)/dist * f;
	fvec[2] = (b.z - a.z)/dist * f;
}

Body newBody(double x, double y, double z, double dx, double dy, double dz, double mass) {
	Body b;
	b.x = x;
	b.y = y;
	b.z = z;
	b.dx = dx;
	b.dy = dy;
	b.dz = dz;
	b.mass = mass;
	return b;
}
