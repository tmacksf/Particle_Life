//
// Created by Thomas Mack on 18/02/2023.
//

#include "Particles.h"
void Particles::Update() {
    for (Particle p : m_particles) {
        float accelerationX = 0;
        float accelerationY = 0;
        for (Particle interactingWith : m_particles) {
            float xDist = interactingWith.getX() - p.getX();
            float yDist = interactingWith.getX() - p.getY();
            float dist = sqrt(xDist*xDist + yDist*yDist);
            if (dist < interactionDistance) {
                accelerationX += p.interactionWithX(interactingWith.getColor(), dist, xDist);
                accelerationY += p.interactionWithY(interactingWith.getColor(), dist, yDist);
            }
        }
        p.updateVelocity(accelerationX, accelerationY);
        p.updatePosition();
    }
}

void Particles::Start() {

}
