#ifndef PARTICLE_LIFE_PARTICLES_H
#define PARTICLE_LIFE_PARTICLES_H


#include "Particle.h"

class Particles {
public:
    std::array<Particle, numParticles> m_particles{};

public:
    Particles();
    void Update();
    Particle &getIndividual(int index) {
        return m_particles[index];
    }
};

#endif //PARTICLE_LIFE_PARTICLES_H
