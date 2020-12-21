#ifndef LOAD_SHADER_H
#define LOAD_SHADER_H

#include <string>
#include <array>
#include <GL/glew.h>
#include <GL/glut.h>
struct ShaderInfo
{
  GLenum type;
  std::string filename;
  GLuint shader; 
};

template<size_t N>
GLuint loadShaders(std::array<ShaderInfo, N>& infos);

#endif
