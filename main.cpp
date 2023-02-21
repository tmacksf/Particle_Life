#include <iostream>

#include "Engine.h"

int main() {
    std::cout << "Bot" << std::endl;
    std::srand(time(nullptr));
    Engine::run();
    return 0;
}