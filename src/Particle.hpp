#ifndef PARTICLE_LIFE_PARTICLE_H
#define PARTICLE_LIFE_PARTICLE_H
#include "Definitions.hpp"
#include <algorithm>

typedef struct xy {
  float x, y;
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
  float m_xPos;
  float m_yPos;
  float m_xVelocity;
  float m_yVelocity;
  Color m_color;

  // We calculat everything using these
  float m_xPos_original;
  float m_yPos_original;

public:
  Particle(int id, Color color, float xPos, float yPos, float xVelocity = 0,
           float yVelocity = 0) {
    m_id = id;
    m_color = color;
    m_xPos = xPos;
    m_yPos = yPos;
    m_xVelocity = xVelocity;
    m_yVelocity = yVelocity;
  }

  Particle() = default;

  static float interaction[5][5];

  inline Color getColor() const { return m_color; }
  inline int getId() const { return m_id; }
  inline float getX() const { return m_xPos; }
  inline float getX_original() const { return m_xPos_original; }
  inline float getY() const { return m_yPos; }
  inline float getY_original() const { return m_xPos_original; }
  inline float getYVelocity() const { return m_yVelocity; }
  inline float getXVelocity() const { return m_xVelocity; }
  void setOriginals() {
    m_xPos_original = m_xPos;
    m_yPos_original = m_yPos;
  }

  static void initInteractions(int numColors);

  void updateVelocity(float accelerationX, float accelerationY) {
    if ((m_yVelocity + accelerationY) < maxVelocity and
        (m_yVelocity + accelerationY) > maxVelocityNegative) {
      m_yVelocity += accelerationY;
    }
    if ((m_xVelocity + accelerationX) < maxVelocity and
        (m_xVelocity + accelerationX) > maxVelocityNegative) {
      m_xVelocity += accelerationX;
    }
  }

  void updatePosition() {
    // checking to see if particle is in the screen
    if ((m_xPos + m_xVelocity) > screenWidth or (m_xPos + m_xVelocity) < 0.0f)
      m_xVelocity *= -1.0f;
    else
      m_xPos += m_xVelocity;
    if ((m_yPos + m_yVelocity) > screenHeight or (m_yPos + m_yVelocity) < 0.0f)
      m_yVelocity *= -1.0f;
    else
      m_yPos += m_yVelocity;
  }

  inline float interactionWith(const Particle *p,
                               const float totalDistance,
                               const float distance) {
    return distanceOnVelocity(distance / totalDistance *
                              Particle::interaction[m_color][p->getColor()]);
  }
};

#endif // PARTICLE_LIFE_PARTICLE_H
