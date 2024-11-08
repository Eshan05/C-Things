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

void display(int[MAX_ROWS][MAX_COLS], int rows, int cols);
int isSquare(int rows, int cols);
void isScalar(int M[MAX_ROWS][MAX_COLS], int rows, int cols);
void isDiagonal(int M[MAX_ROWS][MAX_COLS], int rows, int cols);
void isIdentity(int M[MAX_ROWS][MAX_COLS], int rows, int cols);
void isSingular(int M[MAX_ROWS][MAX_COLS], int rows, int cols);
void isLower(int M[MAX_ROWS][MAX_COLS], int rows, int cols);
void isUpper(int M[MAX_ROWS][MAX_COLS], int rows, int cols);
void isSymmetric(int M[MAX_ROWS][MAX_COLS], int rows, int cols);
void isAntiSymmetric(int M[MAX_ROWS][MAX_COLS], int rows, int cols);

void getCofactor(int M[MAX_ROWS][MAX_COLS], int temp[MAX_ROWS][MAX_COLS],
                 int rows, int cols, int r, int c);
int determinant(int M[MAX_ROWS][MAX_COLS], int n);

int main() {
  cls();
  int m[MAX_ROWS][MAX_COLS] = {
    { 1, 0, 0 },
    { 0, 1, 0 },
    { 0, 0, 1 }
  };
  display(m, 3, 3);
  isScalar(m, 3, 3);
  isDiagonal(m, 3, 3);
  isIdentity(m, 3, 3);
  isLower(m, 3, 3);
  isUpper(m, 3, 3);
}

void display(int M[MAX_ROWS][MAX_COLS], int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) { printf("%d", M[i][j]); }
    NL;
  }
}

void isScalar(int M[MAX_ROWS][MAX_COLS], int rows, int cols) {
  if (!isSquare(rows, cols)) return;

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

void isDiagonal(int M[MAX_ROWS][MAX_COLS], int rows, int cols) {
  if (!isSquare(rows, cols)) return;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i != j && M[i][j] != 0) {
        printf("Not a diagonal matrix");
        return;
      }
    }
  }
  printf("Is a diagonal matrix");
}

void isIdentity(int M[MAX_ROWS][MAX_COLS], int rows, int cols) {
  if (!isSquare(rows, cols)) return;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if ((i == j && M[i][j] != 1) || (i != j && M[i][j] != 0)) {
        printf("Not an identity matrix\n");
        return;
      }
    }
  }
  printf("Is an identity matrix");
}

void isLower(int M[MAX_ROWS][MAX_COLS], int rows, int cols) {
  if (!isSquare(rows, cols)) return;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i < j && M[i][j] != 0) {
        printf("Not lower triangular");
        return;
      }
    }
  }
  printf("Is a lower triangular matrix");
}

void isUpper(int M[MAX_ROWS][MAX_COLS], int rows, int cols) {
  if (!isSquare(rows, cols)) return;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i > j && M[i][j] != 0) {
        printf("Not lower triangular");
        return;
      }
    }
  }
  printf("Is a upper triangular matrix");
}

void isSingular(int M[MAX_ROWS][MAX_COLS], int rows, int cols) {
  if (!isSquare(rows, cols)) return;

  int det = determinant(M, rows);
  if (det == 0) printf("Matrix is singular");
  else printf("Matrix is non-singular");
  return;
}

void isSymmetric(int M[MAX_ROWS][MAX_COLS], int rows, int cols) {
  if (!isSquare(rows, cols)) return;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) { M[i][j] == M[j][i]; }
}

void isAntiSymmetric(int M[MAX_ROWS][MAX_COLS], int rows, int cols) {
  if (!isSquare(rows, cols)) return;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) { M[i][j] == -M[j][i]; }
}

// r, c: Row and column indices of element for which cofactor is computed
void getCOfactor(int M[MAX_ROWS][MAX_COLS], int temp[MAX_ROWS][MAX_COLS],
                 int rows, int cols, int r, int c) {
  int i = 0, j = 0;
  for (int row = 0; row < rows; row++)
    for (int col = 0; col < cols; col++) {
      if (row != r && col != c) {
        temp[i][j++] = M[row][col];
        if (j == cols - 1) {
          j = 0;
          i++;
        }
      }
    }
}

int determinant(int M[MAX_ROWS][MAX_COLS], int n) {
  if (n == 1) return M[0][0];
  if (n == 2) return M[0][0] * M[1][1] - M[0][1] * M[1][0];

  int det = 0;
  int temp[MAX_ROWS][MAX_COLS];
  for (int p = 0; p < n; p++) {
    getCofactor(M, temp, n, n, 0, p);
    // (p % 2 == 0 ? 1 : -1): Alternate signs
    det += ((p % 2 == 0 ? 1 : -1) * M[0][p] * determinant(temp, n - 1));
  }

  return det;
}

int isSquare(int rows, int cols) {
  if (rows != cols) {
    printf("Matrix is not square\n");
    return 0;
  }
  return 1;
}