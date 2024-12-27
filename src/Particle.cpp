#include "Particle.hpp"

float Particle::interaction[5][5] = {{1, -1, 0, -1, 0},
                                     {1, 1, 0, -1, 0},
                                     {0, -1, -1, 1, 1},
                                     {0, -1, 1, 0, 1},
                                     {1, -1, -1, -1, 1}};

void Particle::initInteractions(int colorNum) {
  for (int i = 0; i < colorNum; i++) {
    for (int j = 0; j < colorNum; j++) {
      interaction[i][j] = 0;
    }
  }
}
