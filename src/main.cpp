#include "Engine.hpp"

int main() {
  std::srand(time(nullptr));
  Particles particles(screenWidth, screenHeight);
  Engine e(screenWidth, screenHeight);
  e.run(particles);
  // std::cout << (testSquare() ? "passed" : "failed") << std::endl;
  return 0;
}
