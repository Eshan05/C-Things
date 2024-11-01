#include <stdio.h>
#include <unistd.h>
void hideCursor() { printf("\033[?25l"); }

void rotatingBarAnimation(int duration) {
  const char *symbols = "|/-\\";
  int len = 4;
  int stepDelay = duration * 1000000 / (20);

  for(int i = 0; i < 20; i++) {
    printf("\r%c", symbols[i % len]);
    fflush(stdout);
    usleep(stepDelay);
  }
  printf("\n");
}

void pulsingDotsAnimation(int duration) {
  int stepDelay = duration * 1000000 / 5;

  for(int i = 0; i < 20; i++) {
    printf("\rLoading");
    for(int j = 0; j < (i % 4); j++) { printf("."); }
    fflush(stdout);
    usleep(stepDelay);
  }
  printf("\n");
}

void snakeLoadingAnimation(int duration, int loops) {
  const char *frames[] = { "[=]",       "[~<     ]", "[~~=    ]", "[~~~<   ]",
                           "[  ~~~= ]", "[   ~~~<]", "[    ~~~]", "[     ~~]",
                           "[~]",       "[ ]" };
  int totalFrames = sizeof(frames) / sizeof(frames[0]);
  int stepDelay = (duration * 1000000) / totalFrames;

  for(int l = 0; l < loops; l++) {
    for(int i = 0; i < totalFrames; i++) {
      printf("\r%s", frames[i]);
      fflush(stdout);
      usleep(stepDelay);
    }
  }
  printf("\n");
}

void blocksLoadingAnimation(int duration, int loops) {
  const char *frames[] = { "▁  ", "▂ ", "▃ ", "▄ ", "▅ ", "▆ ", "▇ ", "█ ",
                           "█ ",  "▇ ", "▆ ", "▅ ", "▄ ", "▃ ", "▂ ", "▁ " };

  int totalFrames = sizeof(frames) / sizeof(frames[0]);
  int stepDelay = (duration * 1000000) / (totalFrames * loops);

  for(int l = 0; l < loops; l++) {
    // Ascending part of the wave
    for(int i = 0; i < totalFrames; i++) {
      for(int j = 0; j < 5; j++) { // Number of blocks
        // Stagger the height of each block
        int heightOffset = j; // Adjust this for different rates
        if(i - heightOffset >= 0) {
          printf("%s", frames[i - heightOffset]);
        } else {
          printf("  "); // Empty space for lower heights
        }
      }
      printf("\r");
      fflush(stdout);
      usleep(stepDelay);
    }
    // Descending part of the wave
    for(int i = totalFrames - 1; i >= 0; i--) {
      for(int j = 0; j < 5; j++) { // Number of blocks
        int heightOffset = j;      // Adjust this for different rates
        if(i + heightOffset < totalFrames) {
          printf("%s", frames[i + heightOffset]);
        } else {
          printf("  "); // Empty space for lower heights
        }
      }
      printf("\r");
      fflush(stdout);
      usleep(stepDelay);
    }
  }
  printf("\n");
}

int main() {
  hideCursor();
  // rotatingBarAnimation(2);
  // pulsingDotsAnimation(2);
  // snakeLoadingAnimation(5, 5);
  blocksLoadingAnimation(3, 3);
  return 0;
}