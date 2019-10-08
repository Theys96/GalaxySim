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

Position newPosition() {
  Position pos;
  pos.x = 0.0;
  pos.y = 0.0;
  pos.z = 0.0;
  return pos;
}

Node newNode(Body *body) {
  Node n;
  n.pos = newPosition();
  n.pos.x = body->x;
  n.pos.y = body->y;
  n.pos.z = body->z;
  n.mass = body->mass;
  return n;
}

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
  s.mass = 0.0;
  s.centerOfMass = newPosition();
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
    Node node = newNode(bodies + i);
    insertNode(t.root, &node);
  }
  return t;
}

void insertNode(Subnode *s, Node *node) {
  if (s->node_count > 1) {
    Subnode **quadrant = getQuadrant(s, node);
    insertNode(*quadrant, node);
  } else if (s->node_count == 1) {
    Subnode **quadrant = getQuadrant(s, s->value);
    insertNode(*quadrant, s->value);
    s->value = NULL;

    Subnode **quadrant2 = getQuadrant(s, node);
    insertNode(*quadrant2, node);
  } else {
    s->value = node;
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

Subnode **getQuadrant(Subnode *s, Node *node) {
  Subnode **quadrant = NULL;
  UniverseSize new_universe_size;
  memcpy(&new_universe_size, s->universe_size, sizeof(UniverseSize));
  if (node->pos.z <= (s->universe_size->max_z + s->universe_size->min_z) / 2.0) {
    new_universe_size.max_z = (s->universe_size->max_z + s->universe_size->min_z) / 2.0;
    if (node->pos.y <= (s->universe_size->max_y + s->universe_size->min_y) / 2.0) {
      new_universe_size.max_y = (s->universe_size->max_y + s->universe_size->min_y) / 2.0;
      if (node->pos.x <= (s->universe_size->max_x + s->universe_size->min_x) / 2.0) {
        new_universe_size.max_x = (s->universe_size->max_x + s->universe_size->min_x) / 2.0;
        quadrant = &s->childTopNW;
      } else {
        new_universe_size.min_x = (s->universe_size->max_x + s->universe_size->min_x) / 2.0;
        quadrant = &s->childTopNE;
      }
    } else {
      new_universe_size.min_y = (s->universe_size->max_y + s->universe_size->min_y) / 2.0;
      if (node->pos.x <= (s->universe_size->max_x + s->universe_size->min_x) / 2.0) {
        new_universe_size.max_x = (s->universe_size->max_x + s->universe_size->min_x) / 2.0;
        quadrant = &s->childTopSW;
      } else {
        new_universe_size.min_x = (s->universe_size->max_x + s->universe_size->min_x) / 2.0;
        quadrant = &s->childTopSE;
      }
    }
  } else {
    new_universe_size.min_z = (s->universe_size->max_z + s->universe_size->min_z) / 2.0;
    if (node->pos.y <= (s->universe_size->max_y + s->universe_size->min_y) / 2.0) {
      new_universe_size.max_y = (s->universe_size->max_y + s->universe_size->min_y) / 2.0;
      if (node->pos.x <= (s->universe_size->max_x + s->universe_size->min_x) / 2.0) {
        new_universe_size.max_x = (s->universe_size->max_x + s->universe_size->min_x) / 2.0;
        quadrant = &s->childBottomNW;
      } else {
        new_universe_size.min_x = (s->universe_size->max_x + s->universe_size->min_x) / 2.0;
        quadrant = &s->childBottomNE;
      }
    } else {
      new_universe_size.min_y = (s->universe_size->max_y + s->universe_size->min_y) / 2.0;
      if (node->pos.x <= (s->universe_size->max_x + s->universe_size->min_x) / 2.0) {
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
    s->centerOfMass = s->value->pos;
    s->mass = s->value->mass;
  } else {
    s->mass = 0.0;
    s->centerOfMass = newPosition();
    Subnode *childs[8] = {s->childTopNE, s->childTopNW, s->childTopSE, s->childTopSW, s->childBottomNE, s->childBottomNW, s->childBottomSE, s->childBottomSW};
    for (size_t i = 0; i < 8; i++) {
      computeMass(childs[0]);
      s->mass += childs[0]->value->mass;
      s->centerOfMass.x += childs[0]->value->pos.x;
      s->centerOfMass.y += childs[0]->value->pos.y;
      s->centerOfMass.z += childs[0]->value->pos.z;
    }
    s->centerOfMass.x /= s->mass;
    s->centerOfMass.y /= s->mass;
    s->centerOfMass.z /= s->mass;
  }
}

void computeForceForObject(Body *bodies, int n, Subnode *s) {
  for (int i = 0; i < n; i++) {
    Position f = computeForceFromTree(bodies + i, s->root)
  }
}

void computeForceFromTree(Body *object, Subnode *s, double fvec[3]) {
  double fvec[3];
  if (s->node_count == 1) {
    computeForce(object, s->body, f);
  } else {
    radius = sqrt(pow(object->x - s->body->x, 2) + pow(object->y - s->body->y, 2) + pow(object->z - s->body->z, 2))
    height = s->universe_size->max_x - s->universe_size->min_x;
    if (height/radius < delta) {
      computeForce(object, s->body, f);
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
