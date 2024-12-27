#ifndef PARTICLE_LIFE_PARTICLES_H
#define PARTICLE_LIFE_PARTICLES_H

#include "Particle.hpp"
#include "Quad.hpp"
#include <sys/types.h>
#include <vector>

class Particles {
public:
  std::vector<Particle> m_particles{};

public:
  Particles();
  void Update(void(float, float, float, float));

private:
  QuadTree m_tree;
};

#endif // PARTICLE_LIFE_PARTICLES_H
