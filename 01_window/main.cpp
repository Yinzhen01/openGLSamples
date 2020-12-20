#include <iostream>
#include <GL/glut.h>

void Init()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Render()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

  glutInitWindowSize(300, 300);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("testWindow");

  Init();

  glutDisplayFunc(Render);
  
  glutMainLoop();
}
