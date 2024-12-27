#include "Engine.hpp"

int main() {
  std::srand(time(nullptr));
  Particles particles{};
  Engine::run(particles);
  return 0;
}
