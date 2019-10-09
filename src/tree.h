/*
 * Part of the GalaxySim project
 * by J. Klemm
 *
 * TODO: Library description to be written here.
 */

#ifndef TREE_H
#define TREE_H 1

#include "bodies.h"

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
  UniverseSize universe_size;
  int node_count;
};

typedef Subnode* Tree;

Subnode newSubnode(UniverseSize universe_size);
Tree newTree(Universe u);
void freeSubnode(Subnode *s);
void freeTree(Tree t);

void insertBody(Subnode *s, Body body);
UniverseSize getUniverseSize(Universe u);
UniverseSize getQuadrantSize(UniverseSize original, int index);
Subnode *getQuadrant(Subnode *s, Body body);

void computeMass(Subnode *s);
double max(double a, double b, double c);
void computeForceFromTree(Body object, Subnode *s, double fvec[3]);

#endif
