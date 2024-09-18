#include <GL/freeglut.h>
#include <stdio.h>
#include <string.h>

typedef enum { OPTION_NONE, OPTION_1, OPTION_2 } MenuOption;

MenuOption currentOption = OPTION_NONE;
int menuOpen = 0; // Using int for boolean representation

void drawString(float x, float y, const char *text) {
  glRasterPos2f(x, y);
  for (const char *c = text; *c != '\0'; ++c) {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
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
        menuOpen = 0;        // Close the menu
        glutPostRedisplay(); // Redraw window
      }
      break;

    case '\r': // ENTER key
      if (menuOpen) {
        switch (currentOption) {
          case OPTION_1: printf("Option 1 selected\n"); break;
          case OPTION_2: printf("Option 2 selected\n"); break;
          default: printf("No option selected\n"); break;
        }
        menuOpen = 0;        // Close the menu
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
 * `m` to open menu
 * ENTER to select option
 * Arrow keys to navigate
 * ESC to close
 */
