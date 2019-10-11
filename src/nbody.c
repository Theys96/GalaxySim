/* 
 * Part of the GalaxySim project
 * by M.J. Havinga
 * 
 * Code file for nbody.h
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "nbody.h"
#include "image.h"
#define PI 3.14159265

void renderUniverse(Universe u, char* filename, int cx, int cy, double scale, int width, int height) {
  cx += width/2;
  cy += height/2;

  Image img = newImage(width, height);

  Body a;
  int ax, ay;
  for (int i = 0; i < u.n; i++) {
    a = u.bodies[i];
    ax = (int)((a.x/scale+cx));
    ay = (int)((a.y/scale+cy));
    if ( ax >= 0 && ax < width && ay >= 0 && ay < height) {
      setPixel(img, ax, ay, 255);
    }
  }

  saveImage(img, filename);
  freeImage(img);
}

void universeToCsv(Universe u, char* filename) {
  FILE* file = fopen(filename, "wb");
  fprintf(file, "i,x,y,z,r,theta\n");

  Body a;
  int x, y, z, r, theta;
  for (int i = 0; i < u.n; i++) {
    a = u.bodies[i];
    x = (int)a.x; y = (int)a.y; z = (int)a.z; 
    r = (int)sqrt(x*x + y*y + z*z);
    theta = 180+(int)(atan2(y,x)*180/PI);
    fprintf(file, "%d,%d,%d,%d,%d,%d\n",i,x,y,z,r,theta);
  }
  fclose(file); 
}


Universe newCircularUniverse(int n, int size, int gapSize) {
  Universe u;
  u.n = n;

  // Extra random!
  struct timeval time; 
  gettimeofday(&time,NULL);
  srand((time.tv_sec * 1000) + (time.tv_usec / 1000));

  u.bodies = calloc(n, sizeof(Body));
  u.bodies[0] = newBody(0, 0, 0, 0, 0, 0, 1000*u.n);

  double theta, r, ov, mass = 1000*u.n+10;
  for (int i = 1; i < u.n; i++) {
    theta = rand() % 360;
    r = gapSize + (rand() % (size - gapSize));
    ov = sqrt(mass/r);
    u.bodies[i] = newBody(r*cos(theta), r*sin(theta), 0, -ov*sin(theta), ov*cos(theta), 0, 10);
  }

  return u;
}

Universe newSpiralUniverse(int n, int size, int gapSize) {
  Universe u;
  u.n = n;

  // Extra random!
  struct timeval time; 
  gettimeofday(&time,NULL);
  srand((time.tv_sec * 1000) + (time.tv_usec / 1000));

  u.bodies = calloc(n, sizeof(Body));

  double theta, rot, r, vr, rx, ry, vx, vy, localwidth, mass = 1;
  int ellipses = u.n/10;
  int num = 10;
  double eangle = 540/(double)ellipses;
  double ewidth = (size-gapSize)/ellipses;
  for (int e = 0; e < ellipses; e++) {
    //localwidth = ewidth*(exp(1+2*(float)e/ellipses)/(exp(3)-exp(1))); //* exp(1+2*(double)e/ELLIPSES);
    localwidth = ewidth;
    rot = eangle*e * PI/180;
    for (int i = 0; i < num; i++) {
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
      vx = -sqrt(1000*u.n/r)*sin(theta);
      vy = sqrt(1000*u.n/r)*cos(theta);
      u.bodies[e*num + i] = newBody(rx, ry, 0, vx, vy, 0, mass);
    }
    gapSize += localwidth;
  }
  
  u.bodies[0] = newBody(0, 0, 0, 0, 0, 0, 1000*u.n);

  return u;
}
