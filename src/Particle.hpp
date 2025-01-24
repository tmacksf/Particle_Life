#ifndef PARTICLE_LIFE_PARTICLE_H
#define PARTICLE_LIFE_PARTICLE_H
#include "Definitions.hpp"
#include <algorithm>
#include <cmath>

typedef struct xy {
  float x, y;

  xy subtract(struct xy s) const { return {x - s.x, y - s.y}; }

  xy projection(struct xy s) const {
    float dotProduct = x * s.x + y * s.y;
    float magSquared = s.x * s.x + s.y * s.y;
    if (magSquared == 0) {
      return xy{};
    }
    auto scale = dotProduct / magSquared;
    return s.multiply(scale);
  }

  xy multiply(float scalar) const { return xy{x * scalar, y * scalar}; }

  float distance(xy o) const {
    float dx = o.x - x;
    float dy = o.y - y;
    return sqrt(dx * dx + dy * dy);
  }
} xy;

typedef struct Square {
  xy low, high;

  Square() { low = high = {0, 0}; }
  Square(xy _low, xy _high) {
    low = _low;
    high = _high;
  }

  inline bool Contains(xy p) const {
    return (p.x >= low.x && p.x <= high.x) && (p.y >= low.y && p.y <= high.y);
  }

  bool Intersects(Square &r) const {
    return std::max(r.low.x, low.x) < std::min(r.high.x, high.x) &&
           std::max(r.low.y, low.y) < std::min(r.high.y, high.y);
  }
} Square;

bool testSquare();

class Particle {
private:
  int m_id;
  xy m_pos;
  xy m_vel;
  Color m_color;
  float m_radius;
  float m_mass;

  // We calculat everything using this
  xy m_pos_original;

public:
  static constexpr float restitution = 0.95f; // Coefficient of restitution

  bool isHit(Particle &p);

  Particle(int id, Color color, float xPos, float yPos, float radius,
           float xVelocity = 0, float yVelocity = 0) {
    m_id = id;
    m_color = color;
    m_pos = {.x = xPos, .y = yPos};
    m_vel = {.x = xVelocity, .y = yVelocity};
    m_pos_original = m_pos;
    m_radius = radius;
    m_mass = 1.0f;
  }

  Particle() = default;

  static float interaction[5][5];

  inline Color getColor() const { return m_color; }
  inline int getId() const { return m_id; }
  inline xy getPos() const { return m_pos; }
  inline xy getOriginalPos() const { return m_pos_original; }
  inline xy getVelocity() const { return m_vel; }
  inline void setVel(xy v) { m_vel = v; }
  void setOriginals() { m_pos_original = m_pos; }

  static void initInteractions(int numColors);

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

  void updatePosition() {
    // checking to see if particle is in the screen
    if ((m_pos.x + m_vel.x) > screenWidth or (m_pos.x + m_vel.x) < 0.0f)
      m_vel.x = (-restitution * m_vel.x);
    else
      m_pos.x += m_vel.x;
    if ((m_pos.y + m_vel.y) > screenHeight or (m_pos.y + m_vel.y) < 0.0f)
      m_vel.y = (-restitution * m_vel.y);
    else
      m_pos.y += m_vel.y;
  }

  // inline float interactionWith(const Particle *p, const float totalDistance,
  //                              const float distance) {
  //   return distanceOnVelocity(distance / totalDistance *
  //                             Particle::interaction[m_color][p->getColor()]);
  // }

  inline xy collision(const Particle *p) {
    float sf = ((1.0f + restitution) * p->m_mass) / (p->m_mass + m_mass);
    xy vDiff = m_vel.subtract(p->m_vel);
    xy rDiff = m_pos.subtract(p->m_pos);
    xy proj = vDiff.projection(rDiff);

    return m_vel.subtract(proj.multiply(sf));
  }

  inline void addGravity() {
    const float pxPerM = 50;
    const float fps = 60;
    m_vel.y -= 9.8 / (fps * fps) * pxPerM;
  }
};

#endif // PARTICLE_LIFE_PARTICLE_H
