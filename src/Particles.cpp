#include "Particles.h"

void Particles::Update() {
    const std::array p_copy = m_particles;
    // todo implement threaded for loop (already safe as it is using p_copy which is const and immutable)
    #pragma omp simd
    for (Particle &p : m_particles) {
        float accelerationX = 0;
        float accelerationY = 0;
        for (Particle interactingWith : p_copy) {
            if (p.getId() == interactingWith.getId()) continue;
            float xDist = interactingWith.getX() - p.getX();
            float yDist = interactingWith.getY() - p.getY();
            float dist = sqrt(xDist*xDist + yDist*yDist);
            if (dist == 0) { // avoiding divide by zero NaN
                // TODO make this more elegant
                accelerationX += p.interactionWith(interactingWith.getColor(), 0.001f, 0.001f);
                accelerationY += p.interactionWith(interactingWith.getColor(), 0.001f, 0.001f);
            }
            else if (dist < interactionDistance) {
                accelerationX += p.interactionWith(interactingWith.getColor(), dist, xDist);
                accelerationY += p.interactionWith(interactingWith.getColor(), dist, yDist);
            }
        }
        p.updateVelocity(accelerationX, accelerationY);
        p.updatePosition();
    }
}

Particles::Particles() {
    std::random_device os_seed;
    const uint_least32_t seed = os_seed();
    std::mt19937 generator(seed);

    std::uniform_int_distribution<uint32_t> velocityGeneration(0, 2*maxVelocity);
    std::uniform_int_distribution<uint32_t> yPosition(0, screenHeight);
    std::uniform_int_distribution<uint32_t> xPosition(0, screenWidth);

    // even color spread
    int particlesPerColor = numParticles/numColors;
    Color colorIndex = one;
    int temp = particlesPerColor;
    for (int i = 0; i < numParticles; i++) {
        auto initialX = (float)xPosition(generator);
        auto initialY = (float)yPosition(generator);
        float initialXVelocity = (float)velocityGeneration(generator) - maxVelocity;
        float initialYVelocity = (float)velocityGeneration(generator) - maxVelocity;
        m_particles[i] = Particle(i+1, colorIndex, initialX, initialY, initialXVelocity, initialYVelocity);
        temp--;

        if (!temp) {
            colorIndex = addColor(colorIndex);
            temp = particlesPerColor;
        }
    }
}
