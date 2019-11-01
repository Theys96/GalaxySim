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

/* Returns Body struct with the specified parameters.
 * Inputs:
 *  - x, y, z      : Cartesian coordinates of the body
 *  - dx, dy, dz   : Velocity vector of the body
 *  - mass         : Mass of the body
 */
Body newBody(double x, double y, double z, double dx, double dy, double dz, double mass);

/* Computes the distance between two given bodies.
 * Inputs:
 *  - a, b         : Bodies between which the distance is computed.
 */
double bodyDistance(Body a, Body b);

/* Computes the (gravity) force between two bodies.
 * The returned force vector is for Body a. For Body b
 * it is its exact opposite (negated).
 * Inputs:
 *  - a            : Body on which the force is exerted.
 *  - b            : Body which exerts the force.
 */
void computeForce(Body a, Body b, double fvec[3]);

/* Perform an addition operation on two bodies. This is useful for transforming
 * the location and velocity vectors using another "Body" as the transformation.
 * Inputs:
 *  - a, b         : Bodies to add together.
 */
Body addBodies(Body a, Body b);


/* Returns a new Universe struct with N bodies in it,
 * already allocated.
 * Inputs:
 *  - N            : Number of bodies allocated in the universe.
 */
Universe newUniverse(int N);

Universe copyUniverse(Universe u);

double totalEnergy(Universe u);

/* Frees a universe struct (all of its bodies).
 * Inputs:
 *  - u            : Universe struct to free.
 */
void freeUniverse(Universe u);


/* Iterates the universe state u to a next state with
 * timestep `dt` using the naive Eulerean method.
 * Inputs:
 *  - u            : pointer to the universe state to iterate on.
 *  - dt           : timestep to use for iteration.
 */
void iterateEuler(Universe* u, double dt);

/* Iterates the universe state u to a next state with
 * timestep `dt` using the naive Eulerean method in
 * combination with the Barnes-Hut algorithm.
 * Inputs:
 *  - u            : pointer to the universe state to iterate on.
 *  - dt           : timestep to use for iteration.
 *  - theta        : theta paarmeter for the Barnes-Hut algorithm
 */
void iterateBarnesHut(Universe* u, double dt, double theta);

/* Iterates the universe state u to a next state with
 * timestep `dt` using the naive Eulerean method and only
 * regarding the most significant body/bodies for the
 * gravity simulation. This works if there is a single
 * or a few very heavy bodies that more or less dictate
 * all gravity.
 * Inputs:
 *  - u            : pointer to the universe state to iterate on.
 *  - dt           : timestep to use for iteration.
 */
void iterateMostSignificant(Universe* u, double dt, double minMass);

#endif
