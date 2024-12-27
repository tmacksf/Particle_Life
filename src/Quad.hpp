#ifndef PARTICLE_LIFE_QUAD_H
#define PARTICLE_LIFE_QUAD_H

#include "Particle.hpp"
#include <vector>

const int QuadLimit = 1;

typedef struct q_node {
  std::vector<Particle *> particles;
  struct q_node *nodes[4];
} q_node;

typedef std::pair<std::pair<float, float>, std::pair<float, float>> square;

class QuadTree {
private:
  q_node *nodes;

public:
  q_node *Build(square size, std::vector<Particle *> &particles, int,
                void(float, float, float, float));
  void tear_down();
};

#endif
