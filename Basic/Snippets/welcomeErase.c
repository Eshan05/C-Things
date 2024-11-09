#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ESC "\033["

void typewriterEffect(const char *str) {
  while (*str) {
    putchar(*str);
    fflush(stdout);
    usleep(100000); // 0.1 seconds
    str++;          // Move to the next character
  }
}

int main() {
  char name[100];
  printf("Welcome\n");
  printf("Enter your name: ");
  fflush(stdout); // Make sure the prompt is printed immediately

  // Get the user's name as input
  fgets(name, sizeof(name), stdin);

  // Remove trailing newline character
  name[strcspn(name, "\n")] = 0;

  // Move the cursor up to the first line (Considering new line too)
  printf(ESC "2A");

  // Print the "Welcome" part
  printf("Welcome ");
  printf(ESC "0J");
  typewriterEffect(name);
  printf("! Nice to meet you.\n");
  return 0;
}
