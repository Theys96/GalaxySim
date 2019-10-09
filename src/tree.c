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
#include <time.h>

#define DELTA_STAR 0.0001
#define DELTA_BARNES_HUT 0.5

Subnode newSubnode(UniverseSize *universe_size) {
  Subnode s;
  s.childTopNE = NULL;
  s.childTopNW = NULL;
  s.childTopSE = NULL;
  s.childTopSW = NULL;
  s.childBottomNE = NULL;
  s.childBottomNW = NULL;
  s.childBottomSE = NULL;
  s.childBottomSW = NULL;
  s.value = calloc(1, sizeof(Body));
  *(s.value) = newBody(0,0,0,0,0,0,0);
  s.universe_size = *universe_size;
  s.node_count = 0;
  return s;
}

Tree newTree(Body *bodies, int n) {
  Tree t;
  t.root = calloc(1, sizeof(Subnode));
  UniverseSize universe_size = getUniverseSize(bodies, n);
  *t.root = newSubnode(&universe_size);
  for (int i = 0; i < n; i++) {
    insertBody(t.root, bodies + i);
  }
  return t;
}

void freeSubnode(Subnode *s) {
  Subnode *childs[8] = {s->childTopNE, s->childTopNW, s->childTopSE, s->childTopSW, s->childBottomNE, s->childBottomNW, s->childBottomSE, s->childBottomSW};
  for (size_t i = 0; i < 8; i++) {
    if (childs[i] != NULL) {
      freeSubnode(childs[i]);
    }
  }
  free(s->value);
  free(s);
}

void freeTree(Tree *t) {
  freeSubnode(t->root);
}

void insertBody(Subnode *s, Body *body) {
  if (s->node_count > 1) {
    Subnode **quadrant = getQuadrant(s, body);
    insertBody(*quadrant, body);
  } else if (s->node_count == 1) {
    Subnode **quadrant = getQuadrant(s, s->value);
    insertBody(*quadrant, s->value);
    s->value->x = 0;
    s->value->y = 0;
    s->value->z = 0;
    s->value->mass = 0;

    Subnode **quadrant2 = getQuadrant(s, body);
    // change the cubic cell to prevent infinity recursive call for bodies
    // which are very close to each other.
    if (*quadrant2 == *quadrant && (*quadrant)->universe_size.max_x - (*quadrant)->universe_size.min_x < DELTA_STAR && (*quadrant)->universe_size.max_y - (*quadrant)->universe_size.min_y < DELTA_STAR && (*quadrant)->universe_size.max_z - (*quadrant)->universe_size.min_z < DELTA_STAR) {
      Subnode *childs[8] = {s->childTopNE, s->childTopNW, s->childTopSE, s->childTopSW, s->childBottomNE, s->childBottomNW, s->childBottomSE, s->childBottomSW};
      for (size_t i = 0; i < 8; i++) {
        if (childs[i] == NULL || childs[i]->node_count == 0) {
          quadrant2 = childs+i;
          *quadrant2 = calloc(1, sizeof(Subnode));
          **quadrant2 = newSubnode(&((*quadrant)->universe_size));
          break;
        }
      }
    }
    insertBody(*quadrant2, body);
  } else {
    s->value->x = body->x;
    s->value->y = body->y;
    s->value->z = body->z;
    s->value->mass = body->mass;
  }
  s->node_count++;
}

UniverseSize getUniverseSize(Body *bodies, int n) {
  UniverseSize universe_size;
  universe_size.min_x = bodies[0].x;
  universe_size.max_x = bodies[0].x;
  universe_size.min_y = bodies[0].y;
  universe_size.max_y = bodies[0].y;
  universe_size.min_z = bodies[0].z;
  universe_size.max_z = bodies[0].z;
  for (int i = 1; i < n; i++) {
    if (bodies[i].x < universe_size.min_x) {
      universe_size.min_x = bodies[i].x;
    } else if (bodies[i].x > universe_size.max_x) {
      universe_size.max_x = bodies[i].x;
    }
    if (bodies[i].y < universe_size.min_y) {
      universe_size.min_y = bodies[i].y;
    } else if (bodies[i].y > universe_size.max_y) {
      universe_size.max_y = bodies[i].y;
    }
    if (bodies[i].z < universe_size.min_z) {
      universe_size.min_z = bodies[i].z;
    } else if (bodies[i].z > universe_size.max_z) {
      universe_size.max_z = bodies[i].z;
    }
  }

  return universe_size;
}

Subnode **getQuadrant(Subnode *s, Body *body) {
  Subnode **quadrant = NULL;
  UniverseSize new_universe_size;
  memcpy(&new_universe_size, &(s->universe_size), sizeof(UniverseSize));
  if (body->z <= (s->universe_size.max_z + s->universe_size.min_z) / 2.0) {
    new_universe_size.max_z = (s->universe_size.max_z + s->universe_size.min_z) / 2.0;
    if (body->y <= (s->universe_size.max_y + s->universe_size.min_y) / 2.0) {
      new_universe_size.max_y = (s->universe_size.max_y + s->universe_size.min_y) / 2.0;
      if (body->x <= (s->universe_size.max_x + s->universe_size.min_x) / 2.0) {
        new_universe_size.max_x = (s->universe_size.max_x + s->universe_size.min_x) / 2.0;
        quadrant = &s->childTopNW;
      } else {
        new_universe_size.min_x = (s->universe_size.max_x + s->universe_size.min_x) / 2.0;
        quadrant = &s->childTopNE;
      }
    } else {
      new_universe_size.min_y = (s->universe_size.max_y + s->universe_size.min_y) / 2.0;
      if (body->x <= (s->universe_size.max_x + s->universe_size.min_x) / 2.0) {
        new_universe_size.max_x = (s->universe_size.max_x + s->universe_size.min_x) / 2.0;
        quadrant = &s->childTopSW;
      } else {
        new_universe_size.min_x = (s->universe_size.max_x + s->universe_size.min_x) / 2.0;
        quadrant = &s->childTopSE;
      }
    }
  } else {
    new_universe_size.min_z = (s->universe_size.max_z + s->universe_size.min_z) / 2.0;
    if (body->y <= (s->universe_size.max_y + s->universe_size.min_y) / 2.0) {
      new_universe_size.max_y = (s->universe_size.max_y + s->universe_size.min_y) / 2.0;
      if (body->x <= (s->universe_size.max_x + s->universe_size.min_x) / 2.0) {
        new_universe_size.max_x = (s->universe_size.max_x + s->universe_size.min_x) / 2.0;
        quadrant = &s->childBottomNW;
      } else {
        new_universe_size.min_x = (s->universe_size.max_x + s->universe_size.min_x) / 2.0;
        quadrant = &s->childBottomNE;
      }
    } else {
      new_universe_size.min_y = (s->universe_size.max_y + s->universe_size.min_y) / 2.0;
      if (body->x <= (s->universe_size.max_x + s->universe_size.min_x) / 2.0) {
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
    **quadrant = newSubnode(&new_universe_size);
  }

  return quadrant;
}

void computeMass(Subnode *s) {
  if (s->node_count > 1) {
    s->value->mass = 0.0;
    s->value->x = 0.0;
    s->value->y = 0.0;
    s->value->z = 0.0;
    Subnode *childs[8] = {s->childTopNE, s->childTopNW, s->childTopSE, s->childTopSW, s->childBottomNE, s->childBottomNW, s->childBottomSE, s->childBottomSW};
    // calculate the mass dependent on all child cubic cells
    for (size_t i = 0; i < 8; i++) {
      if (childs[i] != NULL) {
        computeMass(childs[i]);
        s->value->mass += childs[i]->value->mass;
        s->value->x += childs[i]->value->x;
        s->value->y += childs[i]->value->y;
        s->value->z += childs[i]->value->z;
      }
    }
    if (s->value->mass > 0.0) {
      s->value->x /= s->value->mass;
      s->value->x /= s->value->mass;
      s->value->x /= s->value->mass;
    }
  }
}

void computeForceFromTree(Body *object, Subnode *s, double fvec[3]) {
  if (s->node_count == 1) {
    computeForce(*object, *s->value, fvec);
  } else {
    double radius = sqrt(pow(object->x - s->value->x, 2) + pow(object->y - s->value->y, 2) + pow(object->z - s->value->z, 2));
    double height = s->universe_size.max_x - s->universe_size.min_x;
    if (height/radius < DELTA_BARNES_HUT) {
      computeForce(*object, *s->value, fvec);
    } else {
      Subnode *childs[8] = {s->childTopNE, s->childTopNW, s->childTopSE, s->childTopSW, s->childBottomNE, s->childBottomNW, s->childBottomSE, s->childBottomSW};
      // compute the forces for all child cubic cells
      for (size_t i = 0; i < 8; i++) {
        if (childs[i] != NULL) {
          double fsubvec[3];
          computeForceFromTree(object, childs[i], fsubvec);
          fvec[0] += fsubvec[0];
          fvec[1] += fsubvec[1];
          fvec[2] += fsubvec[2];
        }
      }
    }
  }
}
