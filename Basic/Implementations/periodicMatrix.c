#include <stdbool.h>
#include <stdio.h>
#define MAX_SIZE 10

void multiplyMatrices(int A[MAX_SIZE][MAX_SIZE], int B[MAX_SIZE][MAX_SIZE],
                      int result[MAX_SIZE][MAX_SIZE], int size);
bool areEqual(int A[MAX_SIZE][MAX_SIZE], int B[MAX_SIZE][MAX_SIZE], int size);
int getPeriod(int M[MAX_SIZE][MAX_SIZE], int size);
void inputMatrix(int M[MAX_SIZE][MAX_SIZE], int size);

int main() {
  printf("===/ Periodic Matrix \\===\n");
  int M[MAX_SIZE][MAX_SIZE];
  int size;
  printf("Enter size of matrix");
  scanf("%d", &size);
  if (size <= 0 || size > MAX_SIZE) {
    printf("Invalid matrix size\n");
    return 1;
  }

  inputMatrix(M, size);
  int period = getPeriod(M, size);
  if (period != -1) printf("The matrix is periodic with period: %d\n", period);
  else printf("The matrix is not periodic.\n");

  return 0;
}

bool areEqual(int A[MAX_SIZE][MAX_SIZE], int B[MAX_SIZE][MAX_SIZE], int size) {
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      if (A[i][j] != B[i][j]) { return false; }
  return true;
}

void multiplyMatrices(int A[MAX_SIZE][MAX_SIZE], int B[MAX_SIZE][MAX_SIZE],
                      int result[MAX_SIZE][MAX_SIZE], int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      result[i][j] = 0;
      for (int k = 0; k < size; k++) result[i][j] += A[i][k] * B[k][j];
    }
  }
}

int getPeriod(int M[MAX_SIZE][MAX_SIZE], int size) {
  int currentPower[MAX_SIZE][MAX_SIZE];
  int nextPower[MAX_SIZE][MAX_SIZE];
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) //
      currentPower[i][j] = M[i][j];

  for (int p = 2; p <= size * size; p++) {
    multiplyMatrices(currentPower, M, nextPower, size);
    if (areEqual(nextPower, M, size)) return p;
    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++) //
        currentPower[i][j] = nextPower[i][j];
  }

  return -1;
}

void inputMatrix(int M[MAX_SIZE][MAX_SIZE], int size) {
  printf("Enter the matrix of size %d x %d:\n", size, size);
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) //
      scanf("%d", &M[i][j]);
}