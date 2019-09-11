#include <math.h>

typedef struct Body {
	double x;
	double y;
	double z;
	double dx;
	double dy;
	double dz;
	double mass;
} Body;


double bodyDistance(Body a, Body b);
void computeForce(Body a, Body b, double fvec[3]);

Body newBody(double x, double y, double z, double dx, double dy, double dz, double mass);

void printBody(Body b);
