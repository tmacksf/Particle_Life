//
// Created by Thomas Mack on 18/02/2023.
//

#ifndef PARTICLE_LIFE_DEFINITIONS_H
#define PARTICLE_LIFE_DEFINITIONS_H
#define MAXIMUM_VELOCITY = 50

#include <cstdlib>
#include <array>
#include <cmath>

enum Color : int {
    one,
    two,
    three,
    four,
    five
};

//int particleColors[] = {0x51};

constexpr int particleSize = 2;
constexpr float interactionDistance = 10;
constexpr int numParticles = 200;

// Takes the distance and returns the value that the particle should be modified by
float inline distanceOnVelocity(float distance) {
    return ((distance-10)*(distance-10))/100;
}

#endif //PARTICLE_LIFE_DEFINITIONS_H
