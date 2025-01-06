#include "Particles.hpp"
#include "Definitions.hpp"
#include "Quad.hpp"
#include <cstdio>
#include <random>

// void Particles::Update(std::vector<Vector3f> &) {
//   for (Particle &p : m_particles) {
//     p.setOriginals();
//   }
//   for (Particle &p : m_particles) {
//     float startingx = p.getX();
//     float startingy = p.getY();
//     float accelerationX = 0;
//     float accelerationY = 0;
//     for (const Particle &p2 : m_particles) {
//       if (p.getId() == p2.getId())
//         continue;
//       float xDist = p2.getX_original() - startingx;
//       float yDist = p2.getY_original() - startingy;
//       float dist = sqrt(xDist * xDist + yDist * yDist);
//       if (dist == 0) { // avoiding divide by zero NaN
//         accelerationX += p.interactionWith(&p2, 0.0001f, 0.0001f);
//         accelerationY += p.interactionWith(&p2, 0.0001f, 0.0001f);
//       } else if (dist < interactionDistance) {
//         accelerationX += p.interactionWith(&p2, dist, xDist);
//         accelerationY += p.interactionWith(&p2, dist, yDist);
//       }
//     }
//     p.updateVelocity(accelerationX, accelerationY);
//     p.updatePosition();
//   }
// }

void Particles::Update(std::vector<Vector3f> &lines) {
  auto t = new QuadTree(Square({0.0f, 0.0f}, {screenWidth, screenHeight}));

  for (ulong i = 0; i < m_particles.size(); i++) {
    t->insert(0, &m_particles[i], lines);
    m_particles[i].setOriginals();
  }

  unsigned int cmps = 0;

  for (Particle &p : m_particles) {
    float accelerationX = 0;
    float accelerationY = 0;

    auto d = interactionDistance;
    Square s =
        Square({p.getX() - d, p.getY() - d}, {p.getX() + d, p.getY() + d});
    auto possible_interactions = std::vector<Particle *>();
    t->queryRange(possible_interactions, s);

    for (Particle *p_2 : possible_interactions) {
      if (p.getId() == p_2->getId())
        continue;
      float xDist = p_2->getX_original() - p.getX();
      float yDist = p_2->getY_original() - p.getY();
      float dist = sqrt(xDist * xDist + yDist * yDist);
      cmps++;

      if (dist <= particleRadius * 2) {
        // collision
      }

      // if (dist == 0) { // avoiding divide by zero NaN
      //   accelerationX += p.interactionWith(p_2, 0.0001f, 0.0001f);
      //   accelerationY += p.interactionWith(p_2, 0.0001f, 0.0001f);
      // } else if (dist < interactionDistance) {
      //   accelerationX += p.interactionWith(p_2, dist, xDist);
      //   accelerationY += p.interactionWith(p_2, dist, yDist);
      // }
    }

    p.updateVelocity(accelerationX, accelerationY);
    p.updatePosition();
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
  for (int i = 0; i < numParticles; i++) {
    float initialX = (float)xPosition(generator);
    float initialY = (float)yPosition(generator);
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
