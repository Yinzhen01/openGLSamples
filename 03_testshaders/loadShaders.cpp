#include "loadShaders.h"

#include <iostream>
#include <cassert>
#include <vector>

#include "readAsciiFile.h"

using namespace std;

static void attachShader2Program(GLuint program, ShaderInfo& info)
{
  GLuint shader = glCreateShader(info.type);
  string source = ReadAsciiFile(info.filename); 
  const char* strptr[] = {source.c_str()};
  glShaderSource(shader, 1, strptr, NULL);
  glCompileShader(shader);

  GLint compileStatus;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
  if (!compileStatus)
  {
    GLint len = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

    vector<char> log(len+1);
    glGetShaderInfoLog(shader, len, &len, &log[0]);
    cerr << "shader compile error: " << &log[0] << endl;
    exit(1);
  }

  glAttachShader(program, shader);
  info.shader = shader;
}

template<size_t N>
GLuint loadShaders(std::array<ShaderInfo, N>& infos)
{
  static_assert(N);
  GLuint program = glCreateProgram();
  for (auto& info : infos)
  {
    attachShader2Program(program, info);
  }

  glLinkProgram(program);
  GLint linkStatus;
  glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
  if (!linkStatus)
  {
    GLint len = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

    vector<char> log(len+1);
    glGetProgramInfoLog(program, len, &len, &log[0]);
    cerr << "program link error: " << &log[0] << endl;
    
    for (auto& info : infos)
    {
      glDeleteShader(info.shader);
      info.shader = 0;
    }
    return 0;
  }
  return program;
}
