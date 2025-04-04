#include "Particles.hpp"
#include "Definitions.hpp"
#include "Quad.hpp"
#include <cstdio>
#include <random>

void Particles::Update(std::vector<Vec3> &lines) {
  auto t = new QuadTree(Square({0.0f, 0.0f}, {screenWidth, screenHeight}));
  for (ulong i = 0; i < m_particles.size(); i++) {
    t->insert(0, &m_particles[i], lines);
    // m_particles[i].addGravity();
  }

  for (Particle &p : m_particles) {
    float accelerationX = 0;
    float accelerationY = 0;

    constexpr float d = interactionDistance;
    Square s = Square({p.getPos().x - d, p.getPos().y - d},
                      {p.getPos().x + d, p.getPos().y + d});
    auto possible_interactions = std::vector<Particle *>();
    t->queryRange(possible_interactions, s);

    for (Particle *p_2 : possible_interactions) {
      if (p.Id() == p_2->Id())
        continue;
      p.interacts(p_2);
    }

    for (Particle *p_2 : possible_interactions) {
      if (p_2->Id() <= p.Id())
        continue;
      p.collide(p_2);
    }
  }

  for (Particle &p : m_particles) {
    p.update();
    p.edges();
  }

  // std::cout << "Comparisons: " << cmps
  //           << " Old cmps: " << numParticles * numParticles << std::endl;

  t->tear_down();
}

Particles::Particles(float w, float h) {
  std::random_device os_seed;
  const uint_least32_t seed = os_seed();
  std::mt19937 generator(seed);

  std::uniform_int_distribution<uint32_t> velocityGeneration(0,
                                                             2 * maxVelocity);
  std::uniform_int_distribution<uint32_t> xPosition(0, screenWidth);
  std::uniform_int_distribution<uint32_t> yPosition(0, screenHeight);

  // even color spread
  int particlesPerColor = numParticles / numColors;
  Color colorIndex = one;
  int temp = particlesPerColor;
  for (ulong i = 0; i < numParticles; i++) {
    float initialX = (float)xPosition(generator);
    float initialY = (float)yPosition(generator);
    float initialXVelocity = (float)velocityGeneration(generator) - maxVelocity;
    float initialYVelocity = (float)velocityGeneration(generator) - maxVelocity;
    m_particles[i] =
        Particle(i + 1, colorIndex, initialX, initialY, particleRadius,
                 initialXVelocity, initialYVelocity);
    // temp--;

    // if (!temp) {
    colorIndex = addColor(colorIndex);
    //   temp = particlesPerColor;
    // }
  }
}
