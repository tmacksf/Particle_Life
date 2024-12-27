//
// Created by Thomas Mack on 19/02/2023.
//

#include "Engine.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

void draw_square(float x1, float y1, float x2, float y2) {
  glBegin(GL_LINES);
  glLineWidth(1);
  x1 = (x1 / screenWidth - .5f) * 2.0f;
  x2 = (x2 / screenHeight - .5f) * 2.0f;
  glVertex2f(x1, y1);
  glVertex2f(x1, y2);

  glVertex2f(x1, y1);
  glVertex2f(x2, y1);

  glVertex2f(x2, y1);
  glVertex2f(x2, y2);

  glVertex2f(x1, y2);
  glVertex2f(x2, y2);
  glEnd();
}

void Engine::parseShader(const std::string &filePath, std::string &shader) {
  std::ifstream stream(filePath);
  std::string line;
  std::stringstream ss;
  while (getline(stream, line)) {
    ss << line << "\n";
  }

  shader = ss.str();
}

unsigned int Engine::CreateShader(const std::string &vertexShader,
                                  const std::string &fragmentShader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  assert(vs != 0);
  assert(fs != 0);
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

unsigned int Engine::CompileShader(unsigned int type,
                                   const std::string &source) {
  unsigned int id = glCreateShader(type);
  const char *src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char *message = (char *)alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to compile "
              << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
              << " shader." << std::endl;
    std::cout << message << std::endl;
    glDeleteShader(id);
    return 0;
  }

  return id;
}

int Engine::run(Particles &particles) {
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

  // will have the x,y and r,g,b in this
  const int elementsPerPoint = 2;
  const int rgb = 3;
  float points[numParticles * elementsPerPoint * rgb];
  int index = 0;
  for (Particle p : particles.m_particles) {
    points[index] = (p.getX() / screenWidth - .5f) * 2.0f; // --LUKE
    index++;
    points[index] = (p.getY() / screenHeight - .5f) * 2.0f;
    index++;
    points[index] = ColorArray[p.getColor()][0] / 255.0f;
    index++;
    points[index] = ColorArray[p.getColor()][1] / 255.0f;
    index++;
    points[index] = ColorArray[p.getColor()][2] / 255.0f;
    index++;
  }

  unsigned int buffer;
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER,
               numParticles * elementsPerPoint * rgb * sizeof(float), points,
               GL_DYNAMIC_DRAW);
  // glBufferData(GL_ARRAY_BUFFER, numParticles * elementsPerPoint *
  // sizeof(float), points, GL_DYNAMIC_DRAW);

  // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) *
  // elementsPerPoint, nullptr);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, nullptr);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(elementsPerPoint * sizeof(float)));
  glEnableVertexAttribArray(1);

  std::string vertexShader;
  parseShader("./res/vertex.shader", vertexShader);
  std::string fragmentShader;
  parseShader("./res/fragment.shader", fragmentShader);

  unsigned int shader = CreateShader(vertexShader, fragmentShader);
  glUseProgram(shader);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glEnable(GL_POINTS);
  glPointSize(4);
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    // Render here
    glDrawArrays(GL_POINTS, 0, numParticles * 2);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();

    // Particles updated
    particles.Update(draw_square);
    updateArray(points, particles);
    // std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * numParticles * 2 * rgb,
                    points);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  glDeleteProgram(shader);

  glfwTerminate();
  return 0;
}

void Engine::updateArray(float *points, const Particles &particles) {
  int index = 0;
  for (const Particle &p : particles.m_particles) {
    points[index] = (p.getX() / screenWidth - .5f) * 2.0f; // --LUKE
    index++;
    points[index] = (p.getY() / screenHeight - .5f) * 2.0f;
    index = index + 4;
  }
}
