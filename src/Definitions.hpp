#ifndef PARTICLE_LIFE_DEFINITIONS_H
#define PARTICLE_LIFE_DEFINITIONS_H

#include <chrono>
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

constexpr float ColorArray[5][3] = {{54.0f, 120.0f, 153.0f}, // Blue
                                    {222.0f, 100.0f, 73.0f}, // Red
                                    {121.0f, 30.0f, 148.0f}, // Purple
                                    {255.0f, 255.0f, 242.0f}, // White
                                    {65.0f, 211.0f, 189.0f}}; // Turquoise

constexpr uint particleRadius = 5;
constexpr uint particleSize = particleRadius * 2;
constexpr float interactionDistance = 50;
constexpr unsigned long numParticles = 2000;
constexpr float maxVelocity = 5.0f;
constexpr float maxVelocityNegative = maxVelocity * -1;
constexpr float screenWidth = 1920.0f;
constexpr float screenHeight = 1080.0f;

const unsigned int maxThreads = std::thread::hardware_concurrency();

inline long timeInMS() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

inline const bool isnan(float v) { return v != v; }

#endif // PARTICLE_LIFE_DEFINITIONS_H
