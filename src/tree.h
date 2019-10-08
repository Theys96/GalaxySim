/*
 * Part of the GalaxySim project
 * by J. Klemm
 *
 * TODO: Library description to be written here.
 */

#include "bodies.h"

typedef struct Position {
  double x;
  double y;
  double z;
} Position;

typedef struct UniverseSize {
  double min_x;
  double max_x;
  double min_y;
  double max_y;
  double min_z;
  double max_z;
} UniverseSize;

typedef struct Node {
  Position pos;
  double mass;
} Node;

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
  Node *value;
  double mass;
  Position centerOfMass;
  UniverseSize *universe_size;
  int node_count;
};

typedef struct Tree {
	Subnode *root;
} Tree;

Position newPosition();
Node newNode();
Subnode newSubnode();
Tree newTree(Body *bodies, int n);

void insertNode(Subnode *t, Node *node);
UniverseSize getUniverseSize(Body *bodies, int n);
Subnode **getQuadrant(Subnode *s, Node *node);
