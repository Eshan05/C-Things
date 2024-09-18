#include <GLFW/glfw3.h>
#include <stdio.h>

int main() {
  if (!glfwInit()) {
    printf("Failed to initialize GLFW\n");
    return -1;
  }
  printf("GLFW Version: %s\n", glfwGetVersionString());
  glfwTerminate();
  return 0;
}

// clang-format off
// gcc -IC:\ProgramData\mingw64\mingw64\include GLFW.c -o f -LC:\ProgramData\mingw64\mingw64\lib -lfreeglut -lopengl32 -lglu32 -lglfw3 -lgdi32 && .\f.exe