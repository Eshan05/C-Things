// clang-format off

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

// clang-format on
// Your OpenGL code here
void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  glVertex2f(-0.5f, -0.5f);
  glVertex2f(0.5f, -0.5f);
  glVertex2f(0.0f, 0.5f);
  glEnd();
  glutSwapBuffers();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Triangle");
  glewInit(); // Initialize GLEW
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}

/**
 * g++ -IC:\ProgramData\mingw64\mingw64\include triangle.cpp -o triangle
 * -LC:\ProgramData\mingw64\mingw64\lib -lfreeglut -lopengl32 -lglu32 -lglew32
 */