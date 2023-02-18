//
// Created by Thomas Mack on 18/02/2023.
//

#ifndef PARTICLE_LIFE_PARTICLES_H
#define PARTICLE_LIFE_PARTICLES_H


#include "Particle.h"

class Particles {
private:
    std::array<Particle, numParticles> m_particles;

public:
    void Start();
    void Update();
    Particle &getIndividual(int index) {
        return m_particles[index];
    }
};

#endif //PARTICLE_LIFE_PARTICLES_H
