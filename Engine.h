//
// Created by Thomas Mack on 19/02/2023.
//

#ifndef PARTICLE_LIFE_ENGINE_H
#define PARTICLE_LIFE_ENGINE_H

#include "Particles.h"

class Engine {

public:
    static void parseShader(const std::string &filePath, std::string &shader);
    static unsigned int CompileShader(unsigned int type, const std::string &source);
    static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
    static int run();
};


#endif //PARTICLE_LIFE_ENGINE_H
