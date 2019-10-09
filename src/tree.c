/*
 * Part of the GalaxySim project
 * by J. Klemm
 *
 * Code file for tree.c
 */

#include "tree.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

/* LOCAL FUNCTIONS*/
Subnode newSubnode(UniverseSize universe_size);
void freeSubnode(Subnode *s);
UniverseSize getUniverseSize(Universe u);
UniverseSize getQuadrantSize(UniverseSize original, int index);
Subnode *getQuadrant(Subnode *s, Body body);
void insertBody(Subnode *s, Body body);
void computeMass(Subnode *s);
double max(double a, double b, double c);

#define DELTA_STAR 0.0001
#define DELTA_BARNES_HUT 0.5


Tree newTree(Universe u) {
  Tree t = calloc(1, sizeof(Subnode));
  *t = newSubnode(getUniverseSize(u));

  for (int i = 0; i < u.n; i++) {
    insertBody(t, u.bodies[i]);
  }

  computeMass(t);

  return t;
}

void computeForceFromTree(Body object, Subnode *s, double fvec[3]) {
  fvec[0] = 0; fvec[1] = 0; fvec[2] = 0; 
  if (s->node_count == 1) {
    computeForce(object, s->value, fvec);
  } else {
    double radius = bodyDistance(object, s->value);
    double height = max(s->size.max_x - s->size.min_x, s->size.max_y - s->size.min_y, s->size.max_z - s->size.min_z);
    if (height/radius < DELTA_BARNES_HUT) {
      computeForce(object, s->value, fvec);
    } else {
      // compute the forces for all child cubic cells
      for (size_t i = 0; i < 8; i++) {
        if (s->children[i] != NULL) {
          double fsubvec[3];
          computeForceFromTree(object, s->children[i], fsubvec);
          fvec[0] += fsubvec[0];
          fvec[1] += fsubvec[1];
          fvec[2] += fsubvec[2];
        }
      }
    }
  }
}

void freeTree(Tree t) {
  freeSubnode(t);
}



Subnode newSubnode(UniverseSize universe_size) {
  Subnode s;
  for (size_t i = 0; i < 8; i++) {
    s.children[i] = NULL;
  }
  s.value = newBody(0,0,0,0,0,0,0);
  s.size = universe_size;
  s.node_count = 0;
  return s;
}

void freeSubnode(Subnode *s) {
  for (size_t i = 0; i < 8; i++) {
    if (s->children[i] != NULL) {
      freeSubnode(s->children[i]);
    }
  }
  free(s);
}

void insertBody(Subnode *s, Body body) {
  if (s->node_count > 1) {
    Subnode *quadrant = getQuadrant(s, body);
    insertBody(quadrant, body);
  } else if (s->node_count == 1) {
    // If two bodies are very close to each other, we regard them as one mass
    if (bodyDistance(s->value, body) < DELTA_STAR) {
      s->value.mass += body.mass;
    } 
    else {
      Subnode *quadrant = getQuadrant(s, s->value);
      insertBody(quadrant, s->value);

      Subnode *quadrant2 = getQuadrant(s, body);
      insertBody(quadrant2, body);

      s->value = newBody(0,0,0,0,0,0,0);
    }
  } else {
    s->value = body;
  }
  s->node_count++;
}

UniverseSize getUniverseSize(Universe u) {
  UniverseSize sz;

  sz.min_x = u.bodies[0].x;
  sz.max_x = u.bodies[0].x;
  sz.min_y = u.bodies[0].y;
  sz.max_y = u.bodies[0].y;
  sz.min_z = u.bodies[0].z;
  sz.max_z = u.bodies[0].z;
  for (int i = 1; i < u.n; i++) {
    sz.min_x = u.bodies[i].x < sz.min_x ? u.bodies[i].x : sz.min_x;
    sz.max_x = u.bodies[i].x > sz.max_x ? u.bodies[i].x : sz.max_x;
    sz.min_y = u.bodies[i].y < sz.min_y ? u.bodies[i].y : sz.min_y;
    sz.max_y = u.bodies[i].y > sz.max_y ? u.bodies[i].y : sz.max_y;
    sz.min_z = u.bodies[i].z < sz.min_z ? u.bodies[i].z : sz.min_z;
    sz.max_z = u.bodies[i].z > sz.max_z ? u.bodies[i].z : sz.max_z;
  }

  return sz;
}

UniverseSize getQuadrantSize(UniverseSize original, int index) {
  UniverseSize sz = original;
  if (index & 1) {
    sz.min_x = (original.max_x + original.min_x) / 2.0;
  } else {
    sz.max_x = (original.max_x + original.min_x) / 2.0;
  }
  if (index & 2) {
    sz.min_y = (original.max_y + original.min_y) / 2.0;
  } else {
    sz.max_y = (original.max_y + original.min_y) / 2.0;
  }
  if (index & 4) {
    sz.min_z = (original.max_z + original.min_z) / 2.0;
  } else {
    sz.max_z = (original.max_z + original.min_z) / 2.0;
  }
  return sz;
}

Subnode *getQuadrant(Subnode *s, Body body) {
  UniverseSize sz = s->size;
  int index = 
    1 * (body.x > (sz.max_x + sz.min_x) / 2.0) +
    2 * (body.y > (sz.max_y + sz.min_y) / 2.0) + 
    4 * (body.z > (sz.max_z + sz.min_z) / 2.0);

  if (s->children[index] == NULL) {
    s->children[index] = calloc(1, sizeof(Subnode));
    *(s->children[index]) = newSubnode(getQuadrantSize(sz, index));
  }

  return s->children[index];
}

void computeMass(Subnode *s) {
  // Only for nodes with more than 1 body an operation is required
  if (s->node_count > 1) {
    s->value = newBody(0,0,0,0,0,0,0);
    for (size_t i = 0; i < 8; i++) {
      if (s->children[i] != NULL) {
        computeMass(s->children[i]);
        Body com = s->children[i]->value;
        if (com.mass > 0.0) {
          s->value.mass += com.mass;
          s->value.x += com.x / com.mass;
          s->value.y += com.y / com.mass;
          s->value.z += com.z / com.mass;
        }
      }
    }
  }
}

double max(double a, double b, double c) {
  double result = (a > b) ? a : b;
  result = (result > c) ? result : c;
  return result;
}
