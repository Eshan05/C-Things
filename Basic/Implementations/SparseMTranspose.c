#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS     100
#define MAX_COLS     100
#define MAX_NON_ZERO 100
#define NL           printf("\n")

// Matrix or 2D Array -> dataType**
// We use these globals because otherwise we would be working with dynamic
// allocation, plus we can use sizeOf because sizeof(M) gives size of pointer M
// not the dynamically allocated memory it points to.

void cls() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

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
    for (int j = 0; j < cols; j++) { printf(" %d ", matrix[i][j]); }
    NL;
  }
}

int convert(int dense[MAX_ROWS][MAX_COLS], int rows, int cols,
            SparseElement sparse[MAX_NON_ZERO]) {
  int count = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (dense[i][j] != 0) {
        sparse[count].row = i;
        sparse[count].col = j;
        sparse[count].value = dense[i][j];
        count++;
      }
    }
  }
  return count;
}

void print_sparse(SparseElement sparse[MAX_NON_ZERO], int count) {
  for (int i = 0; i < count; i++) {
    printf(" %d %d %d\n", sparse[i].row, sparse[i].col, sparse[i].value);
  }
}

int transpose(SparseElement sparse[MAX_NON_ZERO], int count,
              SparseElement result[MAX_NON_ZERO]) {
  int k = 0;
  for (int i = 0; i < count; i++) {
    result[k].row = sparse[i].col;
    result[k].col = sparse[i].row;
    result[k].value = sparse[i].value;
    k++;
  }
  return k;
}

// Alternative way with dynamic allocation
SparseElement *transposeAlt(SparseElement sparse[MAX_NON_ZERO], int count) {
  SparseElement *result = malloc(count * sizeof(SparseElement));
  if (!transpose) {
    printf("\033[1;31mMemory allocation failed!\n");
    return NULL;
  }

  int k = 0;
  for (int i = 0; i < count; i++) {
    result[k].row = sparse[i].col;
    result[k].col = sparse[i].row;
    result[k].value = sparse[i].value;
    k++;
  }
  return result;
  /**
   * In main:
   * SparseElement *transposed = NULL;
   * transposed = transpose(S1, count1);
   * free(transposed);
   */
}

int fast_transpose(SparseElement sparse[MAX_NON_ZERO], int count,
                   SparseElement result[MAX_NON_ZERO], int rows, int cols) {
  int *row_terms = (int *)calloc(cols, sizeof(int));
  int *start = (int *)calloc(cols, sizeof(int));
  SparseElement *temp = (SparseElement *)malloc(count * sizeof(SparseElement));

  for (int i = 0; i < count; i++) { row_terms[sparse[i].col]++; }
  start[0] = 0;
  for (int i = 1; i < cols; i++) { start[i] = start[i - 1] + row_terms[i - 1]; }

  for (int i = 0; i < count; i++) {
    int pos = start[sparse[i].col];
    temp[pos].row = sparse[i].col;
    temp[pos].col = sparse[i].row;
    temp[pos].value = sparse[i].value;
    start[sparse[i].col]++;
  }

  for (int i = 0; i < count; i++) { result[i] = temp[i]; }

  free(row_terms);
  free(start);
  free(temp);
  return count;
}

int addition(SparseElement s1[MAX_NON_ZERO], int count1,
             SparseElement s2[MAX_NON_ZERO], int count2,
             SparseElement result[MAX_NON_ZERO]) {
  int i = 0, j = 0, k = 0;
  while (i < count1 && j < count2) {
    if (s1[i].row == s2[j].row) {
      if (s1[i].col == s2[j].col) {
        result[k].row = s1[i].row;
        result[k].col = s1[i].col;
        result[k].value = s1[i].value + s2[j].value;
        k++;
        i++;
        j++;
      } else if (s1[i].col < s2[j].col) {
        result[k] = s1[i];
        k++;
        i++;
      } else {
        result[k] = s2[j];
        k++;
        j++;
      }
    } else if (s1[i].row < s2[j].row) {
      result[k] = s1[i];
      k++;
      i++;
    } else {
      result[k] = s2[j];
      k++;
      j++;
    }
  }

  while (i < count1) {
    result[k] = s1[i];
    k++;
    i++;
  }

  while (j < count2) {
    result[k] = s2[j];
    k++;
    j++;
  }

  return k;
}

int main() {
  cls();
  int denseM1[MAX_ROWS][MAX_COLS], denseM2[MAX_ROWS][MAX_COLS];
  SparseElement S1[MAX_NON_ZERO], S2[MAX_NON_ZERO], result[MAX_NON_ZERO];
  int rows1, cols1, rows2, cols2;
  int count1, count2, result_count;
  while (1) {
    printf("\n===/ Menu \\===\n");
    printf("1. Input dense matrix 1\n");
    printf("2. Input dense matrix 2\n");
    printf("3. Transpose of matrix 1\n");
    printf("4. Fast transpose of matrix 1.\n");
    printf("5. Addition of both matrices (Sparse)\n");
    printf("6. Exit\n");
    printf("> ");
    int choice;
    scanf("%d", &choice);
    getchar(); // Consume newline

    if (choice == 1) {
      printf("\n\033[1;32mSelected 1.\033[0m");
      printf("\nEnter the number of rows and columns for Matrix 1 (R C): ");
      scanf("%d %d", &rows1, &cols1);
      printf("Enter elements for Matrix 1 row by row:\n");
      for (int i = 0; i < rows1; i++) {
        printf("R%d - ", i + 1);
        for (int j = 0; j < cols1; j++) { scanf("%d", &denseM1[i][j]); }
      }
      count1 = convert(denseM1, rows1, cols1, S1);
      printf("\n-> Dense Matrix 1:\n");
      display(denseM1, rows1, cols1);
      printf("\n-> Sparse Matrix 1:\n");
      print_sparse(S1, count1);
    } else if (choice == 2) {
      printf("\033[1;32mSelected 2.\033[0m");
      printf("\nEnter the number of rows and columns for Matrix 2 (R C): ");
      scanf("%d %d", &rows2, &cols2);
      printf("Enter elements for Matrix 1 row by row:\n");
      for (int i = 0; i < rows2; i++) {
        printf("R%d - ", i + 1);
        for (int j = 0; j < cols2; j++) { scanf("%d", &denseM2[i][j]); }
      }
      count2 = convert(denseM2, rows1, cols1, S2);
      printf("\n-> Dense Matrix 2:\n");
      display(denseM2, rows2, cols2);
      printf("\n-> Sparse Matrix 2:\n");
      print_sparse(S2, count2);
    } else if (choice == 3) {
      printf("\033[1;32mSelected 3.\033[0m");
      if (count1 > 0) {
        result_count = transpose(S1, count1, result);
        printf("\n-> Transposed Sparse Matrix 1:\n");
        print_sparse(result, result_count);
      } else {
        printf("\n\033[1;31m#\033[0m Sparse matrix 1 is not added yet\n");
      }
    } else if (choice == 4) {
      printf("\033[1;32mSelected 4.\033[0m");
      if (count1 > 0) {
        result_count = fast_transpose(S1, count1, result, rows1, cols1);
        printf("\n-> Fast Transposed Sparse Matrix 1:\n");
        print_sparse(result, result_count);
      } else {
        printf("\n\033[1;31m#\033[0m Sparse matrix 1 is not added yet\n");
      }
    } else if (choice == 5) {
      printf("\033[1;32mSelected 5.\033[0m");
      if (count1 > 0 && count2 > 0) {
        result_count = addition(S1, count1, S2, count2, result);
        printf("\n-> Sparse Matrix 1 + Sparse Matrix 2:\n");
        print_sparse(result, result_count);
      } else {
        printf("\n\033[1;31m#\033[0m Sparse matrix 1 or 2 is not added yet\n");
      }
    } else if (choice == 6) {
      printf("Exiting...\n");
      cls();
      break;
    } else {
      printf("Invalid choice");
    }
  }

  return 0;
}