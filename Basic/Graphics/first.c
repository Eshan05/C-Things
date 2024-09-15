#include <GL/freeglut.h>

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
  glutCreateWindow("FreeGLUT Example");

  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}

/**
 * Installed it via https://www.transmissionzero.co.uk/software/freeglut-devel/
 * Use x64 and put in lib/ and include/
 * g++ -IC:\ProgramData\mingw64\mingw64\include first.c -o f
 * -LC:\ProgramData\mingw64\mingw64\lib -lfreeglut -lopengl32 -lglu32
 */