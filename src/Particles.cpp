#include "Particles.hpp"
#include <random>
#include <vector>

void Particles::Update(void (*draw_ssquare)(float, float, float, float)) {
  for (Particle &p : m_particles) {
    p.setOriginals();
  }
  // TODO: Build out some sort of tree to measure distance and only do
  // calculations on close ones
  for (Particle &p : m_particles) {
    float accelerationX = 0;
    float accelerationY = 0;
    for (const Particle &p2 : m_particles) {
      if (p.getId() == p2.getId())
        continue;
      float xDist = p2.getX_original() - p.getX_original();
      float yDist = p2.getY_original() - p.getY_original();
      float dist = sqrt(xDist * xDist + yDist * yDist);
      if (dist == 0) { // avoiding divide by zero NaN
        accelerationX += p.interactionWith(p2.getColor(), 0.0001f, 0.0001f);
        accelerationY += p.interactionWith(p2.getColor(), 0.0001f, 0.0001f);
      } else if (dist < interactionDistance) {
        accelerationX += p.interactionWith(p2.getColor(), dist, xDist);
        accelerationY += p.interactionWith(p2.getColor(), dist, yDist);
      }
    }
    p.updateVelocity(accelerationX, accelerationY);
    p.updatePosition();
  }
}

// void Particles::Update(void (*draw_square)(float, float, float, float)) {
//   auto p2 = std::vector<Particle *>(m_particles.size());
//   for (int i = 0; i < m_particles.size(); i++) {
//     p2[i] = &m_particles[i];
//   }
//
//   m_tree = QuadTree{};
//   m_tree.Build({{0.0f, 0.0f}, {screenWidth, screenHeight}}, p2, 0,
//   draw_square);
// }

Particles::Particles() {
  std::random_device os_seed;
  const uint_least32_t seed = os_seed();
  std::mt19937 generator(seed);

  std::uniform_int_distribution<uint32_t> velocityGeneration(0,
                                                             2 * maxVelocity);
  std::uniform_int_distribution<uint32_t> yPosition(0, screenHeight);
  std::uniform_int_distribution<uint32_t> xPosition(0, screenWidth);

  m_particles = std::vector<Particle>(numParticles);

  // even color spread
  int particlesPerColor = numParticles / numColors;
  Color colorIndex = one;
  int temp = particlesPerColor;
  for (int i = 0; i < numParticles; i++) {
    auto initialX = (float)xPosition(generator);
    auto initialY = (float)yPosition(generator);
    float initialXVelocity = (float)velocityGeneration(generator) - maxVelocity;
    float initialYVelocity = (float)velocityGeneration(generator) - maxVelocity;
    m_particles[i] = Particle(i + 1, colorIndex, initialX, initialY,
                              initialXVelocity, initialYVelocity);
    temp--;

    if (!temp) {
      colorIndex = addColor(colorIndex);
      temp = particlesPerColor;
    }
  }
}
