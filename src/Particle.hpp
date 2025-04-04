#ifndef PARTICLE_LIFE_PARTICLE_H
#define PARTICLE_LIFE_PARTICLE_H
#include "Definitions.hpp"
#include "Vec.hpp"
#include <cmath>
#include <csignal>
#include <cstdio>
#include <iostream>

class Particle {
private:
  int m_id;
  Vec2 m_pos;
  Vec2 m_vel;
  Color m_color;
  float m_radius;
  float m_mass;
  Vec2 m_acceleration;

public:
  static constexpr float restitution = 1.0f; // Coefficient of restitution

  Particle(int id, Color color, float xPos, float yPos, float radius,
           float xVelocity = 0, float yVelocity = 0) {
    m_id = id;
    m_color = color;
    m_pos = Vec2(xPos, yPos);
    m_vel = Vec2(xVelocity, yVelocity);
    m_radius = radius;
    m_mass = 1.0f;
    m_acceleration = Vec2();
  }

  Particle() = default;

  static float interaction[5][5];

  inline Color getColor() const { return m_color; }
  inline int Id() const { return m_id; }
  inline Vec2 getPos() const { return m_pos; }
  inline Vec2 getVelocity() const { return m_vel; }
  inline void setVel(Vec2 v) { m_vel = v; }

  static void initInteractions(int numColors);

  void update();
  void edges();

  void interacts(const Particle *p);

  void updateVelocity(float accelerationX, float accelerationY) {
    m_vel.y += accelerationY;
    m_vel.x += accelerationX;

    if ((m_vel.y + accelerationY) > maxVelocity)
      m_vel.y = maxVelocity;

    if ((m_vel.y + accelerationY) < maxVelocityNegative)
      m_vel.y = maxVelocityNegative;

    if ((m_vel.x + accelerationX) > maxVelocity)
      m_vel.x = maxVelocity;

    if ((m_vel.x + accelerationX) < maxVelocityNegative)
      m_vel.x = maxVelocityNegative;
  }

  void collide(Particle *p) {
    Vec2 impactVector = p->m_pos.sub(m_pos);
    float d = impactVector.mag();

    if (d > (m_radius + p->m_radius)) {
      return;
    }
    float overlap = d - (m_radius + p->m_radius);
    Vec2 dir = impactVector.setmag(overlap * 0.5);
    m_pos = m_pos.add(dir);
    p->m_pos = p->m_pos.sub(dir);
    d = m_radius + p->m_radius;
    impactVector = impactVector.setmag(d);

    float m_sum = p->m_mass + m_mass;
    Vec2 velDiff = p->m_vel.sub(m_vel);
    // Particle A
    float num = 2.0 * velDiff.dot(impactVector);
    float den = m_sum * d * d;
    if (den == 0.0) {
      den = almostZero;
    }
    Vec2 deltaVa = impactVector.multiply(p->m_mass * num / den);
    m_vel = m_vel.add(deltaVa);
    // Particle B
    Vec2 deltaVb = impactVector.multiply(m_mass * -num / den);
    p->m_vel = p->m_vel.add(deltaVb);
  }

  inline void addGravity() {
    const float pxPerM = 50;
    const float fps = 60;
    m_vel.y -= 9.8 / (fps * fps) * pxPerM;
  }

  inline bool checkNan(bool frontdetection) {
    bool res = false;
    if (m_pos.isNan()) {
      std::cout << "pos" << std::endl;
      res = true;
    }
    if (m_vel.isNan()) {
      std::cout << "vel" << std::endl;
      res = true;
    }
    if (m_radius != m_radius) {
      std::cout << "radius" << std::endl;
      res = true;
    }
    if (m_mass != m_mass) {
      std::cout << "mass" << std::endl;
      res = true;
    }
    if (m_acceleration.isNan()) {
      std::cout << "Acceleration nan" << std::endl;
      res = true;
    }

    if (res) {
      if (frontdetection) {
        std::cout << "Front detection" << std::endl;
      } else {
        std::cout << "Back detection" << std::endl;
      }
      exit(0);
    }
    return res;
  }
};

#endif // PARTICLE_LIFE_PARTICLE_H
