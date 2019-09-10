#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "bodies.h"
#include "image.h"

#define DT 0.01
#define PI 3.141592

int main(int argc, char** argv) {
	srand(time(NULL));

	int N = 100;
	Body bodies[N];

	//bodies[0] = newBody(-30, 0, 0, 0, 3, 0, 1);
	//bodies[1] = newBody(30, 0, 0, 0, -3, 0, 1);
	//bodies[2] = newBody(0, -30, 0, -3, 0, 0, 1);
	//bodies[3] = newBody(0, 30, 0, 3, 0, 0, 1);
	//bodies[4] = newBody(0, 0, 0, 0, 0, 0, 100);
	double theta, r;
	bodies[0] = newBody(0, 0, 0, 0, 3, 0, N);
	for (int i = 1; i < N; i++) {
		theta = rand() % 360;
		r = rand() % 100;
		bodies[i] = newBody(r*cos(theta), r*sin(theta), 0, -0.1*sin(theta), 0.1*cos(theta), 0, 10);
	}
	
	int width = 200;
	int height = 200;
	int cx = width/2;
	int cy = height/2;

	char filename[15];
	double* f = calloc(3, sizeof(double));
	for (int i = 0; i < 500; i++) {
		Image img = newImage(width, height);

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
		Body *b, *c;
		for (int i = 0; i < N; i++) {
			b = &bodies[i];
			for (int j = i+1; j < N; j++) {
				c = &bodies[j];
				computeForce(*b, *c, f);
				b->dx += DT * f[0]/b->mass;
				b->dy += DT * f[1]/b->mass;
				b->dz += DT * f[2]/b->mass;
				c->dx -= DT * f[0]/c->mass;
				c->dy -= DT * f[1]/c->mass;
				c->dz -= DT * f[2]/c->mass;
				b->x +=  DT * b->dx;
				b->y +=  DT * b->dy;
				b->z +=  DT * b->dz;
				c->x +=  DT * c->dx;
				c->y +=  DT * c->dy;
				c->z +=  DT * c->dz;
			}
		}
	}
}
