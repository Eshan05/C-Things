#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void red();
void green();
void yellow();
void blue();
void purple();
void cyan();
void reset();
void proto();
void printColoredText();
void colorStringAlternate(const char *str, int numColors);

int getCode(int index) { return (index % 7) + 31; }
// Function to convert a single digit to an ANSI color code
int getColorCode(int color) {
  switch(color) {
    case 1: return 31; // Red
    case 2: return 32; // Green
    case 3: return 33; // Yellow
    case 4: return 34; // Blue
    case 5: return 35; // Magenta
    case 6: return 36; // Cyan
    case 7: return 37; // White
    default: return 37;
  }
}

// Function to print each character of a string in specified colors
void colorString(const char *str, long long colors) {
  char colorStr[20];
  snprintf(colorStr, sizeof(colorStr), "%d", colors); // Convert to string
  for(int i = 0; i < strlen(str); i++) {
    // Get the corresponding color code from the digit
    int colorCode = getColorCode(colorStr[i] - '0'); // Convert
    printf("\033[%dm%c\033[0m", colorCode, str[i]);  // Print
  }
}

void loadingAnimation(const char symbol, int totalSteps, int duration) {
  int stepDelay = duration * 100000 / totalSteps;
  for(int i = 0; i <= totalSteps; i++) {
    printf("\r[");

    // Print the filled part of the loading bar with colors
    for(int j = 0; j < i; j++) {
      int colorCode = getColorCode(j);
      printf("\033[%dm%c\033[0m", colorCode, symbol); // Print colored symbol
    }

    for(int j = i; j < totalSteps; j++) printf(" ");
    printf("] %d%%", (i * 100) / totalSteps); // Print percentage
    fflush(stdout);    // Ensure output is printed immediately
    usleep(stepDelay); // Sleep for calculated delay
  }
}

int main() {
  int numColors = 6;
  red();
  printf("Hello, World!\n\n");
  reset();

  // printColoredText();
  const char *text = "\nHello, World!";
  colorString("Hey!", 1234);
  colorStringAlternate(text, numColors);
  loadingAnimation('=', 7, 20);
  return 0;
}

void red() { printf("\033[1;31m"); }
void green() { printf("\033[1;32m"); }
void yellow() { printf("\033[1;33m"); }
void blue() { printf("\033[1;34m"); }
void purple() { printf("\033[1;35m"); }
void cyan() { printf("\033[1;36m"); }
void reset() { printf("\033[0m"); }
void proto() { printf("\033[1;27m"); }

void printColoredText() {
  const char *c[] = { "\033[1;30mThis is gray text.\033[0m\n",
                      "\033[1;31mThis is red text.\033[0m\n",
                      "\033[1;32mThis is green text.\033[0m\n",
                      "\033[1;33mThis is yellow text.\033[0m\n",
                      "\033[1;34mThis is blue text.\033[0m\n",
                      "\033[1;35mThis is magenta text.\033[0m\n",
                      "\033[1;36mThis is cyan text.\033[0m\n",
                      "\033[1;37mThis is white text.\033[0m\n",
                      "\033[1;90mThis is bright gray text.\033[0m\n",
                      "\033[1;91mThis is bright red text.\033[0m\n",
                      "\033[1;92mThis is bright green text.\033[0m\n",
                      "\033[1;93mThis is bright yellow text.\033[0m\n",
                      "\033[1;94mThis is bright blue text.\033[0m\n",
                      "\033[1;95mThis is bright magenta text.\033[0m\n",
                      "\033[1;96mThis is bright cyan text.\033[0m\n",
                      "\033[1;97mThis is bright white text.\033[0m\n" };

  for(int i = 0; i < 16; i++) { printf("%s", c[i]); }
}

void colorStringAlternate(const char *str, int numColors) {
  for(int i = 0; i < strlen(str); i++) {
    // Determine color based on the index and the number of colors
    int colorCode = (i % numColors) + 31; // 31 is the base code for red
    printf("\033[%dm%c\033[0m", colorCode,
           str[i]); // Print the character with color
  }
  printf("\n");
}

/**
 * [1;31m: Red
 * [1;32m: Green
 * [1;33m: Yellow
 * [1;34m: Blue
 * [1;35m: Purple
 * [1;36m: Cyan
 * [1;37m: Gray
 * [1;38m: Gray
 */