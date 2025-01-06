#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <iostream>
#include <string>

class Shader {
private:
  int m_id;

  unsigned int CreateShader(const std::string &vertexShader,
                            const std::string &fragmentShader);
  void parseShader(const std::string &filePath, std::string &shader);
  unsigned int CompileShader(unsigned int type, const std::string &source);

public:
  Shader(std::string v, std::string f) {
    std::string vertex;
    std::string frag;

    parseShader(v, vertex);
    parseShader(f, frag);

    m_id = CreateShader(vertex, frag);
    std::cout << "Shader id: " << m_id << std::endl;
  }
  void Enable() { glUseProgram(m_id); }
  void setFloat2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
  }
  void Delete() { glDeleteProgram(m_id); }
};

#endif
