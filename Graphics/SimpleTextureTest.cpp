#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Function prototypes
void processInput(GLFWwindow *window);
void renderTexture();
GLuint createSimpleTexture();

// Global texture ID
GLuint textureID;

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  // Create a windowed mode window and its OpenGL context
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "OpenGL Texture Test", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = true;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  // Set up OpenGL view
  glViewport(0, 0, 800, 600);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);

  // Create a simple texture
  textureID = createSimpleTexture();

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    // Process input
    processInput(window);

    // Clear screen with a light gray color
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render the texture
    renderTexture();

    // Swap front and back buffers
    glfwSwapBuffers(window);
    // Poll for and process events
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

GLuint createSimpleTexture() {
  GLuint textureID;
  unsigned char textureData[4 * 2 * 2] = {
    255, 0,   0,   255, // Red
    0,   255, 0,   255, // Green
    0,   0,   255, 255, // Blue
    255, 255, 0,   255  // Yellow
  };

  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               textureData);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  return textureID;
}

void renderTexture() {
  glBindTexture(GL_TEXTURE_2D, textureID);

  glEnable(GL_TEXTURE_2D);

  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(0.25f, 0.25f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(0.75f, 0.25f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(0.75f, 0.75f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0.25f, 0.75f);
  glEnd();

  glDisable(GL_TEXTURE_2D);
}
