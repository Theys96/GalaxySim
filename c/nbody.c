#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "bodies.h"
#include "image.h"

#define DT 0.05
#define PI 3.141592

int main(int argc, char** argv) {
	srand(time(NULL));

	int N = 5000;
	Body bodies[N];

	//bodies[0] = newBody(-30, 0, 0, 0, 3, 0, 1);
	//bodies[1] = newBody(30, 0, 0, 0, -3, 0, 1);
	//bodies[2] = newBody(0, -30, 0, -3, 0, 0, 1);
	//bodies[3] = newBody(0, 30, 0, 3, 0, 0, 1);
	//bodies[4] = newBody(0, 0, 0, 0, 0, 0, 100);
	//bodies[0] = newBody(0, 0, 0, 0, 0, 0, 100000);
	//bodies[1] = newBody(0, -100, 0, sqrt(100200/100), 0, 0, 200);

	bodies[0] = newBody(-10, 0, 0, 0, 0, 50, 100000);
	bodies[1] = newBody(10, 0, 0, 0, 0, -50, 100000);

	double theta, r, rx, ry, gapSize = 50, mass;
	for (int i = 2; i < N; i++) {
		theta = PI * (rand() % 360) / 180;
		r = rand() % (400 - (int)gapSize);
		rx = gapSize + r * 1.0;
		ry = gapSize + r * 1.0;
		mass = 2+(rand() % 4)*2;
		// 2*pow(100/rx,0.5)
		bodies[i] = newBody(rx*cos(theta), 1+ry*sin(theta), 0, -(sqrt(200001/(rx+20)))*sin(theta), (sqrt(200001/(ry+20)))*cos(theta), 0, mass);
	}
	
	int width = 1000;
	int height = 1000;
	int cx = width/2;
	int cy = height/2;

	char filename[15];
	double* f = calloc(3, sizeof(double));
	int nframes = 2000;

	int percent = nframes/100;

	for (int frame = 0; frame < nframes; frame++) {
		if (frame % percent == 0) {
			printf("%d%%\n", frame/percent);
		}


		//cx = width/2 - (int)bodies[0].x;
		//cy = height/2 - (int)bodies[0].y;

		Body a;
		if (frame > nframes/10*9 || frame%1 == 0) {

			


			Image img = newImage(width, height);
			for (int i = 0; i < N; i++) {
				a = bodies[i];
				if ( (int)(a.x+cx) >= 0 && (int)(a.x+cx) < width && (int)(a.y+cy) >= 0 && (int)(a.y+cy) < height) {
					img.img[(int)a.y+cy][(int)a.x+cx] = a.mass > 100 ? 255 : 255;
					
				}
			}

			sprintf(filename, "image%04d.pgm", frame+1);
			saveImage(img, filename);
			freeImage(img);
		}

		// Update velocities
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

		// Update locations
		for (int i = 0; i < N; i++) {
			Body* b = &bodies[i];
			b->x += DT * b->dx;
			b->y += DT * b->dy;
			b->z += DT * b->dz;
		}
	}

}
