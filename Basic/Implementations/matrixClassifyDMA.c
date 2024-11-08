#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 15
#define MAX_COLS 15
#define NL       printf("\n")

#define ALLOC_MATRIX(rows, cols)                      \
  ({                                                  \
    int **M = (int **)malloc((rows) * sizeof(int *)); \
    for (int i = 0; i < (rows); i++) {                \
      M[i] = (int *)malloc((cols) * sizeof(int));     \
    }                                                 \
    M;                                                \
  })

void transpose(int **M, int **M_T, int rows, int cols);
void multiplyMatrices(int **A, int **B, int **result, int A_rows, int A_cols,
                      int B_cols);
void getCofactor(int **M, int **temp, int rows, int cols, int r, int c);
int determinant(int **M, int n);

void cls();
void display(int **M, int rows, int cols);
int isSquare(int rows, int cols);
void isScalar(int **M, int rows, int cols);
void isDiagonal(int **M, int rows, int cols);
int isIdentity(int **M, int rows, int cols);
void isSingular(int **M, int rows, int cols);
void isLower(int **M, int rows, int cols);
void isUpper(int **M, int rows, int cols);
void isSymmetric(int **M, int rows, int cols);
void isAntiSymmetric(int **M, int rows, int cols);
void isOrthogonal(int **M, int rows, int cols);
void isIdempotent(int **M, int rows, int cols);
void isCentrosymmetric(int **M, int rows, int cols);
void isElementary(int **M, int rows, int cols);

int main() {
  int **m = ALLOC_MATRIX(3, 3);
  m[0][0] = 1;
  m[0][1] = 0;
  m[0][2] = 0;
  m[1][0] = 0;
  m[1][1] = 1;
  m[1][2] = 0;
  m[2][0] = 0;
  m[2][1] = 0;
  m[2][2] = 1;

  int **a = ALLOC_MATRIX(2, 2);
  a[0][0] = 0;
  a[0][1] = 1;
  a[1][0] = 1;
  a[1][1] = 0;

  int **b = ALLOC_MATRIX(3, 3);
  b[0][0] = 1;
  b[0][1] = 0;
  b[0][2] = 0;
  b[1][0] = 0;
  b[1][1] = 1;
  b[1][2] = 3;
  b[2][0] = 0;
  b[2][1] = 0;
  b[2][2] = 1;

  printf("m: ");
  isElementary(m, 3, 3);
  printf("a: ");
  isElementary(a, 2, 2);
  printf("b: ");
  isElementary(b, 3, 3);

  for (int i = 0; i < 3; i++) free(m[i]);
  free(m);

  for (int i = 0; i < 2; i++) free(a[i]);
  free(a);

  for (int i = 0; i < 3; i++) free(b[i]);
  free(b);

  return 0;
}

void display(int **M, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) { printf("%d ", M[i][j]); }
    NL;
  }
}

void isScalar(int **M, int rows, int cols) {
  if (!isSquare(rows, cols)) return;

  int a = M[0][0];
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i == j) {
        if (M[i][j] != a) {
          printf("Not a scalar matrix\n");
          return;
        }
      } else {
        if (M[i][j] != 0) {
          printf("Not a scalar matrix\n");
          return;
        }
      }
    }
  }
  printf("Is a scalar matrix\n");
}

void isDiagonal(int **M, int rows, int cols) {
  if (!isSquare(rows, cols)) return;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i != j && M[i][j] != 0) {
        printf("Not a diagonal matrix\n");
        return;
      }
    }
  }
  printf("Is a diagonal matrix\n");
}

int isIdentity(int **M, int rows, int cols) {
  if (!isSquare(rows, cols)) return 0;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if ((i == j && M[i][j] != 1) || (i != j && M[i][j] != 0)) { return 0; }
    }
  }
  return 1;
}

void isLower(int **M, int rows, int cols) {
  if (!isSquare(rows, cols)) return;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i < j && M[i][j] != 0) {
        printf("Not lower triangular\n");
        return;
      }
    }
  }
  printf("Is a lower triangular matrix\n");
}

void isUpper(int **M, int rows, int cols) {
  if (!isSquare(rows, cols)) return;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i > j && M[i][j] != 0) {
        printf("Not upper triangular\n");
        return;
      }
    }
  }
  printf("Is a upper triangular matrix\n");
}

void isSingular(int **M, int rows, int cols) {
  if (!isSquare(rows, cols)) return;

  int det = determinant(M, rows);
  if (det == 0) printf("Matrix is singular\n");
  else printf("Matrix is non-singular\n");
  return;
}

void isSymmetric(int **M, int rows, int cols) {
  if (!isSquare(rows, cols)) return;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (M[i][j] != M[j][i]) {
        printf("Not a symmetric matrix\n");
        return;
      }
    }
  }
  printf("Is a symmetric matrix\n");
}

void isAntiSymmetric(int **M, int rows, int cols) {
  if (!isSquare(rows, cols)) return;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (M[i][j] != -M[j][i]) {
        printf("Not an anti-symmetric matrix\n");
        return;
      }
    }
  }
  printf("Is an anti-symmetric matrix\n");
}

void isOrthogonal(int **M, int rows, int cols) {
  if (!isSquare(rows, cols)) return;
  int **M_T = ALLOC_MATRIX(cols, rows);

  int **prod = ALLOC_MATRIX(rows, cols);

  transpose(M, M_T, rows, cols);
  multiplyMatrices(M_T, M, prod, cols, rows, cols);

  if (isIdentity(prod, rows, cols)) printf("Is an orthogonal matrix\n");
  else printf("Not an orthogonal matrix\n");

  for (int i = 0; i < cols; i++) free(M_T[i]);
  free(M_T);

  for (int i = 0; i < rows; i++) free(prod[i]);
  free(prod);
}

void isIdempotent(int **M, int rows, int cols) {
  if (!isSquare(rows, cols)) return;
  int **result = ALLOC_MATRIX(rows, cols);

  multiplyMatrices(M, M, result, rows, cols, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (result[i][j] != M[i][j]) {
        printf("Not an idempotent matrix\n");
        return;
      }
    }
  }
  printf("Is an idempotent matrix\n");
  return;
}

void isCentrosymmetric(int **M, int rows, int cols) {
  if (!isSquare(rows, cols)) return;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (M[i][j] != M[rows - i - 1][cols - j - 1]) {
        printf("Not a centrosymmetric matrix\n");
        return;
      }
    }
  }
  printf("Is a centrosymmetric matrix\n");
  return;
}

void isElementary(int **M, int rows, int cols) {
  if (!isSquare(rows, cols)) return;
  if (isIdentity(M, rows, cols)) {
    printf("Identity matrix (Elementary)\n");
    return;
  }

  int swaps = 0;
  int scale = 0;
  int adds = 0;
  for (int i = 0; i < rows; i++) {
    int onesInRow = 0;
    for (int j = 0; j < cols; j++) {
      if (M[i][j] != 1 && i == j && M[i][j] != 0) scale++;
      else if (i != j && M[i][j] == 1) swaps++;
      else if (M[i][j] != 0 && i != j) adds++;
      if (M[i][j] == 1) onesInRow++;
    }
    if (onesInRow > 2 && (adds == 0 || swaps == 0)) {
      printf("Matrix is not elementary\n");
      return;
    }
  }

  if (swaps > 2 || scale > 1 || adds > 1) {
    printf("Matrix is not elementary\n");
    return;
  } else if (swaps == 2 && scale != 1) {
    printf("Matrix is a row swap matrix\n");
  } else if (scale == 1 && swaps != 2) {
    printf("Matrix is a row scaling matrix\n");
  } else if (adds == 1 && swaps != 1) {
    printf("Matrix is a row addition matrix\n");
  } else {
    printf("Matrix is not elementary\n");
  }
}

void getCofactor(int **M, int **temp, int rows, int cols, int r, int c) {
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

int determinant(int **M, int n) {
  if (n == 1) return M[0][0];
  if (n == 2) return M[0][0] * M[1][1] - M[0][1] * M[1][0];

  int det = 0;
  int **temp = ALLOC_MATRIX(n, n);

  for (int p = 0; p < n; p++) {
    getCofactor(M, temp, n, n, 0, p);
    det += ((p % 2 == 0 ? 1 : -1) * M[0][p] * determinant(temp, n - 1));
  }

  for (int i = 0; i < n; i++) free(temp[i]);
  free(temp);

  return det;
}

void transpose(int **M, int **M_T, int rows, int cols) {
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) { M_T[j][i] = M[i][j]; }
}

void multiplyMatrices(int **A, int **B, int **result, int A_rows, int A_cols,
                      int B_cols) {
  for (int i = 0; i < A_rows; i++) {
    for (int j = 0; j < B_cols; j++) {
      result[i][j] = 0;
      for (int k = 0; k < A_cols; k++) { result[i][j] += A[i][k] * B[k][j]; }
    }
  }
}

int isSquare(int rows, int cols) {
  if (rows != cols) {
    printf("Matrix is not square\n");
    return 0;
  }
  return 1;
}

void cls() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}
