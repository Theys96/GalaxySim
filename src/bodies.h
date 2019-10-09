/* 
 * Part of the GalaxySim project
 * by M.J. Havinga
 * 
 * This file contains the definitions for the Body struct and its functions.
 * A Body in this context represents an object with a x,y,z coordinate, a velocity in the same dimensions,
 * and a mass.
 * It can exert a gravity force on other Bodies which can be computed by the given function.
 */

#ifndef BODIES_H
#define BODIES_H 1

typedef struct Body {
  double x;
  double y;
  double z;
  double dx;
  double dy;
  double dz;
  double mass;
} Body;

typedef struct Universe {
    Body* bodies;
    int n;
} Universe;

Body newBody(double x, double y, double z, double dx, double dy, double dz, double mass);
double bodyDistance(Body a, Body b);
void computeForce(Body a, Body b, double fvec[3]);

Universe newUniverse(int N);

void iterateEuler(Universe* u, double dt);
void iterateBarnesHut(Universe* u, double dt);

void freeUniverse(Universe u);

#endif
