//
// Created by Thomas Mack on 18/02/2023.
//

#include "Particle.h"

void Particle::initInteractions(int numColors) {
    for (int colorClass = 0; colorClass < numColors; colorClass++) {
        for (int interactionWith = 0; interactionWith < numColors; interactionWith ++) {

        }
    }
}


float Particle::interactionWithX(const Color &interactionWith, const float &distance, const float &xDistance) {\
    return distanceOnVelocity(distance)*xDistance/distance * interaction[m_color][interactionWith];
}

float Particle::interactionWithY(const Color &interactionWith, const float &distance, const float &yDistance) {
    return distanceOnVelocity(distance)*yDistance/distance * interaction[m_color][interactionWith];
}