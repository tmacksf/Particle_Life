#ifndef PARTICLE_LIFE_QUAD_H
#define PARTICLE_LIFE_QUAD_H

#include "Particle.hpp"
#include <array>
#include <vector>

class QuadTree {
private:
  Square boundary;
  QuadTree *southWest;
  QuadTree *northWest;
  QuadTree *southEast;
  QuadTree *northEast;

  static constexpr unsigned int cap = 2;

  std::array<Particle *, cap> points;
  unsigned int index = 0;

  void subDivide(std::vector<Vector3f> &);

  void helper(QuadTree *q);

public:
  QuadTree(Square b) {
    boundary = b;

    southWest = nullptr;
    northWest = nullptr;
    southEast = nullptr;
    northEast = nullptr;

    for (ulong i = 0; i < points.size(); i++) {
      points[i] = nullptr;
    }
  }
  bool insert(int, Particle *, std::vector<Vector3f> &);
  void tear_down(); // Fully destroys the object including (this)
  void queryRange(std::vector<Particle *> &, Square);
};

#endif
