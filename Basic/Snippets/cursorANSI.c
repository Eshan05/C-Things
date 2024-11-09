#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ES "\033["

void moveToHome() {
  printf(ES "H"); // Moves cursor to home position (0,0)
  printf("Cursor moved to home position.\n");
}

void moveToLineCol(int line, int col) {
  printf(ES "%d;%dH", line, col); // Moves cursor to specific line and column
  printf("Cursor moved to line %d, column %d.\n", line, col);
}

void moveCursorUp(int n) {
  printf(ES "%dA", n); // Moves cursor up N lines
  printf("Cursor moved %d lines up.\n", n);
}

void moveCursorDown(int n) {
  printf(ES "%dB", n); // Moves cursor down N lines
  printf("Cursor moved %d lines down.\n", n);
}

void moveCursorRight(int n) {
  printf(ES "%dC", n); // Moves cursor right N columns
  printf("Cursor moved %d columns to the right.\n", n);
}

void moveCursorLeft(int n) {
  printf(ES "%dD", n); // Moves cursor left N columns
  printf("Cursor moved %d columns to the left.\n", n);
}

void moveToNextLine(int n) {
  printf(ES "%dE", n); // Beginning of next line: N lines down
  printf("Cursor moved to next line %d lines down.\n", n);
}

void moveToPreviousLine(int n) {
  printf(ES "%dF", n); // Beginning of previous line: N lines up
  printf("Cursor moved to previous line %d lines up.\n", n);
}

void moveToColumn(int col) {
  printf(ES "%dG", col); // Moves cursor to specific column (same line)
  printf("Cursor moved to column %d.\n", col);
}

void requestCursorPosition() {
  printf(ES "6n"); // Request current cursor position
  printf("Requested cursor position.\n");
  sleep(1); // Allow time for terminal to respond (simulated)
  printf(ES "[%d;%dR\n", 10, 20); // Simulating a response of row 10, col 20
}

void saveCursorPosition() {
  printf(ES "7"); // Save cursor position (DEC)
  printf("Cursor position saved.\n");
}

void restoreCursorPosition() {
  printf(ES "8"); // Restore cursor position (DEC)
  printf("Cursor position restored.\n");
}

void saveCursorPositionSCO() {
  printf(ES "s"); // Save cursor position (SCO)
  printf("Cursor position saved (SCO).\n");
}

void restoreCursorPositionSCO() {
  printf(ES "u"); // Restore cursor position (SCO)
  printf("Cursor position restored (SCO).\n");
}

void clearScreen() {
  printf(ES "2J"); // Clear the entire screen
  printf("Screen cleared.\n");
}

void printMenu() {
  printf("\nCursor Control ESape Sequences Menu:\n");
  printf("1. Move cursor to home position\n");
  printf("2. Move cursor to specific line and column\n");
  printf("3. Move cursor up\n");
  printf("4. Move cursor down\n");
  printf("5. Move cursor right\n");
  printf("6. Move cursor left\n");
  printf("7. Move cursor to next line\n");
  printf("8. Move cursor to previous line\n");
  printf("9. Move cursor to specific column\n");
  printf("10. Request cursor position\n");
  printf("11. Save cursor position (DEC)\n");
  printf("12. Restore cursor position (DEC)\n");
  printf("13. Save cursor position (SCO)\n");
  printf("14. Restore cursor position (SCO)\n");
  printf("15. Clear the screen\n");
  printf("16. Exit\n");
}

int main() {
  int choice;
  int line, col, n;

  while (1) {
    system("cls");

    printMenu();
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1: moveToHome(); break;
      case 2:
        printf("Enter line and column: ");
        scanf("%d %d", &line, &col);
        moveToLineCol(line, col);
        break;
      case 3:
        printf("Enter number of lines to move up: ");
        scanf("%d", &n);
        moveCursorUp(n);
        break;
      case 4:
        printf("Enter number of lines to move down: ");
        scanf("%d", &n);
        moveCursorDown(n);
        break;
      case 5:
        printf("Enter number of columns to move right: ");
        scanf("%d", &n);
        moveCursorRight(n);
        break;
      case 6:
        printf("Enter number of columns to move left: ");
        scanf("%d", &n);
        moveCursorLeft(n);
        break;
      case 7:
        printf("Enter number of lines to move down: ");
        scanf("%d", &n);
        moveToNextLine(n);
        break;
      case 8:
        printf("Enter number of lines to move up: ");
        scanf("%d", &n);
        moveToPreviousLine(n);
        break;
      case 9:
        printf("Enter column to move to: ");
        scanf("%d", &col);
        moveToColumn(col);
        break;
      case 10: requestCursorPosition(); break;
      case 11: saveCursorPosition(); break;
      case 12: restoreCursorPosition(); break;
      case 13: saveCursorPositionSCO(); break;
      case 14: restoreCursorPositionSCO(); break;
      case 15: clearScreen(); break;
      case 16: printf("Exiting...\n"); return 0;
      default: printf("Invalid choice. Please try again.\n");
    }

    sleep(2);
  }

  return 0;
}
