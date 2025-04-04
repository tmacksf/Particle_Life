#ifndef PARTICLE_LIFE_PARTICLES_H
#define PARTICLE_LIFE_PARTICLES_H

#include "Particle.hpp"
#include <array>
#include <vector>

class Particles {
public:
  std::array<Particle, numParticles> m_particles;

public:
  Particles(float, float);
  void Update(std::vector<Vec3> &lines);
};

#endif // PARTICLE_LIFE_PARTICLES_H
