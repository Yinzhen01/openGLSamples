#include <iostream>
#include <vector>

#include "vec3d.h"
#include "loadShaders.h"

using namespace std;

void Init()
{
  vector<Vec3d<float>> points = {
    {0.0f, 0.0f, 0.0f},
    {0.5f, 0.0f, 0.0f},
    {0.0f, 0.5f, 0.0f}
  };  

  GLuint vbo;
  glGenBuffers(1,&vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3d<float>)*points.size(), &points[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  
  vector<ShaderInfo> shaderInfo = {
    {GL_VERTEX_SHADER, "vertex.shader", 0},
    {GL_FRAGMENT_SHADER, "frag.shader", 0}
  };

  GLuint program = loadShaders(shaderInfo);
  glUseProgram(program);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  GLuint colorIndex = glGetUniformLocation(program, "color");
  glUniform4f(colorIndex, 0.0f, 1.0f, 0.0f, 1.0f);
}

void Render()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glutSwapBuffers();
  
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

  glutInitWindowSize(300, 300);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("testWindow");

  GLenum ret = glewInit();
  if (ret != GLEW_OK)
  {
    std::cout << glewGetErrorString(ret) << std::endl;
    return 1;
  }
 
  Init();

  glutDisplayFunc(Render);
  
  glutMainLoop();
  return 0;
}
