#include <GL/glut.h>
#include <stdio.h>

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutCreateWindow("OpenGL Version Checker");
  const GLubyte *version = glGetString(GL_VERSION);
  const GLubyte *renderer = glGetString(GL_RENDERER);
  printf("OpenGL Version: %s\n", version);
  printf("Renderer: %s\n", renderer);
  return 0;
}

// clang-format off
// gcc -IC:\ProgramData\mingw64\mingw64\include OpenGL.c -o f -LC:\ProgramData\mingw64\mingw64\lib -lfreeglut -lopengl32 -lglu32 && .\f.exe