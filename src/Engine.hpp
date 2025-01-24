//
// Created by Thomas Mack on 19/02/2023.
//

#ifndef PARTICLE_LIFE_ENGINE_H
#define PARTICLE_LIFE_ENGINE_H

#include "Particles.hpp"
#include <iostream>

class Engine {
private:
  unsigned int setupGlBuffer(void *buffer);

  std::vector<unsigned int> VAOs; // Assuming a 1 to 1 mapping of VAO to VBO
  std::vector<unsigned int> VBOs;

  long m_frametimes;
  long m_frameIndex;

  // Take the ms per frame at the end of each frame and outputs when it gets to
  // index frames
  void fps(long t) {
    m_frametimes += t;
    m_frameIndex++;

    if (m_frameIndex >= 60) {
      if (m_frametimes == 0)
        m_frametimes = 1;
      std::cout << "FPS: " << (1000 * m_frameIndex) / m_frametimes << "\n";
      m_frametimes = 0;
      m_frameIndex = 0;
    }
  }

public:
  Engine(float w, float h) {
    VAOs = std::vector<unsigned int>();
    VBOs = std::vector<unsigned int>();

    m_frametimes = 0;
    m_frameIndex = 0;
  }
  int run(Particles particles);
  static void updateArray(Vector3f *points, const Particles &);
};

// unsigned int Engine::setupGlBuffer(void *buffer, , , unsigned int size) {
//   unsigned int VAO, VBO;
//   glGenVertexArrays(1, &VAO);
//   glGenBuffers(1, &VBO);
//
//   glBindVertexArray(VAO);
//
//   glBindBuffer(GL_ARRAY_BUFFER, VBO);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
//
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
//   nullptr); glEnableVertexAttribArray(0); glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//   VAOs.push_back(VAO);
//   VBOs.push_back(VBO);
//   glBindVertexArray(0);
//
//   return VAOs.size() - 1;
// }
//
// int _run() {
//   if (!glfwInit()) {
//     std::cout << "GLFW Window failed" << std::endl;
//     return -1;
//   }
//
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// #ifdef __APPLE__
//   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif
//
//   GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight,
//                                         "Particle Life", nullptr, nullptr);
//   if (!window) {
//     glfwTerminate();
//     return -1;
//   }
//   glfwMakeContextCurrent(window);
//
//   /* Init glew */
//   if (glewInit() != GLEW_OK) {
//     std::cout << "Glew error" << std::endl;
//   }
//   std::cout << glGetString(GL_VERSION) << std::endl;
//
//   glViewport(0, 0, screenWidth, screenHeight);
//   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//   auto shader = Shader("./res/vertex.shader", "./res/fragment.shader");
//
//   float vertices1[] = {-0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.5f,
//   0.0f}; float vertices2[] = {-0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
//   -0.5f, 0.0f};
//
//   unsigned int VAOs[2];
//   unsigned int VBOs[2];
//   /******* What we need for drawing stuff *******/
//   unsigned int VAO, VBO;
//   glGenVertexArrays(1, &VAO);
//   glGenBuffers(1, &VBO);
//
//   glBindVertexArray(VAO);
//
//   glBindBuffer(GL_ARRAY_BUFFER, VBO);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1,
//   GL_STATIC_DRAW);
//
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
//   nullptr); glEnableVertexAttribArray(0); glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//   VAOs[0] = VAO;
//   VBOs[0] = VBO;
//   glBindVertexArray(0);
//   /******* What we need for drawing stuff *******/
//   glGenVertexArrays(1, &VAO);
//   glGenBuffers(1, &VBO);
//
//   glBindVertexArray(VAO);
//
//   glBindBuffer(GL_ARRAY_BUFFER, VBO);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2,
//   GL_DYNAMIC_DRAW);
//
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
//   nullptr); glEnableVertexAttribArray(0); glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//   glBindVertexArray(0);
//   VAOs[1] = VAO;
//   VBOs[1] = VBO;
//
//   while (!glfwWindowShouldClose(window)) {
//     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//     glClear(GL_COLOR_BUFFER_BIT);
//
//     processInput(window);
//
//     shader.Enable();
//     glBindVertexArray(VAOs[0]);
//     glDrawArrays(GL_TRIANGLES, 0, 3);
//     glBindVertexArray(0);
//
//     glBindVertexArray(VAOs[1]);
//     vertices2[0] += 0.05f;
//     if (vertices2[0] > 1)
//       vertices2[0] = -0.5f;
//     vertices2[1] += 0.05f;
//     if (vertices2[1] > 1)
//       vertices2[1] = -0.5f;
//     glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2,
//                  GL_DYNAMIC_DRAW);
//     glDrawArrays(GL_TRIANGLES, 0, 3);
//     glBindVertexArray(0);
//
//     glfwSwapBuffers(window);
//     glfwPollEvents();
//   }
//
//   glfwTerminate();
//   return 0;
// }

#endif // PARTICLE_LIFE_ENGINE_H
