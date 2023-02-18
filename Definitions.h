//
// Created by Thomas Mack on 18/02/2023.
//

#ifndef PARTICLE_LIFE_DEFINITIONS_H
#define PARTICLE_LIFE_DEFINITIONS_H

#include <cstdlib>
#include <array>

enum Color : int {
    one,
    two,
    three,
    four,
    five
};

int colorHex[] = {};

const int particleSize = 2;
const float interactionDistance = 10;
const int numParticles = 200;

// Takes the distance and returns the value that the particle should be modified by
float inline distanceOnVelocity(float distance) {
    return ((distance-10)*(distance-10))/100;
}

#endif //PARTICLE_LIFE_DEFINITIONS_H
