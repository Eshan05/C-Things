#include <GL/freeglut.h>
#include <iostream>
#include <string>

enum MenuState { MENU_MAIN, MENU_SUB, MENU_NONE };

MenuState currentState = MENU_NONE;
int currentOption = 0;
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
    glColor3f(1, 1, 1); // White color for text

    float x = -0.8f;
    float y = 0.7f;

    switch (currentState) {
      case MENU_MAIN:
        drawString(x, y, "Main Menu:");
        y -= 0.1f;
        drawString(x, y, (currentOption == 0 ? "> Option 1" : "  Option 1"));
        y -= 0.1f;
        drawString(x, y, (currentOption == 1 ? "> Option 2" : "  Option 2"));
        y -= 0.1f;
        drawString(x, y, "Press ENTER to select, ESC to close");
        break;

      case MENU_SUB:
        drawString(x, y, "Sub Menu:");
        y -= 0.1f;
        drawString(x, y,
                   (currentOption == 0 ? "> Sub Option 1" : "  Sub Option 1"));
        y -= 0.1f;
        drawString(x, y,
                   (currentOption == 1 ? "> Sub Option 2" : "  Sub Option 2"));
        y -= 0.1f;
        drawString(x, y, "Press ENTER to select, ESC to go back");
        break;

      default: break;
    }
  }

  glFlush();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'm':
      menuOpen = !menuOpen;     // Toggle menu visibility
      currentState = MENU_MAIN; // Reset to main menu
      currentOption = 0;        // Reset selection
      glutPostRedisplay();      // Redraw window
      break;

    case 27: // ESC key
      if (menuOpen) {
        if (currentState == MENU_SUB) {
          currentState = MENU_MAIN; // Go back to main menu
        } else {
          menuOpen = false; // Close the menu
        }
        glutPostRedisplay(); // Redraw window
      }
      break;

    case '\r': // ENTER key
      if (menuOpen) {
        switch (currentState) {
          case MENU_MAIN:
            if (currentOption == 0) {
              std::cout << "Main Option 1 selected\n";
            } else if (currentOption == 1) {
              currentState = MENU_SUB; // Go to sub menu
              currentOption = 0;       // Reset sub menu option
            }
            break;

          case MENU_SUB:
            if (currentOption == 0) {
              std::cout << "Sub Option 1 selected\n";
            } else if (currentOption == 1) {
              std::cout << "Sub Option 2 selected\n";
            }
            currentState = MENU_MAIN; // Return to main menu
            break;
        }
        glutPostRedisplay(); // Redraw window
      }
      break;
  }
}

void specialKeyboard(int key, int x, int y) {
  if (menuOpen) {
    switch (key) {
      case GLUT_KEY_UP:
        currentOption = (currentOption > 0) ? currentOption - 1 : 0;
        glutPostRedisplay(); // Redraw window
        break;

      case GLUT_KEY_DOWN:
        if (currentState == MENU_MAIN) {
          currentOption = (currentOption < 1) ? currentOption + 1 : 1;
        } else if (currentState == MENU_SUB) {
          currentOption = (currentOption < 1) ? currentOption + 1 : 1;
        }
        glutPostRedisplay(); // Redraw window
        break;
    }
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Nested Menu Test");

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
