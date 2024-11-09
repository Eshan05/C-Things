#include <stdio.h>
#include <stdlib.h>

#define ES  "\033["
#define ESC "\033["
#define RES "\033[0m"

void black() { printf("\033[1;30m"); }
void red() { printf("\033[1;31m"); }
void green() { printf("\033[1;32m"); }
void yellow() { printf("\033[1;33m"); }
void blue() { printf("\033[1;34m"); }
void purple() { printf("\033[1;35m"); }
void cyan() { printf("\033[1;36m"); }
void white() { printf("\033[1;37m"); }
void reset() { printf("\033[0m"); }

void printForeground();
void printBackground();
void print256Colors();
void print256Backgrounds();
void printCombinedColors();
void printTextStyles();

int main() {
  // printf(ES "4mHello World" RES ES "1mHello" RES);
  printForeground();
  printBackground();
  printf("You can also use ESC[38;5;{ID}m], with ID from 0 to 255 for "
         "foregrounds\n");
  printf("You can also use ESC[48;5;{ID}m], with ID from 0 to 255 for "
         "foregrounds\n");
  printf("To use RGB Text: ESC[38;2;{r};{g};{b}m\n");
  printf("To use RGB BG: ESC[48;2;{r};{g};{b}m\n");
  printf("To use both: ESC[38;5;{fg_id};48;5;{bg_id}m\n");
  print256Colors();
  print256Backgrounds();
  printCombinedColors(); // \033[38;5;{fg_id};48;5;{bg_id}m
                         // printf("\033[31;1;4mHello\033[0m\n");
                         // printf("\033[2;31;4mHello\033[0m");
                         // printTextStyles();
  printf("You can combine styles as "
         "\033[38;5;242m\<style1>;<style2>;...;<styleN>m\n");
  printf("\033[0mIt should not generate different results in terminals\n\n");
  printf(ESC "1;4mBold and Underlined Text" RES "\n");
  printf(ESC "1;31;44mBold Red Text on Blue Background" RES "\n");
  printf(ESC "1;4;35;42mBold, Underlined, Magenta Text on Green Background" RES
             "\n");
  return 0;
}

void printTextStyles() {
  const char *styleDescriptions[] = {
    "Undefined",               // 0 - (No style, used for reset)
    "Bold",                    // 1
    "Dim",                     // 2
    "Italic",                  // 3
    "Underline",               // 4
    "Blink",                   // 5
    "Rapid Blink",             // 6
    "Reverse",                 // 7
    "Hidden",                  // 8 (Concel)
    "Strike-through",          // 9
    "Reserved",                // 10-19 (Not widely supported or used)
    "Reserved",                // 11
    "Reserved",                // 12
    "Reserved",                // 13
    "Reserved",                // 14
    "Reserved",                // 15
    "Reserved",                // 16
    "Reserved",                // 17
    "Reserved",                // 18
    "Reserved",                // 19
    "Fraktur",                 // 20 (Rarely supported)
    "Double Underline",        // 21
    "Normal",                  // 22 (Reverts intensity or formatting)
    "Not italic, not Fraktur", // 23 (Rarely supported)
    "Underline Off",           // 24
    "Blink Off",               // 25
    "Reserved",                // 26
    "Inverse off",             // 27 (Reverses inverse colors)
    "Reveal",                  // 28 (Concel off)
    "Not crossed out",         // 29
    "Black Color",             // 30
    "Red Color",               // 31
    "Green Color",             // 32
    "Yellow Color",            // 33
    "Blue Color",              // 34
    "Purple Color",            // 35
    "Cyan Color",              // 36
    "White Color",             // 37
    "Custom color",            // 38
    "Default color",           // 39
    "Black BG",                // 40
    "Red BG",                  // 41
    "Green BG",                // 42
    "Yellow BG",               // 43
    "Blue BG",                 // 44
    "Purple BG",               // 45
    "Cyan BG",                 // 46
    "White BG",                // 47
    "Custom BG",               // 48
    "Default BG",              // 49
    "Reserved",                // 50
    "Framed",                  // 51
    "Encircled",               // 52
    "Overlined",               // 53
    "Not framed or encircled", // 54
    "Not overlined",           // 55
  };

  printf("Text Formatting Codes (1-55):\n\n");
  for (int i = 1; i <= 55; i++) {
    printf(ESC "%dm", i);
    printf("Style %2d: %s - ", i, styleDescriptions[i]);
    printf("Text with style %d\033[0m\n", i);
    printf(RES);
  }

  printf("\n");
}

void printCombinedColors() {
  printf("Combined Foreground and Background Colors:\n");
  for (int fg = 0; fg < 10; fg++) {
    for (int bg = 0; bg < 10; bg++) {
      printf(ES "38;5;%d;48;5;%dm%d -%2d\033[0m" RES, fg, bg, fg, bg);

      if ((fg + 1) % 11 == 0 || bg >= 9) {
        printf("\n");
      } else printf(" ");
    }
  }
  printf("\n");
}

void print256Colors() {
  printf("\n256 Colors:\n");
  for (int i = 0; i < 256; i++) {
    printf(ES "38;5;%dm%3d" RES, i, i);
    if ((i + 1) % 16 == 0) {
      printf("\n");
    } else printf(" ");
  }

  printf("\n");
}

void print256Backgrounds() {
  printf("256 Backgrounds:\n");
  for (int i = 0; i < 256; i++) {
    printf(ES "48;5;%dm%3d" RES, i, i);
    if ((i + 1) % 16 == 0) {
      printf("\n");
    } else printf(" ");
  }

  printf("\n");
}

void printBackground() {
  const char *colors[] = { "Black",        "Red",
                           "Green",        "Yellow",
                           "Blue",         "Magenta",
                           "Cyan",         "White",
                           "Bright Black", "Bright Red",
                           "Bright Green", "Bright Yellow",
                           "Bright Blue",  "Bright Magenta",
                           "Bright Cyan",  "Bright White" };

  printf("Background Colors:\n");
  for (int i = 0; i < 8; i++) {
    printf(ESC "%dm%d" ESC "0m: " ESC "%dm%-15s\033[0m ", 40 + i, 40 + i,
           40 + i, colors[i]);
    printf(ESC "%dm%d" ESC "0m: " ESC "%dm%-15s\033[0m\n", 100 + i, 100 + i,
           100 + i, colors[i + 8]);
  }

  printf("\n");
}

void printForeground() {
  const char *colors[] = { "Black",        "Red",
                           "Green",        "Yellow",
                           "Blue",         "Magenta",
                           "Cyan",         "White",
                           "Bright Black", "Bright Red",
                           "Bright Green", "Bright Yellow",
                           "Bright Blue",  "Bright Magenta",
                           "Bright Cyan",  "Bright White" };

  printf("Foreground Colors:\n");
  for (int i = 0; i < 8; i++) {
    // printf(ES "%dm%d" ES "0m: " ES "%dm%-15s " ES "%dm%-15s\n", 30 + i, 30 +
    // i, 30 + i, colors[i], 90 + i, colors[i + 8]);
    printf(ESC "%dm%d" ESC "0m: " ESC "%dm%-15s ", 30 + i, 30 + i, 30 + i,
           colors[i]);
    printf(ESC "%dm%d" ESC "0m: " ESC "%dm%-15s\n", 90 + i, 90 + i, 90 + i,
           colors[i + 8]);
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