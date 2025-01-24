//
// Created by Thomas Mack on 19/02/2023.
//

#include "Engine.hpp"
#include "Definitions.hpp"
#include "Shader.hpp"
#include <GL/glew.h>
// Need to avoid format sorting this
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <ctime>
#include <iostream>
#include <vector>

void fillPoints(Vector3f *points, const Particles &particles) {
  int index = 0;
  for (const auto &p : particles.m_particles) {
    points[index] = Vector3f(p.getPos().x, p.getPos().y, 0.0f);
    index++;
    auto c = p.getColor();
    points[index] =
        Vector3f(ColorArray[c][0] / 255.0f, ColorArray[c][1] / 255.0f,
                 ColorArray[c][2] / 255.0f);
    index++;
  }
}

void normaliseLines(std::vector<Vector3f> &lines) {
  for (auto &l : lines) {
    l.x = (l.x / screenWidth - 0.5f) * 2.0f;
    l.y = (l.y / screenHeight - 0.5f) * 2.0f;
  }
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    std::cout << "Esc" << std::endl;
    glfwSetWindowShouldClose(window, true);
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

int Engine::run(Particles particles) {
  // return _run();
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit()) {
    std::cout << "GLFW Window failed" << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(screenWidth, screenHeight, "Particle Life", nullptr,
                            nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  /* Init glew */
  if (glewInit() != GLEW_OK) {
    std::cout << "Glew error" << std::endl;
  }

  std::cout << glGetString(GL_VERSION) << std::endl;

  // Each particle will have a position and color
  Vector3f Vertices[numParticles * 2];

  fillPoints(Vertices, particles);
  updateArray(Vertices, particles);

  unsigned int VAO;
  unsigned int VBO;
  glGenBuffers(1, &VBO);

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind buffer
  VAOs.push_back(VAO);
  VBOs.push_back(VBO);
  glBindVertexArray(0); // unbind

  std::vector<Vector3f> lines = std::vector<Vector3f>();
  Shader pointsShader =
      Shader("./res/points_vertex.shader", "./res/points_fragment.shader");
  pointsShader.setFloat2("screenSize", screenWidth, screenHeight);

  glPointSize(particleSize);
  std::cout << "Particle size: " << particleSize << " count: " << numParticles
            << std::endl;

  Shader lineShader = Shader("./res/vertex.shader", "./res/fragment.shader");
  glGenBuffers(1, &VBO);

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, lines.size() * sizeof(Vector3f), lines.data(),
               GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  VAOs.push_back(VAO);
  VBOs.push_back(VBO);
  glBindVertexArray(0);

  bool paused = false;

  auto startTime = timeInMS();
  while (!glfwWindowShouldClose(window)) {
    startTime = timeInMS();
    glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    paused = false;
    processInput(window);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
      paused = true;
    }

    if (!paused) {
      // Particles updated
      lines.clear();
      particles.Update(lines);
      updateArray(Vertices, particles);
      normaliseLines(lines);
    }

    // Render
    pointsShader.Enable();
    pointsShader.setFloat2("screenSize", screenWidth, screenHeight);
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_POINTS, 0, numParticles);
    glBindVertexArray(0);

    lineShader.Enable();
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, lines.size() * sizeof(Vector3f), lines.data(),
                 GL_DYNAMIC_DRAW);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_LINES, 0, lines.size());
    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();

    fps(timeInMS() - startTime);
  }

  pointsShader.Delete();

  glfwTerminate();
  return 0;
}

void Engine::updateArray(Vector3f *points, const Particles &particles) {
  int index = 0;
  for (const Particle &p : particles.m_particles) {
    points[index].x = p.getPos().x;
    points[index].y = p.getPos().y;
    index += 2;
  }
}
