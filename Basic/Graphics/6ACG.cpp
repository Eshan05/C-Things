#include <GL/glut.h>
#include <iostream>
#include <string>

enum MenuOption { OPTION_NONE, OPTION_1, OPTION_2 };

MenuOption currentOption = OPTION_NONE;
bool menuOpen = false;

void drawString(float x, float y, const std::string &text) {
  glRasterPos2f(x, y);
  for (char c : text) {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
  }
}

void Draw() {
  glClear(GL_COLOR_BUFFER_BIT);

  if (menuOpen) {
    // Draw the menu
    glColor3f(1, 1, 1); // Text color
    float x = -0.8f;
    float y = 0.7f;

    // Draw menu title
    drawString(x, y, "Menu:");
    y -= 0.1f;

    // Draw menu options
    drawString(x, y, (currentOption == OPTION_1 ? "> Option 1" : "  Option 1"));
    y -= 0.1f;
    drawString(x, y, (currentOption == OPTION_2 ? "> Option 2" : "  Option 2"));
    y -= 0.1f;
    drawString(x, y, "Press ENTER to select, ESC to close");
  }

  glFlush();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'm':
      menuOpen = !menuOpen;        // Toggle menu visibility
      currentOption = OPTION_NONE; // Reset selection
      glutPostRedisplay();         // Redraw window
      break;

    case 27: // ESC key
      if (menuOpen) {
        menuOpen = false;
        glutPostRedisplay(); // Redraw window
      }
      break;

    case '\r': // ENTER key
      if (menuOpen) {
        switch (currentOption) {
          case OPTION_1: std::cout << "Option 1 selected\n"; break;
          case OPTION_2: std::cout << "Option 2 selected\n"; break;
          default: std::cout << "No option selected\n"; break;
        }
        menuOpen = false;    // Close the menu
        glutPostRedisplay(); // Redraw window
      }
      break;
  }
}

void specialKeyboard(int key, int x, int y) {
  if (menuOpen) {
    switch (key) {
      case GLUT_KEY_UP:
        currentOption = (currentOption == OPTION_1) ? OPTION_NONE : OPTION_1;
        glutPostRedisplay(); // Redraw window
        break;

      case GLUT_KEY_DOWN:
        currentOption = (currentOption == OPTION_2) ? OPTION_NONE : OPTION_2;
        glutPostRedisplay(); // Redraw window
        break;
    }
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Keyboard Menu Test");

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glutDisplayFunc(Draw);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeyboard);

  glutMainLoop();
  return 0;
}

/**
 * For some reason right click doesn't make any menu appears nor does any other
 * mouse buttons. `m` to open menu ENTER to select option Arrow keys to navigate
 */