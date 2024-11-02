#include <stdio.h>
#include <stdlib.h>

/*Linked List Node Structure*/

struct listNode {
  int info;
  int row;
  int column;
  struct listNode *nextRow;
  struct listNode *nextColumn;
}; // MLL

/* Prototypes */
void createMatrix(struct listNode **startPtr, int rows, int columns);
void addRowNode(struct listNode *startPtr, int row, int column, int info);
void addColNode(struct listNode *startPtr, int row, int column, int info);
void insert(struct listNode *startPtr, int row, int column, int info);
void printRow(struct listNode *startPtr, int row, int number_columns);
void printMatrix(struct listNode *startPtr, int number_rows,
                 int number_columns);
int delete(struct listNode *startPtr, int row, int column);
int locate(struct listNode *startPtr, int row, int column);
int assign(struct listNode *startPtr, int row, int column, int info);
int read(struct listNode *startPtr, int row, int column);
struct listNode *sum(struct listNode *startPtr_0, struct listNode *startPtr_1,
                     int *size_0, int *size_1);
struct listNode *product(struct listNode *startPtr_0,
                         struct listNode *startPtr_1, int *size_0, int *size_1);

int main(void) {
  struct listNode **startPtr = NULL;
  struct listNode *startPtr_0 = NULL;
  struct listNode *startPtr_1 = NULL;
  struct listNode *sum_startPtr = NULL;
  struct listNode *prod_startPtr = NULL;
  int size_0[2] = {}; // Size of the first matrix
  int size_1[2] = {}; // Size of the second matrix
  int *size;          // Auxiliary pointer that I use to point the size(array)
  int option;
  int row, column, info; // Parameters for insert function
  int select_matrix;

  printf("--- Welcome: Sparse Matrix via MLL ---\n\n");
  /*First Matrix*/
  printf("*** Enter the size for the first matrix *** \n");
  printf("Enter the number of rows: ");
  scanf(" %d,", size_0);
  printf("Enter the number of columns: ");
  scanf(" %d", size_0 + 1);
  createMatrix(&startPtr_0, size_0[0], size_0[1]);

  /*Second Matrix*/
  printf("\n*** Enter the size for the second matrix ***\n");
  printf("Enter the number of rows: ");
  scanf(" %d,", size_1);
  printf("Enter the number of columns: ");
  scanf(" %d", size_1 + 1);
  createMatrix(&startPtr_1, size_1[0], size_1[1]);

  do {
    printf("Do you choose first (1) or second (2) matrix: ");
    scanf(" %d", &select_matrix);
    if(select_matrix == 1) {
      startPtr = &startPtr_0;
      size = size_0;
    } else if(select_matrix == 2) {
      startPtr = &startPtr_1;
      size = size_1;
    } else printf("Invalid option\n");

    printf("\t===/ SPARSE MATRIX \\===\n\n");
    printf("\t 1 - Print Matrix\n");
    printf("\t 2 - Insert an element\n");
    printf("\t 3 - Delete an element\n");
    printf("\t 4 - Assign Info\n");
    printf("\t 5 - Read Info\n");
    printf("\t 6 - Exit\n\n");
    printf("\tEnter your option: ");
    scanf(" %d", &option);
    printf("\n");
    if(option < 1 || option > 6) printf("Invalid option\n");
    if(option == 1) printMatrix(*startPtr, size[0], size[1]);
    if(option == 2) {
      printf("Enter position [R,C]: ");
      scanf(" %d,%d", &row, &column);
      if(row > size[0] || column > size[1]) {
        printf("Out of range!\n");
      } else if(locate(*startPtr, row, column) == 1) {
        printf("There is an element in that position use [Assign] to change "
               "its value\n");
      } else {
        printf("Enter the data: ");
        scanf(" %d", &info);
        insert(*startPtr, row, column, info);
      }
    }
    if(option == 3) {
      printf("Enter position [R,C]: ");
      scanf(" %d,%d", &row, &column);
      if(row > size[0] || column > size[1]) {
        printf("Out of range!\n");
      } else if(locate(*startPtr, row, column) == 0) {
        printf("There is no element in that position\n");
      } else {
        printf("Deleted value: %d\n", delete(*startPtr, row, column));
      }
    }
    if(option == 4) {
      printf("Enter position [R,C]: ");
      scanf(" %d,%d", &row, &column);
      if(row > size[0] || column > size[1]) {
        printf("Out of range!\n");
      } else {
        printf("Enter the data: ");
        scanf(" %d", &info);
        if(assign(*startPtr, row, column, info) == 0)
          printf("Node does not exist");
      }
    }

    if(option == 5) {
      printf("Enter position [R,C]: ");
      scanf(" %d,%d", &row, &column);
      if(row > size[0] || column > size[1]) {
        printf("Out of range!\n");
      } else {
        printf("Data: %d\n", read(*startPtr, row, column));
      }
    }

    printf("\n");
    printf("Press [Enter] key to continue.\n");
    while(getchar() != '\n');
    getchar();
    system("clear");
  } while(option != 6);

  // Sum

  printf("***SUM OF MATRIXES***\n");
  sum_startPtr = sum(startPtr_0, startPtr_1, size_0, size_1);
  if(sum_startPtr != NULL) printMatrix(sum_startPtr, size_0[0], size_0[1]);

  // Multiplication

  printf("***MATRIX PRODUCT***\n");
  prod_startPtr = product(startPtr_0, startPtr_1, size_0, size_1);
  if(prod_startPtr != NULL) printMatrix(prod_startPtr, size_0[0], size_1[1]);

  return 0;
}

void addRowNode(struct listNode *startPtr, int row, int column, int info) {
  /* This function adds an element in the same ROW */

  struct listNode *currentPtr = startPtr;
  struct listNode *newNode = malloc(sizeof(struct listNode));
  if(newNode == NULL) {
    printf("%d not inserted. No memory available. \n", info);
    return;
  }

  newNode->info = info;
  newNode->row = row;
  newNode->column = column;
  newNode->nextRow = newNode;
  newNode->nextColumn = newNode;

  while(currentPtr->nextColumn != startPtr) // Searching the last node in row
    currentPtr = currentPtr->nextColumn;

  currentPtr->nextColumn = newNode;
  newNode->nextColumn = startPtr;
}

void addColNode(struct listNode *startPtr, int row, int column, int info) {
  /* This function adds an element in the same column */

  struct listNode *currentPtr = startPtr;
  struct listNode *newNode = malloc(sizeof(struct listNode));
  if(newNode == NULL) {
    printf("%d not inserted. No memory available. \n", info);
    return;
  }

  newNode->info = info;
  newNode->row = row;
  newNode->column = column;
  newNode->nextRow = newNode;
  newNode->nextColumn = newNode;

  while(currentPtr->nextRow != startPtr) // Searching the last node in column
    currentPtr = currentPtr->nextRow;

  currentPtr->nextRow = newNode;
  newNode->nextRow = startPtr;
}

void createMatrix(struct listNode **startPtr, int rows, int columns) {
  if(*startPtr != NULL) { // If there is already a matrix
    printf("Not possible to create a new matrix");
    return;
  }

  int i; // Auxiliary variable to be used in the for loops
         // that is going to create the extra row and column
  struct listNode *headPtr = malloc(sizeof(struct listNode));

  if(headPtr == NULL) {
    printf("No memory available. \n");
    return;
  }

  headPtr->row = 0; // Initializing values
  headPtr->column = 0;
  headPtr->nextRow = headPtr;
  headPtr->nextColumn = headPtr;

  *startPtr = headPtr;
  // Linking startPtr with head of matrix, that is the element 0,0
  for(i = 1; i <= columns; i++) { addRowNode(*startPtr, 0, i, 0); }
  for(i = 1; i <= rows; i++) { addColNode(*startPtr, i, 0, 0); }
}

void insert(struct listNode *startPtr, int row, int column, int info) {
  // Add validations for when the element already exists or for when
  // the row or column is out of range

  struct listNode *newNode = malloc(sizeof(struct listNode));
  struct listNode *currentPtr;
  struct listNode *rowPtr = startPtr; // pointer to hold header of row
  struct listNode *colPtr = startPtr; // Pointer to hold header of column
  int i;
  /* Auxiliary variables to hold the addresses that will be modified */

  struct listNode *previousNextRowPtr;
  struct listNode *previousNextColPtr;

  if(newNode == NULL) {
    printf("%d not inserted. No memory available. \n", info);
    return;
  }

  // Initialize new node with provided values
  newNode->info = info;
  newNode->row = row;
  newNode->column = column;
  newNode->nextRow = NULL;
  newNode->nextColumn = NULL;

  // Traverse to the correct row header
  for(i = 1; i <= row; i++) rowPtr = rowPtr->nextRow;
  for(i = 1; i <= column; i++) colPtr = colPtr->nextColumn;
  // Here I have the headers of the row and the column;
  currentPtr = rowPtr;
  // While loop to position myself at previous element of the row
  while((currentPtr->nextColumn)->column < column &&
        currentPtr->nextColumn != rowPtr) {
    currentPtr = currentPtr->nextColumn;
  }

  // Insert the new node into the row

  previousNextColPtr = currentPtr->nextColumn;
  currentPtr->nextColumn = newNode;
  newNode->nextColumn = previousNextColPtr;

  currentPtr = colPtr;
  // While loop to position myself at the previous element of the column
  while((currentPtr->nextRow)->row < row && currentPtr->nextRow != colPtr) {
    currentPtr = currentPtr->nextRow;
  }

  // Connecting with the column

  previousNextRowPtr = currentPtr->nextRow;
  currentPtr->nextRow = newNode;
  newNode->nextRow = previousNextRowPtr;
}

void printRow(struct listNode *startPtr, int row, int number_columns) {
  struct listNode *rowPtr = startPtr;
  struct listNode *currentPtr;
  int i, j;

  for(i = 1; i <= row; i++) // Find row to print
    rowPtr = rowPtr->nextRow;

  if(rowPtr->nextColumn == rowPtr) { // When row is empty
    // If empty, print placeholders for all columns
    for(i = 1; i <= number_columns; i++) printf("_ ");
    printf("\n");
    return;
  }

  currentPtr = rowPtr->nextColumn; // Start with the first element in the row
  i = 1; // Counter to track the current column position

  while(currentPtr != rowPtr) {
    if(currentPtr->column > i) {
      // Print empty spaces for columns before the current node
      for(j = i; j < currentPtr->column; j++) {
        printf("_ ");
        i++;
      }
    } //

    printf("%d ", currentPtr->info);
    i++;

    if(currentPtr->nextColumn == rowPtr) {
      // Print placeholder for remaining columns
      for(j = currentPtr->column; j < number_columns; j++) { printf("_ "); }
    }

    currentPtr = currentPtr->nextColumn; // Move to the next node
  }
  printf("\n");
}

void printMatrix(struct listNode *startPtr, int number_rows,
                 int number_columns) {
  int i;
  for(i = 1; i <= number_rows; i++) { printRow(startPtr, i, number_columns); }
}

int delete(struct listNode *startPtr, int row, int column) {
  struct listNode *DeletedPtr;
  struct listNode *currentPtr;
  struct listNode *rowPtr = startPtr; // Pointer holding header of row
  struct listNode *colPtr = startPtr; // Pointer holding header of column
  int i;
  int deleted_value;
  /* Auxiliary variables to hold addresses to be modified */

  for(i = 1; i <= row; i++) // Traverse to specified row to locate node
    rowPtr = rowPtr->nextRow;
  for(i = 1; i <= column; i++) // Traverse to specified column to locate node
    colPtr = colPtr->nextColumn;

  // Position myself at the previous node in the row to modify its pointers
  currentPtr = rowPtr;
  while((currentPtr->nextColumn)->column != column) {
    currentPtr = currentPtr->nextColumn;
  }

  DeletedPtr = currentPtr->nextColumn; // Node to be deleted
  currentPtr->nextColumn = DeletedPtr->nextColumn;
  currentPtr =
      colPtr; // Move to the node prior to the target node in the column
  // Navigate to the correct row
  while((currentPtr->nextRow)->row != row) { currentPtr = currentPtr->nextRow; }
  currentPtr->nextRow = DeletedPtr->nextRow; // Adjusts links
  deleted_value = DeletedPtr->info;          // Store the value to be deleted

  free(DeletedPtr);
  return (deleted_value);
}

int locate(struct listNode *startPtr, int row, int column) {
  struct listNode *rowPtr = startPtr; // Pointer to hold the header of the row
  struct listNode *currentPtr;
  int i;

  // Find the row of the node to be located
  for(i = 1; i <= row; i++) rowPtr = rowPtr->nextRow;

  currentPtr = rowPtr;
  // Traverse the columns of the row to find the specified column
  while(currentPtr->nextColumn != rowPtr) {
    if((currentPtr->nextColumn)->column == column) {
      return (1); // Return 1 if the column is found
    }
    currentPtr = currentPtr->nextColumn;
  }

  return (0); // Return 0 if the column is not found
}

int assign(struct listNode *startPtr, int row, int column, int info) {
  // Check if the specified node exists;
  if(locate(startPtr, row, column) == 0) return 0;

  struct listNode *rowPtr = startPtr; // Pointer to hold header of row
  struct listNode *currentPtr;
  int i;

  // Find the row of the node I want to locate
  for(i = 1; i <= row; i++) rowPtr = rowPtr->nextRow;

  currentPtr = rowPtr;
  // Traverse to find the specified column
  while(currentPtr->column != column) currentPtr = currentPtr->nextColumn;
  // Assign the new value to the located node
  currentPtr->info = info;

  return (1); // Return 1 to indicate success
}

int read(struct listNode *startPtr, int row, int column) {
  // Check if the specified node exists;
  if(locate(startPtr, row, column) == 0) return 0;

  struct listNode *rowPtr = startPtr; // Pointer to hold header of row
  struct listNode *currentPtr;
  int i;

  // Find the row of the node to be located
  for(i = 1; i <= row; i++) rowPtr = rowPtr->nextRow;

  currentPtr = rowPtr;
  // Traverse to find the specified column
  while(currentPtr->column != column) currentPtr = currentPtr->nextColumn;
  // Return the value of the located node
  return (currentPtr->info);
}

struct listNode *sum(struct listNode *startPtr_0, struct listNode *startPtr_1,
                     int *size_0, int *size_1) {
  // Validate that the matrices are of the same size
  if(*(size_0) != *(size_1) || *(size_0 + 1) != *(size_1 + 1)) {
    printf("Incompatible Matrices to sum\n");
    return NULL;
  }

  struct listNode *startPtr = NULL;
  int i, j, suma;

  // Create a new matrix to hold the sum
  createMatrix(&startPtr, *(size_0), *(size_0 + 1));
  for(i = 1; i <= *(size_0); i++) {
    for(j = 1; j <= *(size_0 + 1); j++) {
      // Read values from both matrices and compute their sum
      suma = read(startPtr_0, i, j) + read(startPtr_1, i, j);
      // Insert the sum into the new matrix if it's not zero
      if(suma != 0) { insert(startPtr, i, j, suma); }
    }
  }

  return (startPtr); // Return the new matrix containing the sums
}

struct listNode *product(struct listNode *startPtr_0,
                         struct listNode *startPtr_1, int *size_0,
                         int *size_1) {
  if(*(size_0 + 1) != *(size_1)) {
    printf("Incompatible Matrices to multiply\n");
    return NULL;
  }

  struct listNode *startPtr = NULL;
  int i, j, k, suma;
  createMatrix(&startPtr, *(size_0), *(size_1 + 1));
  for(i = 1; i <= *(size_1 + 1); i++) {
    for(j = 1; j <= *(size_0); j++) {
      suma = 0;
      for(k = 1; k <= *(size_0 + 1); k++) {
        suma += read(startPtr_0, j, k) * read(startPtr_1, k, i);
      }
      if(suma != 0) insert(startPtr, j, i, suma);
    }
  }

  return (startPtr);
}

/**
 * The node structure is
 * Row | Column | Info
 * nextRow | nextColumn
 */

/**
 * Many networks are represented by sparse matrices because many of the elements
 * do not have direct connections and therefore their adjacency matrices are
 * sparse. Some examples are like friend connections, actors who mutually played
 * in movies or router connections. All these make graphs with sparse adjacency
 * matrices.
 *
 * Consider the following matrix for friends:
 * (Program takes in matrix and internally works with sparse matrix)
 */

/**
 * 0 1 1 0
 * 0 0 0 1
 * 0 0 0 0
 * 0 0 0 0
 *
 * Inputs:
 * 4
 * 4
 * 1,2
 * 1
 * 1,3
 * 1
 * 2,4
 * 1
 */

/**
 * Columns: Movie 1 2 3 4
 * A = | 4  0  0  5 |  (User 1)
       | 0  3  0  0 |  (User 2)
       | 0  0  2  0 |  (User 3)
       | 1  0  0  0 |  (User 4)

 * Columns: Same as A
 * B = | 1  0  0  1 |  (Action)
       | 0  1  1  0 |  (Drama)
       | 0  0  0  1 |  (Comedy)
       | 1  0  1  0 |  (Thriller)
 * Typically I would have to so column sum to a 100

 * C = A * B (User Ratings + Movie Attribute Ratio)
 * Columns: Same as A
 * A + B = | 5  0  0  6 | (User 1)
           | 0  4  1  0 |
           | 0  0  2  1 |
           | 2  0  1  0 |

 * C = A * B
 * Columns: Genres
 * Shows how much user likes each genre
 * C = | 9  0  5  4 | (User 1)
       | 0  3  3  0 |
       | 0  2  0  2 |
       | 1  0  0  1 |
 */

/**
 * As can be seen from above, the sum and product matrix give insights. The sum
 * matrix shows how different things relate to each other (Direct connections),
 * like here (Even though movie attributes are boolean) it shows how much user
 * likes each movie and weight of attribute of movie
 *
 * The product matrix shows how different things relate to each other (Indirect
 * connections), like here it shows how much user likes each genre as per movie
 * attribute (Therefore, there is a 5 in 3rd Column as 4th movie has comedy 1).
 * This is used for recommendations
 *
 * Sum shows how individual values combine
 * Product shows underlying pattern between values
 */