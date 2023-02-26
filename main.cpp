#include <iostream>

#include "Engine.h"

int main() {
    std::srand(time(nullptr));
    Particles particles{};
    particles.Start();
    Engine::run(particles);
    return 0;
}