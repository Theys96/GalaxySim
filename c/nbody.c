#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "bodies.h"
#include "image.h"

#define DT 0.005
#define PI 3.141592
#define E 2.

#define ANGLES 24
#define RADII 30

#define ELLIPSES 500
#define ENUM 2
#define EANGLE 0.8
#define EWIDTH 4
#define BODIES (ELLIPSES * ENUM + 1)
#define SCALE 12
#define DIMENSIONS 800
#define FRAMES 500

void printTimestamp() {
	time_t ltime = time(NULL);
	printf("%s\n",asctime(localtime(&ltime)));
}

int main(int argc, char** argv) {
	srand(time(NULL));

	int N = BODIES;
	Body bodies[N];

	//bodies[0] = newBody(-30, 0, 0, 0, 3, 0, 1);
	//bodies[1] = newBody(30, 0, 0, 0, -3, 0, 1);
	//bodies[2] = newBody(0, -30, 0, -3, 0, 0, 1);
	//bodies[3] = newBody(0, 30, 0, 3, 0, 0, 1);
	//bodies[4] = newBody(0, 0, 0, 0, 0, 0, 100);
	//bodies[0] = newBody(0, 0, 0, 0, 0, 0, 100000);
	//bodies[1] = newBody(0, -100, 0, sqrt(100200/100), 0, 0, 200);

	/*
	bodies[0] = newBody(0, 0, 0, 0, 0, 0, 100000);
	//bodies[N-1] = newBody(0, -250, 0, sqrt(100100/250), 0, 0, 1000);
	double theta, r;
	for (int i = 1; i <= RADII; i++) {
		r = 20 + i * 30;
		for (int a = 0; a < ANGLES; a++) {
			theta = PI * (a*(360/ANGLES)) / 180;
			bodies[a*RADII+i] = newBody(r*cos(theta), r*sin(theta), 0, -sqrt(100010/r)*sin(theta), sqrt(100010/r)*cos(theta), 0, 10);
		}
	}
	*/

	bodies[N-1] = newBody(0, 0, 0, 0, 0, 0, 100000000);
	/*
	for (int i = 1; i < N; i++) {
		theta = PI * (rand() % 360) / 180;
		r = rand() % (200 - (int)gapSize);
		rx = gapSize + r * 1.0;
		ry = gapSize + r * 1.0;
		mass = 10; //2+(rand() % 4)*2;
		// 2*pow(100/rx,0.5)
		bodies[i] = newBody(rx*cos(theta), ry*sin(theta), 0, -(sqrt(100000/rx))*sin(theta), (sqrt(100000/rx))*cos(theta), 0, mass);
	}*/


	double theta, rot, r, vr, rx, ry, vx, vy, gapSize = 200, localwidth, mass = 1;
	for (int e = 0; e < ELLIPSES; e++) {
		localwidth = EWIDTH*(exp(1+2*(float)e/ELLIPSES)/(exp(3)-exp(1))); //* exp(1+2*(double)e/ELLIPSES);
		rot = EANGLE*e * PI/180;
		for (int i = 0; i < ENUM; i++) {
			theta = PI * (rand() % 360) / 180;
			r = (double)(rand() % (int)(localwidth*1000))/1000;
			vr = r;
			rx = (gapSize + r) * cos(theta) * 1;
			ry = (gapSize + r) * sin(theta) * .9;
			r = sqrt(rx*rx + ry*ry);
			theta = atan2(rx,ry);
			theta -= rot;
			rx = r*cos(theta);
			ry = r*sin(theta);
			vx = -sqrt(100000000/r)*sin(theta);
			vy = sqrt(100000000/r)*cos(theta);
			bodies[e*ENUM + i] = newBody(rx, ry, 0, vx, vy, 0, mass);
		}
		gapSize += localwidth;
	}

	/*
	double theta, r, rx, ry, gapSize = 5, mass;
	for (int i = 0; i < 500; i++) {
		theta = PI * (rand() % 360) / 180;
		r = rand() % (100 - (int)gapSize);
		rx = gapSize + r * 1.0;
		ry = gapSize + r * 1.0;
		mass = 1000; //2+(rand() % 4)*2;
		// 2*pow(100/rx,0.5)
		bodies[i] = newBody(rx*cos(theta), 1+ry*sin(theta), 0, -(sqrt((500*mass)/(4*rx)))*sin(theta), (sqrt((500*mass)/(4*ry)))*cos(theta), 0, mass);
	}

	gapSize = 150;
	for (int i = 500; i < N; i++) {
		theta = PI * (rand() % 360) / 180;
		r = rand() % (400 - (int)gapSize);
		rx = gapSize + r * 1.0;
		ry = gapSize + r * 1.0;
		mass = 1; //2+(rand() % 4)*2;
		// 2*pow(100/rx,0.5)
		bodies[i] = newBody(rx*cos(theta), 1+ry*sin(theta), 0, -(sqrt((500*1000+mass)/(rx)))*sin(theta), (sqrt((500*1000+mass)/(ry)))*cos(theta), 0, mass);
	}
	*/
	
	int width = DIMENSIONS;
	int height = DIMENSIONS;
	int cx = width/2;
	int cy = height/2;

	char filename[15];
	double* f = calloc(3, sizeof(double));
	int nframes = FRAMES;

	printf("\nGalaxySim n-body simulation vTHIJS-0.0\n");
	printTimestamp();

	printf("Specifications:\n");
	printf("\tn = %d\n", BODIES);
	printf("\timage dimensions = %dx%d\n", DIMENSIONS, DIMENSIONS);
	printf("\tframes = %d\n", nframes);
	printf("\n");
	clock_t t0, t1;
	double timeRendering = 0, timeComputing = 0;

	int percent = nframes/100;

	for (int frame = 0; frame < nframes; frame++) {
		if (frame % percent == 0) {
			// printf("%d%%\n", frame/percent);
		}


		//cx = width/2 - (int)bodies[0].x;
		//cy = height/2 - (int)bodies[0].y;

		t0 = clock();
		if (1) {
			Body a;
			Image img = newImage(width, height);
			int rx, ry;
			for (int i = 0; i < N; i++) {
				a = bodies[i];
				rx = (int)((a.x/SCALE+cx));
				ry = (int)((a.y/SCALE+cy));
				if ( rx >= 0 && rx < width && ry >= 0 && ry < height) {
					img.img[ry][rx] = a.mass > 100 ? 0 : 255;
				}
			}

			sprintf(filename, "image%04d.pgm", frame+1);
			saveImage(img, filename);
			freeImage(img);
		}
		t1 = clock();
		timeRendering += (double)(t1 - t0) / CLOCKS_PER_SEC;


		t0 = clock();
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
		t1 = clock();
		timeComputing += (double)(t1 - t0) / CLOCKS_PER_SEC;
	}

	printf("\nDone.\n");
	printf("Time used rendering images and saving them to file:\n");
	printf("\t%.3fs total for %d frames\n", timeRendering, nframes);
	printf("\t%.3fms on average\n", timeRendering / nframes * 1000 );
	printf("\n");
	printf("Time used updating the universe state:\n");
	printf("\t%.3fs total for %d frames\n", timeComputing, nframes);
	printf("\t%.3fms on average\n", timeComputing / nframes * 1000 );
	printf("\n");

}
