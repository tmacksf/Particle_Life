#include "Quad.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

bool QuadTree::insert(int depth, Particle *particle, std::vector<Vec3> &v) {
  if (!boundary.Contains(particle->getPos()))
    return false;

  if (index < cap && northWest == nullptr) {
    points[index] = particle;
    index++;
    return true;
  }

  if (!northWest)
    subDivide(v);

  if (southWest->insert(depth + 1, particle, v))
    return true;
  if (northWest->insert(depth + 1, particle, v))
    return true;
  if (southEast->insert(depth + 1, particle, v))
    return true;
  if (northEast->insert(depth + 1, particle, v))
    return true;

  std::cout << "Should not be here!" << std::endl;
  return false;
}

void QuadTree::subDivide(std::vector<Vec3> &v) {
  float cx = (boundary.high.x + boundary.low.x) / 2;
  float cy = (boundary.high.y + boundary.low.y) / 2;
  southWest = new QuadTree(Square({boundary.low.x, boundary.low.y}, {cx, cy}));
  northWest = new QuadTree(Square({boundary.low.x, cy}, {cx, boundary.high.y}));
  southEast = new QuadTree(Square({cx, boundary.low.y}, {boundary.high.x, cy}));
  northEast =
      new QuadTree(Square({cx, cy}, {boundary.high.x, boundary.high.y}));

  v.push_back({cx, cy, 0.0f});
  v.push_back({boundary.low.x, cy, 0.0f});

  v.push_back({cx, cy, 0.0f});
  v.push_back({cx, boundary.low.y, 0.0f});

  v.push_back({cx, cy, 0.0f});
  v.push_back({cx, boundary.high.y, 0.0f});

  v.push_back({cx, cy, 0.0f});
  v.push_back({boundary.high.x, cy, 0.0f});
}

void QuadTree::helper(QuadTree *q) {
  if (!q) {
    std::cout << "This shouldn't happen" << std::endl;
  }
  if (q->southWest)
    helper(q->southWest);
  if (q->northWest)
    helper(q->northWest);
  if (q->southEast)
    helper(q->southEast);
  if (q->northEast)
    helper(q->northEast);

  delete q;
}

void QuadTree::tear_down() { helper(this); }

void QuadTree::queryRange(std::vector<Particle *> &res, Square s) {
  if (!boundary.Intersects(s)) {
    return;
  }

  for (ulong i = 0; i < points.size(); i++) {
    if (!points[i])
      continue;
    res.push_back(points[i]);
  }

  if (southWest != nullptr)
    southWest->queryRange(res, s);
  if (northWest != nullptr)
    northWest->queryRange(res, s);
  if (southEast != nullptr)
    southEast->queryRange(res, s);
  if (northEast != nullptr)
    northEast->queryRange(res, s);
}

bool testSquare() {
  bool pass = true;

  Square s1 = Square({0, 0}, {100, 100});
  Square s2 = Square({10, 10}, {20, 20});

  pass = s1.Intersects(s2);
  pass = s2.Intersects(s1);

  s2 = Square({90, 90}, {200, 200});
  pass = s1.Intersects(s2);
  pass = s2.Intersects(s1);

  s2 = Square({200, 200}, {201, 201});
  pass = !s1.Intersects(s2);
  pass = !s2.Intersects(s1);

  return pass;
}
