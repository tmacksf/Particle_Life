//
// Created by Thomas Mack on 18/02/2023.
//

#ifndef PARTICLE_LIFE_DEFINITIONS_H
#define PARTICLE_LIFE_DEFINITIONS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <array>
#include <cmath>
#include <random>
#include <ctime>
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>


enum Color : int {
    one,
    two,
    three,
    four,
    five
};
constexpr uint numColors = 5;

constexpr Color addColor(Color c) {
    switch(c){
        case one : return two;
        case two : return three;
        case three : return four;
        case four : return five;
        case five : return one;
    }
}

constexpr float ColorArray[5][3] = {
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f}
};

constexpr uint particleSize = 2;
constexpr float interactionDistance = 50;
constexpr int numParticles = 500;
constexpr float maxVelocity = 5.0f;
constexpr float maxVelocityNegative = maxVelocity*-1;
constexpr float screenWidth = 1920.0f;
constexpr float screenHeight = 1080.0f;

// Takes the distance and returns the value that the particle should be modified by
float inline distanceOnVelocity(float distance) {
    return ((distance-10)*(distance-10))/100;
}

#endif //PARTICLE_LIFE_DEFINITIONS_H
