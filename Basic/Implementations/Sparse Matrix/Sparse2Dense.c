#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ROWS     100
#define MAX_COLS     100
#define MAX_NON_ZERO 100
#define NL           printf("\n")

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

void display(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) { printf(" %d ", matrix[i][j]); }
    NL;
  }
}

void convert_to_dense(SparseElement sparse[MAX_NON_ZERO], int count,
                      int dense[MAX_ROWS][MAX_COLS], int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) { dense[i][j] = 0; }
  }

  for (int i = 0; i < count; i++) {
    dense[sparse[i].row][sparse[i].col] = sparse[i].value;
  }
}

int convert_to_sparse(int dense[MAX_ROWS][MAX_COLS], int rows, int cols,
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

int tranpose(SparseElement sparse[MAX_NON_ZERO], int count,
             SparseElement result[MAX_NON_ZERO]) {
  int k = 0;
  for (int i = 0; i < count; i++) {
    result[k].row = sparse[i].col;
    result[k].col = sparse[i].row;
    result[k].value = sparse[i].value;
    k++;
  }
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
  int rows1, rows2, cols1, cols2;
  int count1, count2, result_count;
  while (1) {
    printf("\n===/ Menu \\===\n");
    printf("1. Input sparse matrix 1\n");
    printf("2. Input sparse matrix 2\n");
    printf("3. Transpose of matrix 1\n");
    printf("4. Addition of both matrices (Sparse)\n");
    printf("5. Exit\n");
    printf("> ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
      printf("\n\033[1;32mSelected 1.\033[0m");
      printf("\nEnter the number of rows and columns for Matrix 1 (R C): ");
      scanf("%d %d", &rows1, &cols1);
      printf("Enter the number of non-zero elements in Matrix 1: ");
      scanf("%d", &count1);
      printf("Enter sparse elements (row, col, value) for Matrix 1:\n");
      for (int i = 0; i < count1; i++) {
        scanf("%d %d %d", &S1[i].row, &S1[i].col, &S1[i].value);
      }

      convert_to_dense(S1, count1, denseM1, rows1, cols1);
      printf("\n-> Sparse Matrix 1:\n");
      print_sparse(S1, count1);
      printf("\n-> Dense Matrix 1:\n");
      display(denseM1, rows1, cols1);
    } else if (choice == 2) {
      printf("\n\033[1;32mSelected 2.\033[0m");
      printf("\nEnter the number of rows and columns for Matrix 2 (R C): ");
      scanf("%d %d", &rows2, &cols2);
      printf("Enter the number of non-zero elements in Matrix 2: ");
      scanf("%d", &count2);
      printf("Enter sparse elements (row, col, value) for Matrix 2:\n");
      for (int i = 0; i < count2; i++) {
        scanf("%d %d %d", &S2[i].row, &S2[i].col, &S2[i].value);
      }

      convert_to_dense(S2, count2, denseM2, rows2, cols2);
      printf("\n-> Sparse Matrix 2:\n");
      print_sparse(S2, count2);
      printf("\n-> Dense Matrix 2:\n");
      display(denseM2, rows2, cols2);
    } else if (choice == 3) {
      printf("\n\033[1;32mSelected 3.\033[0m");
      if (count1 > 0) {
        result_count = transpose(S1, count1, result);
        printf("\n-> Transposed Sparse Matrix 1:\n");
        print_sparse(result, result_count);
      } else {
        printf("\n\033[1;31m#\033[0m Sparse matrix 1 is not added yet\n");
      }
    } else if (choice == 4) {
      printf("\n\033[1;32mSelected 4.\033[0m");
      if (count1 > 0 && count2 > 0) {
        result_count = addition(S1, count1, S2, count2, result);
        printf("\n-> Sparse Matrix 1 + Sparse Matrix 2:\n");
        print_sparse(result, result_count);
      } else {
        printf("\n\033[1;31m#\033[0m Sparse matrix 1 or 2 is not added yet\n");
      }
    } else if (choice == 5) {
      printf("Exiting...\n");
      sleep(1);
      cls();
      break;
    } else {
      printf("Invalid choice");
    }
  }

  return 0;
}