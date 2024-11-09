#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 50
#define MAX_TRIES       6

const char *words[] = {
  "python", "computer", "programming",
  "algorithm", "hangman", "developer"
};

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void drawHangman(int wrongGuesses) {
  switch (wrongGuesses) {
    case 0:
      printf("\n+---+\n");
      printf("    |\n");
      printf("    |\n");
      printf("    |\n");
      printf("   ===\n");
      break;
    case 1:
      printf("\n+---+\n");
      printf("O   |\n");
      printf("    |\n");
      printf("    |\n");
      printf("   ===\n");
      break;
    case 2:
      printf("\n+---+\n");
      printf("O   |\n");
      printf("|   |\n");
      printf("    |\n");
      printf("   ===\n");
      break;
    case 3:
      printf("\n+---+\n");
      printf(" O  |\n");
      printf("/|  |\n");
      printf("    |\n");
      printf("   ===\n");
      break;
    case 4:
      printf("\n+---+\n");
      printf(" O  |\n");
      printf("/|\\ |\n");
      printf("    |\n");
      printf("   ===\n");
      break;
    case 5:
      printf("\n+---+\n");
      printf(" O  |\n");
      printf("/|\\ |\n");
      printf("/   |\n");
      printf("   ===\n");
      break;
    case 6:
      printf("\n+---+\n");
      printf(" O  |\n");
      printf("/|\\ |\n");
      printf("/ \\ |\n");
      printf("   ===\n");
      break;
  }
}

int main() {
  char word[MAX_WORD_LENGTH];
  char guessedWord[MAX_WORD_LENGTH];
  char guessedLetters[26] = { 0 };
  int wordLength, wrongGuesses = 0, correctGuesses = 0;
  char guess;

  // Seed random number generator
  srand(time(NULL));
  strcpy(word, words[rand() % (sizeof(words) / sizeof(words[0]))]);
  wordLength = strlen(word);

  // Initialize guessed word with underscores
  for (int i = 0; i < wordLength; i++) { guessedWord[i] = '_'; }
  guessedWord[wordLength] = '\0';

  while (wrongGuesses < MAX_TRIES) {
    clearScreen();
    drawHangman(wrongGuesses);
    printf("\nWord: ");
    for (int i = 0; i < wordLength; i++) {
      printf("%c ", guessedWord[i]);
    }

    printf("\n\nEnter a letter: ");
    scanf(" %c", &guess);
    guess = tolower(guess);

    // Check if letter already guessed
    if (strchr(guessedLetters, guess)) {
      printf("You already guessed that letter!\n");
      continue;
    }

    guessedLetters[strlen(guessedLetters)] = guess;

    // Check if guess is correct
    int found = 0;
    for (int i = 0; i < wordLength; i++) {
      if (word[i] == guess) {
        guessedWord[i] = guess;
        found = 1;
        correctGuesses++;
      }
    }

    if (!found) wrongGuesses++;
    // Check win/lose conditions
    if (strcmp(word, guessedWord) == 0) {
      clearScreen();
      printf("Congratulations! You guessed the word: %s\n", word);
      break;
    }

    if (wrongGuesses == MAX_TRIES) {
      clearScreen();
      drawHangman(wrongGuesses);
      printf("Game Over! The word was: %s\n", word);
      break;
    }
  }

  return 0;
}
