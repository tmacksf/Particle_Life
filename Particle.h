//
// Created by Thomas Mack on 18/02/2023.
//

#ifndef PARTICLE_LIFE_PARTICLE_H
#define PARTICLE_LIFE_PARTICLE_H
#include "Definitions.h"

class Particle {
private:
    float m_xPos;
    float m_yPos;
    float m_xVelocity;
    float m_yVelocity;
    Color m_color;

public:
    Particle(Color color, float xPos, float yPos, float xVelocity = 0, float yVelocity = 0)  {
        m_color = color;
        m_xPos = xPos;
        m_yPos = yPos;
        m_xVelocity = xVelocity;
        m_yVelocity = yVelocity;
    }

    Particle() = default;

    static float interaction[5][5];

    void setColor(Color c) {m_color = c;}
    Color getColor() {return m_color;}

    void setX(float x) {m_xPos = x;}
    float getX() const {return m_xPos;}
    void setY(float y) {m_yPos = y;}
    float getY() const {return m_yPos;}
    float getYVelocity() const {return m_yVelocity;}
    void setYVelocity(float y_vel) {m_yVelocity = y_vel;}
    float getXVelocity() const {return m_xVelocity;}
    void setXVelocity(float x_vel) {m_xVelocity = x_vel;}

    static void initInteractions(int numColors);

    void updateVelocity(const float accelerationX, const float accelerationY) {
        if ((m_yVelocity + m_xVelocity) < maxVelocity) {
            m_yVelocity += accelerationY;
             m_xVelocity += accelerationX;
        }
    }

    void updatePosition() {
        // checking to see if particle is in the screen
        if ((m_xPos + m_xVelocity) > screenWidth or (m_xPos + m_xVelocity) < 0.0f) {
            m_xVelocity *= -1.0f;
        }
        else {
            m_xPos += m_xVelocity;
        }
        if ((m_yPos + m_yVelocity) > screenHeight or (m_yPos + m_yVelocity) < 0.0f) {
            m_yVelocity = -1.0f;
        }
        else {
            m_yPos += m_yVelocity;
        }
    }

    float interactionWithX(const Color &interactionWith, const float &distance, const float &xDistance);
    float interactionWithY(const Color &interactionWith, const float &distance, const float &yDistance);
};

#endif //PARTICLE_LIFE_PARTICLE_H
