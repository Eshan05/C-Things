#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ES "\033["

void eraseFromCursorToEndOfScreen() {
  printf(ES "0J"); // Erase from the cursor to the end of the screen
  printf("Erased from cursor to the end of the screen.\n");
}

void eraseFromCursorToBeginningOfScreen() {
  printf(ES "1J"); // Erase from the cursor to the beginning of the screen
  printf("Erased from cursor to the beginning of the screen.\n");
}

void eraseEntirESreen() {
  printf(ES "2J"); // Erase the entire screen
  printf("Erased the entire screen.\n");
}

void eraseSavedLines() {
  printf(ES "3J"); // Erase saved lines
  printf("Erased saved lines.\n");
}

void eraseFromCursorToEndOfLine() {
  printf(ES "0K"); // Erase from the cursor to the end of the line
  printf("Erased from cursor to the end of the line.\n");
}

void eraseFromStartOfLineToCursor() {
  printf(ES "1K"); // Erase from the start of the line to the cursor
  printf("Erased from the start of the line to the cursor.\n");
}

void eraseEntireLine() {
  printf(ES "2K"); // Erase the entire line
  printf("Erased the entire line.\n");
}

void printMenu() {
  printf("\nScreen and Line Erasing ESape Sequences Menu:\n");
  printf("1. Erase from cursor to end of screen (ES[0J)\n");
  printf("2. Erase from cursor to beginning of screen (ES[1J)\n");
  printf("3. Erase entire screen (ES[2J)\n");
  printf("4. Erase saved lines (ES[3J)\n");
  printf("5. Erase from cursor to end of line (ES[0K)\n");
  printf("6. Erase from start of line to cursor (ES[1K)\n");
  printf("7. Erase entire line (ES[2K)\n");
  printf("8. Exit\n");
}

int main() {
  int choice;
  while (1) {
    system("cls");
    printMenu();
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1: eraseFromCursorToEndOfScreen(); break;
      case 2: eraseFromCursorToBeginningOfScreen(); break;
      case 3: eraseEntirESreen(); break;
      case 4: eraseSavedLines(); break;
      case 5: eraseFromCursorToEndOfLine(); break;
      case 6: eraseFromStartOfLineToCursor(); break;
      case 7: eraseEntireLine(); break;
      case 8: printf("Exiting...\n"); return 0;
      default: printf("Invalid choice. Please try again.\n");
    }

    sleep(2);
  }

  return 0;
}
