#include "Particle.hpp"
#include "Definitions.hpp"
#include <cstdio>

float Particle::interaction[5][5] = {{1, -1, 0, -1, 0},
                                     {1, 0, 0, -1, 0},
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

void Particle::update() {
  m_vel = m_vel.add(m_acceleration);
  if (m_vel.x > maxVelocity) {
    m_vel.x = maxVelocity;
  } else if (m_vel.x < maxVelocityNegative) {
    m_vel.x = maxVelocityNegative;
  }
  if (m_vel.y > maxVelocity) {
    m_vel.y = maxVelocity;
  } else if (m_vel.y < maxVelocityNegative) {
    m_vel.y = maxVelocityNegative;
  }

  m_pos = m_pos.add(m_vel);
  m_acceleration = Vec2();
}

void Particle::edges() {
  if (m_pos.x > screenWidth - m_radius) {
    m_pos.x = screenWidth - m_radius;
    m_vel.x = m_vel.x * -1;
  } else if (m_pos.x < m_radius) {
    m_pos.x = m_radius;
    m_vel.x = m_vel.x * -1;
  }

  if (m_pos.y > screenHeight - m_radius) {
    m_pos.y = screenHeight - m_radius;
    m_vel.y = m_vel.y * -1;
  } else if (m_pos.y < m_radius) {
    m_pos.y = m_radius;
    m_vel.y = m_vel.y * -1;
  }
}

void Particle::interacts(const Particle *p) {
  checkNan(true);
  Vec2 dist = p->m_pos.sub(m_pos);
  float d = dist.mag();
  if (d > interactionDistance) {
    return;
  }
  if (interaction[m_color][p->m_color] == 0.0f) {
    return;
  }
  float towards = interaction[m_color][p->m_color] * 0.1;
  // Vec2 pull = dist.setmag(towards / d);
  if (d == 0) {
    d = almostZero;
  }
  Vec2 pull = dist.multiply(towards / d);
  m_vel = m_vel.add(pull);
  checkNan(false);
}
