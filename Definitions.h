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
constexpr int numColors = 5;

constexpr Color addColor(Color c) {
    switch(c){
        case one : return two;
        case two : return three;
        case three : return four;
        case four : return five;
        case five : return one;
    }
}

//int particleColors[] = {0x51};

constexpr int particleSize = 2;
constexpr float interactionDistance = 10;
constexpr int numParticles = 200;
constexpr int maxVelocity = 50;
constexpr float screenWidth = 1280.0f;
constexpr float screenHeight = 720.0f;

// Takes the distance and returns the value that the particle should be modified by
float inline distanceOnVelocity(float distance) {
    return ((distance-10)*(distance-10))/100;
}

#endif //PARTICLE_LIFE_DEFINITIONS_H
