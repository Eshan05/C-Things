#include <stdio.h>

int random_number_gen(int min_range, int max_range) {
  static int rand_number = 199198;
  rand_number = ((rand_number * rand_number) / 10) % 9890;
  return rand_number % (max_range + 1 - min_range) + min_range;
}

int main() {
  int ch, cch;
  do {
    printf("Enter 1 for rock, 2 for paper, 3 for scissors\n");
    scanf("%d", &ch);
    cch = random_number_gen(1, 3);
    if (ch == cch) printf("Draw!\n");
    else if (ch == 1 && cch == 2 ||
             ch == 2 && cch == 3 ||
             ch == 3 && cch == 1)
      printf("You win!\n");
    else printf("You lose!\n");
  } while (1);
}