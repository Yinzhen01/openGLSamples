#include "loadShaders.h"

#include <iostream>
#include <cassert>
#include <vector>

#include "readAsciiFile.h"

using namespace std;

Shader::Shader(GLenum type, string filename)
  : type(type), filename(filename)
{
  index = glCreateShader(type);
  string source = ReadAsciiFile(filename); 
  const char* strptr[] = {source.c_str()};
  glShaderSource(index, 1, strptr, NULL);
  glCompileShader(index);

  GLint compileStatus;
  glGetShaderiv(index, GL_COMPILE_STATUS, &compileStatus);
  if (!compileStatus)
  {
    GLint len = 0;
    glGetShaderiv(index, GL_INFO_LOG_LENGTH, &len);

    vector<char> log(len+1);
    glGetShaderInfoLog(index, len, &len, &log[0]);
    cerr << filename <<": shader compile error: " << &log[0] << endl;
  };
}

ShadersProgram::ShadersProgram(const vector<ShaderInfo>& infos)
{
  index = glCreateProgram();
  for (auto& info : infos)
  {
    Shader shader(info.type, info.filename);
    glAttachShader(index, shader.ShaderIndex());
  }

  glLinkProgram(index);
  GLint linkStatus;
  glGetProgramiv(index, GL_LINK_STATUS, &linkStatus);
  if (!linkStatus)
  {
    GLint len = 0;
    glGetProgramiv(index, GL_INFO_LOG_LENGTH, &len);

    vector<char> log(len+1);
    glGetProgramInfoLog(index, len, &len, &log[0]);
    cerr << "program link error: " << &log[0] << endl;
    
    for (auto& shader:shaders)
    {
      glDeleteShader(shader.ShaderIndex());
    }
  }

}

ShadersProgram::~ShadersProgram()
{
  for (auto& shader:shaders)
  {
    glDeleteShader(shader.ShaderIndex());
  }
}

void ShadersProgram::linkUniformBlock(std::string blockName, std::string... args)
{
  GLuint blockIndex = glGetUniformBlockIndex(index, blockName.c_str());

  GLuint size = 0;
  glGetActiveUniformsiv(index, uniBlock.second, GL_UNIFORM_BLOCK_DATA_SIZE, &size); 
  uniformBlocks.emplace_back(blockName, blockIndex, size);

  vector<string> strs;
  getArgsItems<string>(strs, args);
  
}

void ShadersProgram::linkUniformBlockItem(std::string itemName, std::string... args)
{
  
}


