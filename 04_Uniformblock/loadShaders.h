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
};

struct UniformBlockItem
{
  std::string itemName;
  GLuint itemIndex;
  GLuint itemSize;
};

struct UniformBlock
{
  std::string blockName;
  GLuint blockIndex;
  GLuint blockSize;

  std::vector<UniformBlockItem> items;
  
  UniformBlock(std::string blockName, GLuint blockIndex, GLuint blockSize) 
    : blockName(blockName), blockIndex(blockIndex), blockSize(blockSize) {}
};

struct UniformFunc
{
  void operator() (GLuint index, float value)
  {
    glUniform1f(index, value);
  }

  void operator() (GLuint index, float value1, float value2)
  {
    glUniform2f(index, value1, value2);
  }
 
  void operator() (GLuint index, float value1, float value2, float value3)
  {
    glUniform3f(index, value1, value2, value3);
  }

  void operator() (GLuint index, float value1, float value2, float value3, float value4)
  {
    glUniform4f(index, value1, value2, value3, value4);
  }

};

class Shader
{
public:
  Shader(GLenum type, std::string filename);
  
  GLuint ShaderIndex() const {return index;}
  GLenum ShaderType() const {return type;}

private:
  GLuint index;
  GLenum type;
  std::string filename;
};

template<typename datatyep>
void getArgsItems(std::vector<datatyep>& strs)
{
}

template<typename datatype>
void getArgsItems(std::vector<datatype>& items, datatype first, datatype... args)
{
  items.push_back(first);
}


class ShadersProgram
{
public:
  ShadersProgram(const std::vector<ShaderInfo>& infos);
  ~ShadersProgram();

  GLuint ProgramIndex() const {return index;}

  template<int dim, typename... Args>
  void linkUniformValues(std::string varName, Args... args);

  template<int dim, typename... Args>
  void updateUniformValues(std::string varName, Args... args);

  void linkUniformBlock(std::string blockName, std::string... args);


private:
  GLuint index;
  std::vector<Shader> shaders;
  std::vector<std::pair<std::string, GLuint>> uniformVars;
  std::vector<UniformBlock> uniformBlocks;
};

template<int dim, typename... Args>
void ShadersProgram::linkUniformValues(std::string varName, Args... args)
{
  static_assert(sizeof...(args) == dim); 
  GLuint varIndex = glGetUniformLocation(index, varName.c_str());
  UniformFunc()(varIndex, std::forward<Args>(args)...);
  uniformVars.push_back(std::make_pair(varName, varIndex));
}

template<int dim, typename... Args>
void ShadersProgram::updateUniformValues(std::string varName, Args... args)
{
  static_assert(sizeof...(args) == dim); 
  for (auto& var : uniformVars)
  {
    if (var.first != varName) continue;
    UniformFunc()(var.second, std::forward<Args>(args)...);
  }
}



#endif
