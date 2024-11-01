#include <stdio.h>

void set_color(int r, int g, int b) { printf("\033[38;2;%d;%d;%dm", r, g, b); }
void reset_color() { printf("\033[0m"); }
void set_bg_color(int r, int g, int b) {
  printf("\033[48;2;%d;%d;%dm", r, g, b);
}

// Function to print a message in the specified RGB color
void print_colored_text(int r, int g, int b, const char *message) {
  set_color(r, g, b);
  printf("%s\n", message);
  reset_color();
}

void print_both_text(int text_r, int text_g, int text_b, int bg_r, int bg_g,
                     int bg_b, const char *message) {
  set_bg_color(bg_r, bg_g, bg_b);
  set_color(text_r, text_g, text_b);
  printf("%s\n", message);
  reset_color();
}

void print_with_background(int bg_r, int bg_g, int bg_b, const char *message) {
  set_bg_color(bg_r, bg_g, bg_b); // Set the desired background color
  printf("%s\n", message);        // Print the message
  reset_color();                  // Reset colors to default
}

int main() {
  // Example usage of print_colored_text
  print_colored_text(255, 0, 0, "This is red text!");       // Red
  print_colored_text(0, 255, 0, "This is green text!");     // Green
  print_colored_text(0, 0, 255, "This is blue text!");      // Blue
  print_colored_text(255, 255, 0, "This is yellow text!");  // Yellow
  print_colored_text(255, 0, 255, "This is magenta text!"); // Magenta
  print_colored_text(0, 255, 255, "This is cyan text!");    // Cyan

  // You can also use custom colors
  print_colored_text(123, 45, 67, "This is a custom color!");
  print_with_background(123, 45, 67, "This text has a custom background!");
  print_both_text(123, 45, 67, 200, 150, 100,
                  "Custom color text on custom background!");

  return 0;
}