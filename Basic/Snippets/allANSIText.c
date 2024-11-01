#include <stdio.h>
#include <stdlib.h>

void red();
void green();
void yellow();
void blue();
void purple();
void cyan();
void reset();
void black() { printf("\033[1;30m"); }
void white() { printf("\033[1;37m"); }
void light_red() { printf("\033[0;31m"); }
void light_green() { printf("\033[0;32m"); }
void light_yellow() { printf("\033[0;33m"); }
void light_blue() { printf("\033[0;34m"); }
void light_cyan() { printf("\033[0;36m"); }
void light_purple() { printf("\033[0;35m"); }

void bg_black() { printf("\033[40m"); }
void bg_red() { printf("\033[41m"); }
void bg_green() { printf("\033[42m"); }
void bg_yellow() { printf("\033[43m"); }
void bg_blue() { printf("\033[44m"); }
void bg_cyan() { printf("\033[46m"); }
void bg_purple() { printf("\033[45m"); }
void bg_white() { printf("\033[47m"); }

void bold() { printf("\033[1m"); }
void underline() { printf("\033[4m"); }
void blink() { printf("\033[5m"); }
void reverse() { printf("\033[7m"); }

int main() {
  reset();
  red();
  printf("This is red text.\n");
  green();
  printf("This is green text.\n");
  yellow();
  printf("This is yellow text.\n");
  blue();
  printf("This is blue text.\n");
  cyan();
  printf("This is cyan text.\n");
  purple();
  printf("This is purple text.\n");
  light_red();
  printf("This is light red text.\n");
  light_green();
  printf("This is light green text.\n");
  light_yellow();
  printf("This is light yellow text.\n");
  light_blue();
  printf("This is light blue text.\n");
  light_cyan();
  printf("This is light cyan text.\n");
  light_purple();
  printf("This is light purple text.\n");

  // Using background colors
  bg_black();
  white();
  printf("This is white text on black background.\n");
  bg_red();
  black();
  printf("This is black text on red background.\n");
  bg_green();
  black();
  printf("This is black text on green background.\n");
  bg_yellow();
  black();
  printf("This is black text on yellow background.\n");
  bg_blue();
  white();
  printf("This is white text on blue background.\n");
  bg_cyan();
  black();
  printf("This is black text on cyan background.\n");
  bg_purple();
  white();
  printf("This is white text on purple background.\n");
  bg_white();
  black();
  printf("This is black text on white background.\n");

  // Using text styles
  reset(); // Reset before applying styles
  bold();
  printf("This is bold text.\n");
  reset();
  underline();
  printf("This is underlined text.\n");
  reset();
  blink();
  printf("This is blinking text.\n");
  reset();
  reverse();
  printf("This is reversed text.\n");
  reset();

  // printColoredText();
  return 0;
}

void red() { printf("\033[1;31m"); }
void green() { printf("\033[1;32m"); }
void yellow() { printf("\033[1;33m"); }
void blue() { printf("\033[1;34m"); }
void purple() { printf("\033[1;35m"); }
void cyan() { printf("\033[1;36m"); }
void reset() { printf("\033[0m"); }

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