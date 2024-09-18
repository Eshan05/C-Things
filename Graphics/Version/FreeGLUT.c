#include <GL/freeglut.h>
#include <stdio.h>

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutCreateWindow("FreeGLUT Version Checker");
  printf("FreeGLUT Version: %d\n", glutGet(GLUT_VERSION));
  return 0;
}

// clang-format off
// gcc -IC:\ProgramData\mingw64\mingw64\include FreeGLUT.c -o -LC:\ProgramData\mingw64\mingw64\lib -lfreeglut -lopengl32 -lglu32 && .\f.exe