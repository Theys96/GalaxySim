/*
 * Part of the GalaxySim project
 * by J. Klemm
 *
 * TODO: Library description to be written here.
 */

#ifndef TREE_H
#define TREE_H 1
#include "bodies.h"

typedef struct Body Body;

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
  Subnode *childTopNE;
  Subnode *childTopNW;
  Subnode *childTopSE;
  Subnode *childTopSW;
  Subnode *childBottomNE;
  Subnode *childBottomNW;
  Subnode *childBottomSE;
  Subnode *childBottomSW;
  Body *value;
  double mass;
  double centerOfMass[3];
  UniverseSize universe_size;
  int node_count;
};

typedef struct Tree {
	Subnode *root;
} Tree;

// Position newPosition();
Subnode newSubnode();
Tree newTree(Body *bodies, int n);

void insertBody(Subnode *t, Body *body);
UniverseSize getUniverseSize(Body *bodies, int n);
Subnode **getQuadrant(Subnode *s, Body *body);

void computeMass(Subnode *s);
void computeForceFromTree(Body *object, Subnode *s, double fvec[3]);
#endif
