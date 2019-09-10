#include <stdio.h>
#include <stdlib.h>
#include "bodies.h"
#include "image.h"

#define DT 0.1

int main(int argc, char** argv) {
	Body a = newBody(-30, 0, 0, 0, 5, 0, 1);
	Body b = newBody(10, 0, 0, 0, 0, 0, 100);
	
	int width = 200;
	int height = 200;
	int cx = width/2;
	int cy = height/2;

	char filename[15];
	double* f = calloc(3, sizeof(double));
	for (int i = 0; i < 500; i++) {
		Image img = newImage(width, height);

		if ( (int)(a.x+cx) >= 0 && (int)(a.x+cx) < width && (int)(a.y+cy) >= 0 && (int)(a.y+cy) < height) {
			img.img[(int)a.y+cy][(int)a.x+cx] = 255;
		}
		if ( (int)(b.x+cx) >= 0 && (int)(b.x+cx) < width && (int)(b.y+cy) >= 0 && (int)(b.y+cy) < height) {
			img.img[(int)b.y+cy][(int)b.x+cx] = 255;
		}

		sprintf(filename, "image%04d.pgm", i+1);
		saveImage(img, filename);
		freeImage(img);

		// Update locations
		computeForce(a, b, f);
		a.dx += DT * f[0]/a.mass;
		a.dy += DT * f[1]/a.mass;
		a.dz += DT * f[2]/a.mass;
		b.dx -= DT * f[0]/b.mass;
		b.dy -= DT * f[1]/b.mass;
		b.dz -= DT * f[2]/b.mass;
		a.x +=  DT * a.dx;
		a.y +=  DT * a.dy;
		a.z +=  DT * a.dz;
		b.x +=  DT * b.dx;
		b.y +=  DT * b.dy;
		b.z +=  DT * b.dz;
	}
}
