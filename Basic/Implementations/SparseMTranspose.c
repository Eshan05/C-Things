#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS     100
#define MAX_COLS     100
#define MAX_NON_ZERO 100
#define NL           printf("\n");

// Matrix or 2D Array -> dataType**
// We use these globals because otherwise we would be working with dynamic
// allocation, plus we can use sizeOf because sizeof(M) gives size of pointer M
// not the dynamically allocated memory it points to.

typedef struct {
  int row;
  int col;
  int value;
} SparseElement;
/*SparseElement S1[MAX_NON_ZERO] = {
  {0, 2, 3},  // Row 0, Column 2, Value 3
  {2, 0, 4},  // Row 2, Column 0, Value 4
  {2, 2, 5}   // Row 2, Column 2, Value 5
};*/

void display(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%d ", matrix[i][j]);
      NL;
    }
  }
}

int main() {
  int denseM1[MAX_ROWS][MAX_COLS], denseM2[MAX_ROWS][MAX_COLS];
  SparseElement S1[MAX_NON_ZERO], S2[MAX_NON_ZERO], result[MAX_NON_ZERO];
  int rows1, cols1, rows2, cols2;
  int count1, count2, result_count;
  while (1) {
    printf("\n Menu:\n");
    printf("1. Input dense matrix 1\n");
    printf("2. Input dense matrix 2\n");
    printf("3. Transpose of matrix 1\n");
    printf("4. Fast transpose of matrix 1.\n");
    printf("5. Addition of both matrices (Sparse)\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    getchar(); // Consime newline

    if (choice == 1) {
      printf("\nEnter the number of rows and columns for Matrix 1: ");
      scanf("%d %d", &rows1, &cols1);
      printf("\nEnter elements for Matrix 1 row by row:\n");
      for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) { scanf("%d", &denseM1[i][j]); }
      }
    }
  }
}