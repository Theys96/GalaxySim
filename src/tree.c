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

#define DELTA_STAR 0.0001
#define DELTA_BARNES_HUT 0.5

Subnode newSubnode(UniverseSize universe_size) {
  Subnode s;
  for (size_t i = 0; i < 8; i++) {
    s.children[i] = NULL;
  }
  s.value = newBody(0,0,0,0,0,0,0);
  s.universe_size = universe_size;
  s.node_count = 0;
  return s;
}

Tree newTree(Universe u) {
  Tree t = calloc(1, sizeof(Subnode));
  *t = newSubnode(getUniverseSize(u));

  for (int i = 0; i < u.n; i++) {
    insertBody(t, u.bodies[i]);
  }
  return t;
}

void freeSubnode(Subnode *s) {
  for (size_t i = 0; i < 8; i++) {
    if (s->children[i] != NULL) {
      freeSubnode(s->children[i]);
    }
  }
  free(s);
}

void freeTree(Tree t) {
  freeSubnode(t);
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
  UniverseSize universe_size;
  universe_size.min_x = u.bodies[0].x;
  universe_size.max_x = u.bodies[0].x;
  universe_size.min_y = u.bodies[0].y;
  universe_size.max_y = u.bodies[0].y;
  universe_size.min_z = u.bodies[0].z;
  universe_size.max_z = u.bodies[0].z;
  for (int i = 1; i < u.n; i++) {
    if (u.bodies[i].x < universe_size.min_x) {
      universe_size.min_x = u.bodies[i].x;
    } else if (u.bodies[i].x > universe_size.max_x) {
      universe_size.max_x = u.bodies[i].x;
    }
    if (u.bodies[i].y < universe_size.min_y) {
      universe_size.min_y = u.bodies[i].y;
    } else if (u.bodies[i].y > universe_size.max_y) {
      universe_size.max_y = u.bodies[i].y;
    }
    if (u.bodies[i].z < universe_size.min_z) {
      universe_size.min_z = u.bodies[i].z;
    } else if (u.bodies[i].z > universe_size.max_z) {
      universe_size.max_z = u.bodies[i].z;
    }
  }

  return universe_size;
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
  UniverseSize universe_size = s->universe_size;
  int index = 
    1 * (body.x > (universe_size.max_x + universe_size.min_x) / 2.0) +
    2 * (body.y > (universe_size.max_y + universe_size.min_y) / 2.0) + 
    4 * (body.z > (universe_size.max_z + universe_size.min_z) / 2.0);

  if (s->children[index] == NULL) {
    s->children[index] = calloc(1, sizeof(Subnode));
    *(s->children[index]) = newSubnode(getQuadrantSize(universe_size, index));
  }

  return s->children[index];

  /*
  Subnode **quadrant = NULL;
  UniverseSize new_universe_size = s->universe_size;

  if (body.z <= (s->universe_size.max_z + s->universe_size.min_z) / 2.0) {
    new_universe_size.max_z = (s->universe_size.max_z + s->universe_size.min_z) / 2.0;
    if (body.y <= (s->universe_size.max_y + s->universe_size.min_y) / 2.0) {
      new_universe_size.max_y = (s->universe_size.max_y + s->universe_size.min_y) / 2.0;
      if (body.x <= (s->universe_size.max_x + s->universe_size.min_x) / 2.0) {
        new_universe_size.max_x = (s->universe_size.max_x + s->universe_size.min_x) / 2.0;
        quadrant = &s->childTopNW;
      } else {
        new_universe_size.min_x = (s->universe_size.max_x + s->universe_size.min_x) / 2.0;
        quadrant = &s->childTopNE;
      }
    } else {
      new_universe_size.min_y = (s->universe_size.max_y + s->universe_size.min_y) / 2.0;
      if (body.x <= (s->universe_size.max_x + s->universe_size.min_x) / 2.0) {
        new_universe_size.max_x = (s->universe_size.max_x + s->universe_size.min_x) / 2.0;
        quadrant = &s->childTopSW;
      } else {
        new_universe_size.min_x = (s->universe_size.max_x + s->universe_size.min_x) / 2.0;
        quadrant = &s->childTopSE;
      }
    }
  } else {
    new_universe_size.min_z = (s->universe_size.max_z + s->universe_size.min_z) / 2.0;
    if (body.y <= (s->universe_size.max_y + s->universe_size.min_y) / 2.0) {
      new_universe_size.max_y = (s->universe_size.max_y + s->universe_size.min_y) / 2.0;
      if (body.x <= (s->universe_size.max_x + s->universe_size.min_x) / 2.0) {
        new_universe_size.max_x = (s->universe_size.max_x + s->universe_size.min_x) / 2.0;
        quadrant = &s->childBottomNW;
      } else {
        new_universe_size.min_x = (s->universe_size.max_x + s->universe_size.min_x) / 2.0;
        quadrant = &s->childBottomNE;
      }
    } else {
      new_universe_size.min_y = (s->universe_size.max_y + s->universe_size.min_y) / 2.0;
      if (body.x <= (s->universe_size.max_x + s->universe_size.min_x) / 2.0) {
        new_universe_size.max_x = (s->universe_size.max_x + s->universe_size.min_x) / 2.0;
        quadrant = &s->childBottomSW;
      } else {
        new_universe_size.min_x = (s->universe_size.max_x + s->universe_size.min_x) / 2.0;
        quadrant = &s->childBottomSE;
      }
    }
  }
  // create a new subnode for an empty child
  if (*quadrant == NULL) {
    *quadrant = calloc(1, sizeof(Subnode));
    **quadrant = newSubnode(new_universe_size);
  }

  return quadrant;
  */
}

void computeMass(Subnode *s) {
  if (s->node_count > 1) {
    s->value = newBody(0,0,0,0,0,0,0);
    // calculate the mass dependent on all child cubic cells
    for (size_t i = 0; i < 8; i++) {
      if (s->children[i] != NULL) {
        computeMass(s->children[i]);
        s->value.mass += s->children[i]->value.mass;
        s->value.x += s->children[i]->value.x;
        s->value.y += s->children[i]->value.y;
        s->value.z += s->children[i]->value.z;
      }
    }
    if (s->value.mass > 0.0) {
      s->value.x /= s->value.mass;
      s->value.y /= s->value.mass;
      s->value.z /= s->value.mass;
    }
  }
}

double max(double a, double b, double c) {
  double result = (a > b) ? a : b;
  result = (result > c) ? result : c;
  return result;
}

void computeForceFromTree(Body object, Subnode *s, double fvec[3]) {
  if (s->node_count == 1) {
    computeForce(object, s->value, fvec);
  } else {
    double radius = bodyDistance(object, s->value);
    double height = max(s->universe_size.max_x - s->universe_size.min_x, s->universe_size.max_y - s->universe_size.min_y, s->universe_size.max_z - s->universe_size.min_z);
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
