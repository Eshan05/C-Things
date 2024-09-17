#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

constexpr int WIDTH = 768;
constexpr int HEIGHT = 768;
constexpr double EPSILON = 1e-7;

struct Point {
  double x;
  double y;
};

std::vector<Point> generateKochSnowflake(const std::vector<Point> &points,
                                         int depth) {
  std::vector<Point> new_points;
  for (size_t i = 0; i < points.size(); ++i) {
    const Point &p1 = points[i];
    const Point &p2 = points[(i + 1) % points.size()];

    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;

    Point p3{ p1.x + dx / 3.0, p1.y + dy / 3.0 };
    Point p4{ p1.x + 2.0 * dx / 3.0, p1.y + 2.0 * dy / 3.0 };

    double nx = p4.x - p3.x;
    double ny = p4.y - p3.y;

    Point p5{ p3.x + (nx - ny * std::sqrt(3.0)) / 2.0,
              p3.y + (ny + nx * std::sqrt(3.0)) / 2.0 };

    new_points.push_back(p1);
    new_points.push_back(p3);
    new_points.push_back(p5);
    new_points.push_back(p4);
  }
  return new_points;
}

void renderKochSnowflake(const std::vector<Point> &points) {
  glBegin(GL_LINES);
  for (size_t i = 0; i < points.size(); ++i) {
    glVertex2d(points[i].x, points[i].y);
    glVertex2d(points[(i + 1) % points.size()].x,
               points[(i + 1) % points.size()].y);
  }
  glEnd();
}

int main(int argc, char *argv[]) {
  int max_depth = 1;
  if (argc > 1) { max_depth = std::stoi(argv[1]); }

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
  }

  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "Koch Snowflake", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glOrtho(0, WIDTH, 0, HEIGHT, -1.0, 1.0);

  double side_length = (HEIGHT * 3.0 / 2.0) / std::sqrt(3.0);
  double width_offset = (WIDTH - side_length) / 2.0;

  std::vector<Point> initial_points = { { width_offset, HEIGHT / 4.0 },
                                        { WIDTH - width_offset, HEIGHT / 4.0 },
                                        { WIDTH / 2, HEIGHT } };

  std::vector<Point> points = initial_points;

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 0.0f);

    auto start = std::chrono::high_resolution_clock::now();

    for (int d = 0; d < max_depth; ++d) {
      points = generateKochSnowflake(points, d);
    }

    renderKochSnowflake(points);

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(
                     end - start)
                     .count()
              << "\n";

    glfwSwapBuffers(window);
    glfwPollEvents();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
