#ifndef PARTICLE_LIFE_DEFINITIONS_H
#define PARTICLE_LIFE_DEFINITIONS_H

#include <cstdlib>
#include <thread>

enum Color : int { one, two, three, four, five };
constexpr uint numColors = 5;

constexpr Color addColor(Color c) {
  switch (c) {
  case one:
    return two;
  case two:
    return three;
  case three:
    return four;
  case four:
    return five;
  case five:
    return one;
  default:
    return one;
  }
}

constexpr float ColorArray[5][3] = {{54.0f, 120.0f, 153.0f},
                                    {222.0f, 100.0f, 73.0f},
                                    {121.0f, 30.0f, 148.0f},
                                    {255.0f, 255.0f, 242.0f},
                                    {65.0f, 211.0f, 189.0f}};

constexpr uint particleSize = 2;
constexpr float interactionDistance = 20;
constexpr int numParticles = 20;
constexpr float maxVelocity = 3.0f;
constexpr float maxVelocityNegative = maxVelocity * -1;
constexpr float screenWidth = 1920.0f;
constexpr float screenHeight = 1080.0f;

const unsigned int maxThreads = std::thread::hardware_concurrency();

// Takes the distance and returns the value that the particle should be modified
// by
float inline distanceOnVelocity(float distance) {
  return ((distance - 10) * (distance - 10)) / 100;
}

#endif // PARTICLE_LIFE_DEFINITIONS_H
