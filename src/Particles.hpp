#ifndef PARTICLE_LIFE_PARTICLES_H
#define PARTICLE_LIFE_PARTICLES_H

#include "Particle.hpp"
#include <array>
#include <sys/types.h>
#include <vector>

class Particles {
public:
  std::array<Particle, numParticles> m_particles;

public:
  Particles(float, float);
  void Update(std::vector<Vector3f> &lines);
};

#endif // PARTICLE_LIFE_PARTICLES_H
