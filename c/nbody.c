#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "bodies.h"
#include "image.h"

#define DT 0.0005
#define PI 3.141592

int main(int argc, char** argv) {
	srand(time(NULL));

	int N = 4000;
	Body bodies[N];

	//bodies[0] = newBody(-30, 0, 0, 0, 3, 0, 1);
	//bodies[1] = newBody(30, 0, 0, 0, -3, 0, 1);
	//bodies[2] = newBody(0, -30, 0, -3, 0, 0, 1);
	//bodies[3] = newBody(0, 30, 0, 3, 0, 0, 1);
	//bodies[4] = newBody(0, 0, 0, 0, 0, 0, 100);
	double theta, r, rx, ry, gapSize = 35;
	bodies[0] = newBody(0, 10, 0, -2, 0, 0, 100*N);
	bodies[1] = newBody(0, -10, 0, 2, 0, 0, 100*N);
	for (int i = 2; i < N; i++) {
		theta = PI * (rand() % 360) / 180;
		r = (rand() % 250);
		rx = gapSize + r * 1.0;
		ry = gapSize + r * 1.0;
		bodies[i] = newBody(rx*cos(theta)*0.3, 1+ry*sin(theta), 0, -2*pow(80/rx,0.5)*sin(theta), 2*pow(80/ry,0.5)*cos(theta), 0, 10);
	}
	
	int width = 400;
	int height = 400;
	int cx = width/2;
	int cy = height/2;

	char filename[15];
	double* f = calloc(3, sizeof(double));
	int nframes = 1000;

	int percent = nframes/100;
	for (int i = 0; i < nframes; i++) {
		if (i % percent == 0) {
			printf("%d%%\n", i/percent);
		}

		Image img = newImage(width, height);

		//cx = width/2 - (int)bodies[0].x;
		//cy = height/2 - (int)bodies[0].y;

		Body a;
		for (int i = 0; i < N; i++) {
			a = bodies[i];
			if ( (int)(a.x+cx) >= 0 && (int)(a.x+cx) < width && (int)(a.y+cy) >= 0 && (int)(a.y+cy) < height) {
				img.img[(int)a.y+cy][(int)a.x+cx] = 255;
			}
		}

		sprintf(filename, "image%04d.pgm", i+1);
		saveImage(img, filename);
		freeImage(img);

		// Update locations
		for (int i = 0; i < N; i++) {
			Body *b, *c;
			b = &bodies[i];
			for (int j = i+1; j < N; j++) {
				c = &bodies[j];
				computeForce(*b, *c, f);
				b->dx += DT * f[0]/(b->mass);
				b->dy += DT * f[1]/(b->mass);
				b->dz += DT * f[2]/(b->mass);
				c->dx -= DT * f[0]/(c->mass);
				c->dy -= DT * f[1]/(c->mass);
				c->dz -= DT * f[2]/(c->mass);
			}
		}
		
		// #pragma omp parallel for
		for (int i = 0; i < N; i++) {
			Body* b = &bodies[i];
			b->x += b->dx;
			b->y += b->dy;
			b->z += b->dz;
		}
	}
}
