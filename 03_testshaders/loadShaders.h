#ifndef LOAD_SHADER_H
#define LOAD_SHADER_H

#include <string>
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
struct ShaderInfo
{
  GLenum type;
  std::string filename;
  GLuint shader; 
};

GLuint loadShaders(std::vector<ShaderInfo>& infos);

#endif
