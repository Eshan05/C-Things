// clang-format off
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

void checkOpenGL() {
  const GLubyte *version = glGetString(GL_VERSION);
  const GLubyte *renderer = glGetString(GL_RENDERER);
  printf("OpenGL Version: %s\n", version);
  printf("Renderer: %s\n", renderer);
}

void checkFreeGLUT() { printf("FreeGLUT Version: %d\n", glutGet(GLUT_VERSION)); }
void checkGLEW() { printf("GLEW Version: %s\n", glewGetString(GLEW_VERSION)); }
void checkGLFW() { printf("GLFW Version: %s\n", glfwGetVersionString()); }

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Version Checker");
  glewInit();
  checkOpenGL();
  checkFreeGLUT();
  if (!glfwInit()) {
    printf("Failed to initialize GLFW\n");
    return -1;
  }
  GLFWwindow *window = glfwCreateWindow(640, 480, "GLFW Window", NULL, NULL);
  if (!window) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  checkGLEW();
  checkGLFW();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

// gcc -IC:\ProgramData\mingw64\mingw64\include draft.c -o c -LC:\ProgramData\mingw64\mingw64\lib -lfreeglut -lopengl32 -lglu32 -lglew32 -lglfw3 -lgdi32