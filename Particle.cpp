//
// Created by Thomas Mack on 18/02/2023.
//

#include "Particle.h"

float Particle::interaction[5][5] ={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};

float Particle::interactionWithX(const Color &interactionWith, const float &distance, const float &xDistance) {
    return distanceOnVelocity(distance)*xDistance/distance * Particle::interaction[m_color][interactionWith];
}

float Particle::interactionWithY(const Color &interactionWith, const float &distance, const float &yDistance) {
    return distanceOnVelocity(distance)*yDistance/distance * Particle::interaction[m_color][interactionWith];
}

void Particle::initInteractions(int colorNum) {
    for (int i = 0; i < colorNum; i++) {
        for (int j = 0; j < colorNum; j++){
            interaction[i][j] = 0;
        }
    }
}
