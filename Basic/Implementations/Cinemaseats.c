#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS  10
#define SEATS 7

void initSeats(bool seats[ROWS][SEATS]) {
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < SEATS; j++) {
      seats[i][j] = false;
    }
  }
}

void displaySeats(bool seats[ROWS][SEATS]) {
  printf("Seating Arrangement\n\n");
  for(int i = 0; i < ROWS; i++) {
    printf("Row %d: ", i);
    for(int j = 0; j < SEATS; ++j) {
      if(seats[i][j]) printf("S%d: |_B_| ", j);
      else printf("S%d: |___| ", j);
    }
    printf("\n");
  }
  printf("\n");
}

bool bookSeat(bool seats[ROWS][SEATS], int row, int seat) {
  if(!seats[row][seat]) {
    seats[row][seat] = true;
    return true;
  }
  return false;
}

bool cancelSeat(bool seats[ROWS][SEATS], int row, int seat) {
  if(seats[row][seat]) {
    seats[row][seat] = false;
    return true;
  }
  return false;
}

int main() {
  bool seats[ROWS][SEATS];
  initSeats(seats);
  int ch, row, seat;
  printf("\n1. Display Seats\n");
  printf("2. Book Seat\n");
  printf("3. Cancel Booking\n");
  printf("4. Exit\n");
  while(1) {
    printf("Enter your choice: ");
    scanf("%d", &ch);
    switch(ch) {
      case 1: displaySeats(seats); break;
      case 2:
        printf("Enter row (0-9) and seat (0-6): ");
        scanf("%d %d", &row, &seat);
        if(row < 1 || row >= ROWS || seat < 0 || seat >= SEATS)
          printf("Invalid input!");
        else if(bookSeat(seats, row, seat)) printf("Booked successfully!\n");
        else printf("This seat is already booked.\n");
        break;
      case 3:
        printf("Enter row (0-9) and seat (0-6): ");
        scanf("%d %d", &row, &seat);
        if(row < 1 || row >= ROWS || seat < 0 || seat >= SEATS)
          printf("Invalid input!");
        else if(cancelSeat(seats, row, seat))
          printf("Cancelled successfully!\n");
        else printf("This seat isn't booked.\n");
        break;
      case 4: printf("Exiting..."); return 0;
      default: printf("Invalid choice!");
    }
  }
  return 0;
}
