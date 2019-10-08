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

// Position newPosition() {
//   Position pos;
//   pos.x = 0.0;
//   pos.y = 0.0;
//   pos.z = 0.0;
//   return pos;
// }

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
  s.value = NULL;
  // s.mass = 0.0;
  s.centerOfMass[0] = 0.0;
  s.centerOfMass[1] = 0.0;
  s.centerOfMass[2] = 0.0;
  // s.centerOfMass = newPosition();
  s.universe_size = universe_size;
  s.node_count = 0;
  return s;
}

Tree newTree(Body *bodies, int n) {
  Tree t;
  t.root = calloc(1, sizeof(Subnode));
  UniverseSize universe_size = getUniverseSize(bodies, n);
  *t.root = newSubnode(&universe_size);
  for (int i = 0; i < n; i++) {
    Body body;
    insertBody(t.root, &body);
  }
  return t;
}

void insertBody(Subnode *s, Body *body) {
  if (s->node_count > 1) {
    Subnode **quadrant = getQuadrant(s, body);
    insertBody(*quadrant, body);
  } else if (s->node_count == 1) {
    Subnode **quadrant = getQuadrant(s, s->value);
    insertBody(*quadrant, s->value);
    s->value = NULL;

    Subnode **quadrant2 = getQuadrant(s, body);
    insertBody(*quadrant2, body);
  } else {
    s->value = body;
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
  memcpy(&new_universe_size, s->universe_size, sizeof(UniverseSize));
  if (body->z <= (s->universe_size->max_z + s->universe_size->min_z) / 2.0) {
    new_universe_size.max_z = (s->universe_size->max_z + s->universe_size->min_z) / 2.0;
    if (body->y <= (s->universe_size->max_y + s->universe_size->min_y) / 2.0) {
      new_universe_size.max_y = (s->universe_size->max_y + s->universe_size->min_y) / 2.0;
      if (body->x <= (s->universe_size->max_x + s->universe_size->min_x) / 2.0) {
        new_universe_size.max_x = (s->universe_size->max_x + s->universe_size->min_x) / 2.0;
        quadrant = &s->childTopNW;
      } else {
        new_universe_size.min_x = (s->universe_size->max_x + s->universe_size->min_x) / 2.0;
        quadrant = &s->childTopNE;
      }
    } else {
      new_universe_size.min_y = (s->universe_size->max_y + s->universe_size->min_y) / 2.0;
      if (body->x <= (s->universe_size->max_x + s->universe_size->min_x) / 2.0) {
        new_universe_size.max_x = (s->universe_size->max_x + s->universe_size->min_x) / 2.0;
        quadrant = &s->childTopSW;
      } else {
        new_universe_size.min_x = (s->universe_size->max_x + s->universe_size->min_x) / 2.0;
        quadrant = &s->childTopSE;
      }
    }
  } else {
    new_universe_size.min_z = (s->universe_size->max_z + s->universe_size->min_z) / 2.0;
    if (body->y <= (s->universe_size->max_y + s->universe_size->min_y) / 2.0) {
      new_universe_size.max_y = (s->universe_size->max_y + s->universe_size->min_y) / 2.0;
      if (body->x <= (s->universe_size->max_x + s->universe_size->min_x) / 2.0) {
        new_universe_size.max_x = (s->universe_size->max_x + s->universe_size->min_x) / 2.0;
        quadrant = &s->childBottomNW;
      } else {
        new_universe_size.min_x = (s->universe_size->max_x + s->universe_size->min_x) / 2.0;
        quadrant = &s->childBottomNE;
      }
    } else {
      new_universe_size.min_y = (s->universe_size->max_y + s->universe_size->min_y) / 2.0;
      if (body->x <= (s->universe_size->max_x + s->universe_size->min_x) / 2.0) {
        new_universe_size.max_x = (s->universe_size->max_x + s->universe_size->min_x) / 2.0;
        quadrant = &s->childBottomSW;
      } else {
        new_universe_size.min_x = (s->universe_size->max_x + s->universe_size->min_x) / 2.0;
        quadrant = &s->childBottomSE;
      }
    }
  }
  if (*quadrant == NULL) {
    Subnode new_subnode = newSubnode(&new_universe_size);
    *quadrant = &new_subnode;
  }

  return quadrant;
}

void computeMass(Subnode *s) {
  if (s->node_count == 1) {
    s->centerOfMass[0] = s->value->x;
    s->centerOfMass[1] = s->value->y;
    s->centerOfMass[2] = s->value->z;
    s->mass = s->value->mass;
  } else {
    s->mass = 0.0;
    s->centerOfMass[0] = 0.0;
    s->centerOfMass[1] = 0.0;
    s->centerOfMass[2] = 0.0;
    Subnode *childs[8] = {s->childTopNE, s->childTopNW, s->childTopSE, s->childTopSW, s->childBottomNE, s->childBottomNW, s->childBottomSE, s->childBottomSW};
    for (size_t i = 0; i < 8; i++) {
      computeMass(childs[0]);
      s->mass += childs[0]->value->mass;
      s->centerOfMass[0] += childs[0]->value->x;
      s->centerOfMass[1] += childs[0]->value->y;
      s->centerOfMass[2] += childs[0]->value->z;
    }
    s->centerOfMass[0] /= s->mass;
    s->centerOfMass[1] /= s->mass;
    s->centerOfMass[2] /= s->mass;
  }
}

void computeForceFromTree(Body *object, Subnode *s, double fvec[3]) {
  if (s->node_count == 1) {
    computeForce(*object, *s->value, fvec);
  } else {
    double delta = 0.5;
    double radius = sqrt(pow(object->x - s->value->x, 2) + pow(object->y - s->value->y, 2) + pow(object->z - s->value->z, 2));
    double height = s->universe_size->max_x - s->universe_size->min_x;
    if (height/radius < delta) {
      computeForce(*object, *s->value, fvec);
    } else {
      Subnode *childs[8] = {s->childTopNE, s->childTopNW, s->childTopSE, s->childTopSW, s->childBottomNE, s->childBottomNW, s->childBottomSE, s->childBottomSW};
      for (size_t i = 0; i < 8; i++) {
        double fsubvec[3];
        computeForceFromTree(object, childs[i], fsubvec);
        fvec[0] += fsubvec[0];
        fvec[1] += fsubvec[1];
        fvec[2] += fsubvec[2];
      }
    }
  }
}
