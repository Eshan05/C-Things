#include <GL/glut.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Element {
  string value;
};

constexpr int MAX_STACK_SIZE = 4;
constexpr int SCREEN_WIDTH = 500;
constexpr int SCREEN_HEIGHT = 500;

vector<Element> stack;
int top = -1;

bool initOpenGL();
void renderStack();
void renderInstructions();
void pushElement();
void popElement();
void render();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

bool initOpenGL() {
  glClearColor(0, 0, 0, 1); // Set the background color to black
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); // Set the viewport
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-250, 250, -250, 250, -100, 100); // Set orthogonal view
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  GLenum error = glGetError();
  return (error == GL_NO_ERROR);
}

void drawBitmapText(const string &text, int x, int y) {
  glRasterPos2f(x, y);
  for (char ch : text) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ch);
  }
}

void pushElement() {
  if (top >= MAX_STACK_SIZE - 1) {
    drawBitmapText("STACK IS FULL", -70, 200);
    glutSwapBuffers();
    Sleep(100);
    return;
  }

  top++;
  string input;
  cout << "\nEnter the Element: ";
  cin >> input;

  if (top < stack.size()) {
    stack[top].value = input;
  } else {
    stack.push_back({ input });
  }
  renderStack();
}

void popElement() {
  if (top < 0) {
    drawBitmapText("STACK IS EMPTY", -70, 200);
    glutSwapBuffers();
    Sleep(1000);
    return;
  }

  cout << "\nElement " << stack[top].value << " is removed from stack\n";
  top--;
  renderStack();
}

void renderStack() {
  glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glPushMatrix();
  glTranslatef(0, -200, 0);

  int yOffset = 0;
  for (int i = 0; i <= top; ++i) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    glVertex2f(-100, yOffset);
    glVertex2f(100, yOffset);
    glVertex2f(100, yOffset + 50);
    glVertex2f(-100, yOffset + 50);
    glEnd();

    drawBitmapText(stack[i].value, -90, yOffset + 10);
    yOffset += 50;
  }

  glPopMatrix();
  glutSwapBuffers();
}

void renderInstructions() {
  glClear(GL_COLOR_BUFFER_BIT);
  drawBitmapText("1. Enter i or I to Push", -70, 160);
  drawBitmapText("2. Enter r or R to Pop", -70, 140);
  drawBitmapText("3. Enter q or Q to Exit", -70, 120);
  glutSwapBuffers();
}

void render() {
  if (top == -1) {
    renderInstructions();
  } else {
    renderStack();
  }
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-250, 250, -250, 250, -100, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'i':
    case 'I': pushElement(); break;
    case 'r':
    case 'R': popElement(); break;
    case 'q':
    case 'Q': exit(0); break;
    default: break;
  }
  render();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutCreateWindow("STACK");

  if (!initOpenGL()) {
    cout << "Error initializing OpenGL" << endl;
    return -1;
  }

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(render);
  glutReshapeFunc(reshape);
  glutMainLoop();

  return 0;
}

/**
 * I to push
 * R to pop
 * Q to exit
 */