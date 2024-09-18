#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

// Global variable to store GLFW window
GLFWwindow *window;

// Initialize FreeGLUT
void initFreeGLUT() {
  // Initialize FreeGLUT
  int argc = 0;
  glutInit(&argc, NULL);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutCreateWindow("FreeGLUT Window");

  // Set up FreeGLUT display function
  glutDisplayFunc([]() {
    // Clear the screen with a color
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a simple triangle
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.5f, -0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    // Swap buffers
    glutSwapBuffers();
  });

  // Set up FreeGLUT idle function
  glutIdleFunc([]() {
    // Redraw
    glutPostRedisplay();
  });
}

// GLFW callback for window size changes
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // Set the viewport size
  glViewport(0, 0, width, height);
}

// Initialize GLEW
void initGLEW() {
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
    exit(-1);
  }
}

int main(void) {
  // Initialize GLFW
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return -1;
  }

  // Set OpenGL version to 3.3 (you can adjust this if needed)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a GLFW window and context
  window = glfwCreateWindow(800, 600, "GLFW and FreeGLUT Example with GLEW",
                            NULL, NULL);
  if (!window) {
    fprintf(stderr, "Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  initGLEW();

  // Set GLFW callback for window size changes
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Initialize FreeGLUT
  initFreeGLUT();

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    // Poll for and process events
    glfwPollEvents();

    // FreeGLUT rendering
    glutMainLoopEvent();
  }

  // Terminate GLFW
  glfwTerminate();
  return 0;
}

// clang-format off
/**
 * Should open two windows because I have got both GLFW and FreeGLUT (I guess).
 * * g++ -IC:/ProgramData/mingw64/mingw64/include -IC:/ProgramData/mingw64/mingw64/include/GLFW -LC:/ProgramData/mingw64/mingw64/lib -o f 6ACG.cpp -lglfw3 -lglew32 -lopengl32 -lgdi32 -lglu32 -lfreeglut
 * ^^ Master command I'll say. Remove -lfreeglut 
 */