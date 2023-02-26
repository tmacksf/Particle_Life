//
// Created by Thomas Mack on 18/02/2023.
//

#include "Particle.h"

float Particle::interaction[5][5] ={{1,-1,1,1,0},{1,1,0,-1,-1},{1,1,1,-1,0},{-1,-1,-1,1,0},{1,1,0,-1,0}};

float Particle::interactionWith(const Color &interactionWith, const float &totalDistance, const float &distance) {
    return distanceOnVelocity(distance)*distance/totalDistance * Particle::interaction[m_color][interactionWith];
}

void Particle::initInteractions(int colorNum) {
    for (int i = 0; i < colorNum; i++) {
        for (int j = 0; j < colorNum; j++){
            interaction[i][j] = 0;
        }
    }
}
