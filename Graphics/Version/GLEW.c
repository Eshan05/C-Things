// clang-format off
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutCreateWindow("GLEW Version Checker");
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    printf("Error initializing GLEW: %s\n", glewGetErrorString(err));
    return -1;
  }
  printf("GLEW Version: %s\n", glewGetString(GLEW_VERSION));
  return 0;
}

// gcc -IC:\ProgramData\mingw64\mingw64\include GLEW.c -o f -LC:\ProgramData\mingw64\mingw64\lib -lfreeglut -lopengl32 -lglu32 -lglew32 && .\f.exe