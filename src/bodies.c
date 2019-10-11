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
#include <stdio.h>
#include <time.h>
#define G 1

// Local methods
void updateVelocities(Universe* u, double dt);
void updateLocations(Universe* u, double dt);
double totalPotentialEnergy(Universe u);
double totalKineticEnergy(Universe u);


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

double bodyDistance(Body a, Body b) {
  return sqrt(pow(b.x - a.x,2) + pow(b.y - a.y,2) + pow(b.z - a.z,2));
}

void computeForce(Body a, Body b, double fvec[3]) {
  double dist = bodyDistance(a,b);
  if (dist < 1) { dist = 1; }
  int f = G * a.mass * b.mass / (dist*dist);
  fvec[0] = (b.x - a.x)/dist * f;
  fvec[1] = (b.y - a.y)/dist * f;
  fvec[2] = (b.z - a.z)/dist * f;
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

Universe copyUniverse(Universe u) {
  Universe u2;
  u2.n = u.n;
  u2.bodies = calloc(u2.n, sizeof(Body));
  for (int i = 0; i < u2.n; i++) {
    u2.bodies[i] = u.bodies[i];
  }
  return u2;
}

double totalEnergy(Universe u) {
  return totalPotentialEnergy(u) + totalKineticEnergy(u);
}

void freeUniverse(Universe u) {
  free(u.bodies);
}


void iterateEuler(Universe* u, double dt) {
  // Update locations
  updateLocations(u, dt);

  // Update velocities
  updateVelocities(u, dt);
}

void iterateBarnesHut(Universe* u, double dt) {
  // Update locations
  updateLocations(u, dt);

  // Create Tree
  Tree t = newTree(*u);

  // Update velocities
  Body* b;
  double f[3];
  for (int i = 0; i < u->n; i++) {
    b = u->bodies + i;
    computeForceFromTree(*b, t, f);
    b->dx += dt * f[0]/(b->mass);
    b->dy += dt * f[1]/(b->mass);
    b->dz += dt * f[2]/(b->mass);
  }

  // Free the tree 
  freeTree(t);
}

void iterateMostSignificant(Universe* u, double dt, double minMass) {
  // Update locations
  updateLocations(u, dt);

  // Update velocities
  Body *b, *c;
  double f[3];
  for (int i = 0; i < u->n; i++) {
    b = u->bodies + i;
    if (b->mass >= minMass) {
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
  }
}


/* HELPER FUNCTIONS */

void updateVelocities(Universe* u, double dt) {
  Body *b, *c;
  double f[3];
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
}

void updateLocations(Universe* u, double dt) {
  Body* b;
  for (int i = 0; i < u->n; i++) {
    b = u->bodies + i;
    b->x += dt * b->dx;
    b->y += dt * b->dy;
    b->z += dt * b->dz;
  }
}

double totalPotentialEnergy(Universe u) {
  double dist;
  double energy = 0;
  Body a, b;
  for (int i = 0; i < u.n; i++) {
    a = u.bodies[i];
    for (int j = i+1; j < u.n; j++) {
      b = u.bodies[i];
      dist = bodyDistance(a,b);
      if (dist > 0) {
        energy -= G * a.mass * b.mass / dist;
      }
    }
  }
  return energy;
}

double totalKineticEnergy(Universe u) {
  double energy = 0;
  Body a;
  for (int i = 0; i < u.n; i++) {
    a = u.bodies[i];
    energy += a.mass + fabs(a.dx*a.dx + a.dy*a.dy + a.dz*a.dz);
  }
  return energy/2;
}
