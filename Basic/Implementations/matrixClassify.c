#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 15
#define MAX_COLS 15
#define NL       printf("\n")

void cls() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void display(int M[MAX_ROWS][MAX_COLS], int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) { printf("%d", M[i][j]); }
    NL;
  }
}

void isScalar(int M[MAX_ROWS][MAX_COLS], int rows, int cols) {
  if (rows != cols) {
    printf("Not a square matrix");
    return;
  }

  int a = M[0][0];
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i == j) {
        if (M[i][j] != a) {
          printf("Not a scalar matrix");
          return;
        }
      } else {
        if (M[i][j] != 0) {
          printf("Not a scalar matrix");
          return;
        }
      }
    }
  }

  printf("Is a scalar matrix");
  return;
}

int main() {
  cls();
  int m[MAX_ROWS][MAX_COLS] = {
    { 5, 1, 0 },
    { 0, 5, 0 },
    { 0, 0, 5 }
  };
  display(m, 3, 3);
  isScalar(m, 3, 3);
}