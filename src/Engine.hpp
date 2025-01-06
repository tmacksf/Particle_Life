//
// Created by Thomas Mack on 19/02/2023.
//

#ifndef PARTICLE_LIFE_ENGINE_H
#define PARTICLE_LIFE_ENGINE_H

#include "Particles.hpp"

class Engine {
private:
  unsigned int setupGlBuffer(void *buffer);

  std::vector<unsigned int> VAOs;
  std::vector<unsigned int> VBOs;

public:
  Engine(float w, float h) {
    VAOs = std::vector<unsigned int>();
    VBOs = std::vector<unsigned int>();
  }
  int run(Particles particles);
  static void updateArray(Vector3f *points, const Particles &);
};

// unsigned int Engine::setupGlBuffer(void *buffer, , , unsigned int size) {
//   unsigned int VAO, VBO;
//   glGenVertexArrays(1, &VAO);
//   glGenBuffers(1, &VBO);
//
//   glBindVertexArray(VAO);
//
//   glBindBuffer(GL_ARRAY_BUFFER, VBO);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
//
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
//   nullptr); glEnableVertexAttribArray(0); glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//   VAOs.push_back(VAO);
//   VBOs.push_back(VBO);
//   glBindVertexArray(0);
//
//   return VAOs.size() - 1;
// }

#endif // PARTICLE_LIFE_ENGINE_H
