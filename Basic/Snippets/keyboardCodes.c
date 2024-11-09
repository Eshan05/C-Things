#include <conio.h>
#include <stdio.h>

// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797#keyboard-strings
void displayKeyCode(char key) {
  switch (key) {
    case 13: // Enter key
      printf("Enter key pressed (Code 13)\n");
      break;
    case 9: // Tab key
      printf("Tab key pressed (Code 9)\n");
      break;
    case 8: // Backspace
      printf("Backspace key pressed (Code 8)\n");
      break;
    case 27: // ESC key
      printf("Escape key pressed (Code 27)\n");
      break;
    default: printf("Key: '%c' Code: %d\n", key, (int)key); break;
  }
}

int main() {
  char key;
  printf("Press any key (ESC to quit):\n");

  while (1) {
    if (_kbhit()) {
      key = _getch();
      if (key == 27) break;
      displayKeyCode(key);
    }
  }

  return 0;
}
