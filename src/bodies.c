/*
 * Part of the GalaxySim project
 * by M.J. Havinga
 * 
 * Code file for bodies.h
 */


#include "bodies.h"
#include "tree.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define G 1

double bodyDistance(Body a, Body b) {
  return sqrt(pow(b.x - a.x,2) + pow(b.y - a.y,2) + pow(b.z - a.z,2));
}

void computeForce(Body a, Body b, double fvec[3]) {
  float dist = bodyDistance(a,b);
  if (dist < 1) { dist = 1; }
  int f = G * a.mass * b.mass / (dist*dist);
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

Universe newUniverse(int n) {
  Universe u;
  u.n = n;
  u.bodies = calloc(n, sizeof(Body));
  for (int i = 0; i < n; i++) {
    u.bodies[i] = newBody(0,0,0,0,0,0,1);
  }
  return u;
}

Universe newCircularUniverse(int n, int size, int gapSize) {
  Universe u;
  u.n = n;

  srand(time(NULL));
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

void iterateBarnesHut(Universe* u, double dt) {
  double f[3];
  // Body *b, *c;
  Body* b;

  // Create Tree and calculate masses of the center of gravities
  Tree t = newTree(*u);
  computeMass(t);

  // Update velocities
  for (int i = 0; i < u->n; i++) {
    double fvec[3];
    b = u->bodies + i;
    computeForceFromTree(*b, t, fvec);
    b->dx += dt * f[0]/(b->mass);
    b->dy += dt * f[1]/(b->mass);
    b->dz += dt * f[2]/(b->mass);
  }

  // Free the tree 
  freeTree(t);

  for (int i = 0; i < u->n; i++) {
    b = u->bodies + i;
    b->x += dt * b->dx;
    b->y += dt * b->dy;
    b->z += dt * b->dz;
  }
}

void iterateNaive(Universe* u, double dt) {
  double f[3];
  Body *b, *c;

  // Update velocities
  for (int i = 0; i < u->n; i++) {
    b = u->bodies + i;
    for (int j = i+1; j < u->n; j++) {
      c = u->bodies + j;
      computeForce(*b, *c, f);
      b->dx += dt * f[0]/(b->mass);
      b->dy += dt * f[1]/(b->mass);
      b->dz += dt * f[2]/(b->mass);
      c->dx -= dt * f[0]/(c->mass);
      c->dy -= dt * f[1]/(c->mass);
      c->dz -= dt * f[2]/(c->mass);
    }
  }

  // Update locations
  for (int i = 0; i < u->n; i++) {
    b = u->bodies + i;
    b->x += dt * b->dx;
    b->y += dt * b->dy;
    b->z += dt * b->dz;
  }
}

void freeUniverse(Universe u) {
  free(u.bodies);
}

