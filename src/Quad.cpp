#include "Quad.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

q_node *QuadTree::Build(square size, std::vector<Particle *> &particles,
                        int depth,
                        void(draw_square)(float, float, float, float)) {
  auto tree = new q_node{};
  if (particles.size() < QuadLimit ||
      ((size.second.first - size.first.first) / 2 < interactionDistance ||
       (size.second.second - size.first.second) / 2 < interactionDistance)) {
    // we fill the vec with the points and return
    draw_square(size.first.first, size.first.second, size.second.first,
                size.second.second);
    tree->particles = particles;
    return tree;
  }

  // How do we start this
  const float x0 = size.first.first;
  const float y0 = size.first.second;
  const float xmid = (size.first.first + size.second.first) / 2;
  const float ymid = (size.first.second + size.second.second) / 2;
  const float x1 = size.second.first;
  const float y1 = size.second.second;

  square southwest = {{x0, y0}, {xmid, ymid}};
  square northwest = {{x0, ymid}, {xmid, y1}};
  square southeast = {{xmid, y0}, {x1, ymid}};
  square northeast = {{xmid, ymid}, {x1, y1}};

  auto southwest_vec = std::vector<Particle *>{};
  auto northwest_vec = std::vector<Particle *>{};
  auto southeast_vec = std::vector<Particle *>{};
  auto northeast_vec = std::vector<Particle *>{};

  for (int i = 0; i < particles.size(); i++) {
    auto p = particles[i];
    auto p_x = p->getX();
    auto p_y = p->getY();

    if (p_x >= southwest.first.first && p_y >= southwest.first.second &&
        p_x < southwest.second.first && p_y < southwest.second.second) {
      southwest_vec.push_back(p);
    } else if (p_x >= northwest.first.first && p_y >= northwest.first.second &&
               p_x < northwest.second.first && p_y <= northwest.second.second) {
      northwest_vec.push_back(p);
    } else if (p_x >= southeast.first.first && p_y >= southeast.first.second &&
               p_x <= southeast.second.first && p_y < southeast.second.second) {
      southeast_vec.push_back(p);
    } else if (p_x >= northeast.first.first && p_y >= northeast.first.second &&
               p_x <= northeast.second.first &&
               p_y <= northeast.second.second) {
      northeast_vec.push_back(p);
    } else {
      std::cout << "Error, unhandled thing: " << p_x << " " << p_y << std::endl;
    }
  }

  tree->nodes[0] = Build(southwest, southwest_vec, depth + 1, draw_square);
  tree->nodes[0] = Build(northwest, northwest_vec, depth + 1, draw_square);
  tree->nodes[0] = Build(southeast, southeast_vec, depth + 1, draw_square);
  tree->nodes[0] = Build(northeast, northeast_vec, depth + 1, draw_square);
  return tree;
}

void helper(q_node *node) {
  for (int i = 0; i < 4; i++) {
    if (node->nodes[i] != nullptr)
      helper(node->nodes[i]);
  }
  delete node;
}

void QuadTree::tear_down() { helper(nodes); }
