/*
 * Part of the GalaxySim project
 * by J. Klemm
 *
 * Provides an implementation for a tree of bodies as used
 * in the Barnes-Hut algorithm for N-body simulation.
 */

#ifndef TREE_H
#define TREE_H 1

#include "bodies.h"

extern double delta_barnes_hut;

typedef struct UniverseSize {
  double min_x;
  double max_x;
  double min_y;
  double max_y;
  double min_z;
  double max_z;
} UniverseSize;

typedef struct Subnode Subnode;

struct Subnode {
  Subnode* children[8];
  Body value;
  UniverseSize size;
  int node_count;
};

typedef Subnode* Tree;

/* Creates a new Barnes-Hut tree of bodies from the given Universe u.
 * Inputs:
 *  - u    : Universe struct to input.
 */
Tree newTree(Universe u);

/* Uses the Barnes-Hut algorithm to compute the force exerted on
 * body `object` by the rest of the given universe `s`. The force
 * is set in fvec.
 * Inputs:
 *  - object  : The Body struct representing the body to compute
 *              the exerted force for.
 *  - s       : Barnes-Hut tree object representing the universe.
 *  - fvec    : Vector of 3 doubles to return the force vector.
 */
void computeForceFromTree(Body object, Subnode *s, double fvec[3]);

/* Frees the given Barnes-Hut tree and with it all its subnodes.
 * Inputs:
 *  - t    : Tree to free.
 */
void freeTree(Tree t);

#endif
