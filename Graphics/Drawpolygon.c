#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
  float x, y;
} Vertex;

Vertex vertices[MAX_VERTICES];
int vertexCount = 0;

void drawPolygon() {
  if (vertexCount < 3) return;
  glBegin(GL_POLYGON);
  for (int i = 0; i < vertexCount; i++) {
    glVertex2f(vertices[i].x, vertices[i].y);
  }
  glEnd();
}

void fillPolygon() {
  // Basic scan-line algorithm
  for (int i = 0; i < vertexCount; i++) {
    int next = (i + 1) % vertexCount;
    if (vertices[i].y > vertices[next].y) {
      Vertex temp = vertices[i];
      vertices[i] = vertices[next];
      vertices[next] = temp;
    }
  }

  for (float y = vertices[0].y; y <= vertices[vertexCount - 1].y; y++) {
    float x_min = 10000, x_max = -10000;
    for (int i = 0; i < vertexCount; i++) {
      int next = (i + 1) % vertexCount;
      if (y >= vertices[i].y && y < vertices[next].y) {
        float x = vertices[i].x + (y - vertices[i].y) *
                                      (vertices[next].x - vertices[i].x) /
                                      (vertices[next].y - vertices[i].y);
        if (x < x_min) x_min = x;
        if (x > x_max) x_max = x;
      }
    }

    if (x_min < x_max) {
      glBegin(GL_LINES);
      glVertex2f(x_min, y);
      glVertex2f(x_max, y);
      glEnd();
    }
  }
}

void printEdgeTable() {
  printf("Edge Table:\n");
  for (int i = 0; i < vertexCount; i++) {
    int next = (i + 1) % vertexCount;
    float deltaX = vertices[next].x - vertices[i].x;
    float deltaY = vertices[next].y - vertices[i].y;
    float slope_inv =
        (deltaY != 0) ? deltaX / deltaY : 0; // Avoid division by zero

    printf("Edge %d: From (%.2f, %.2f) to (%.2f, %.2f), Slope Inverse: %.2f\n",
           i, vertices[i].x, vertices[i].y, vertices[next].x, vertices[next].y,
           slope_inv);
  }
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    if (vertexCount < MAX_VERTICES) {
      double xpos, ypos;
      glfwGetCursorPos(window, &xpos, &ypos);
      vertices[vertexCount].x = xpos / 400.0 - 1.0; // Normalize to [-1, 1]
      vertices[vertexCount].y = 1.0 - ypos / 300;   // Normalize to [-1, 1]

      // Print the position of the vertex in console
      printf("Vertex %d: (%.2f, %.2f) in pixels: (%.2f, %.2f)\n", vertexCount,
             vertices[vertexCount].x, vertices[vertexCount].y, xpos,
             600 - ypos);

      vertexCount++;
      glClear(GL_COLOR_BUFFER_BIT);
      drawPolygon();
      glFlush();
    }
  } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
    glClear(GL_COLOR_BUFFER_BIT);
    fillPolygon();
    printEdgeTable();
    glFlush();
  }
}

int main() {
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return -1;
  }

  GLFWwindow *window = glfwCreateWindow(800, 600, "Draw Polygons", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon();
    glFlush();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
