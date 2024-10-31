// conversion.c

#include "conversion.h"
#include <stdio.h>

void ConversionCalculator() {
  int flag = 1;
  int choice;

  while (flag) {
    printf(
        "1. Time\n2. Length\n3. Weight\n4. Storage\n5. Temperature\n6. Exit\n");
    printf("Select an option: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1: convertTime(); break;
      case 2: convertLength(); break;
      case 3: convertWeight(); break;
      case 4: convertStorage(); break;
      case 5: convertTemperature(); break;
      case 6:
        printf("Exiting...\n");
        flag = 0;
        break;
      default: printf("Invalid option, please try again.\n"); break;
    }
  }
}

void convertTime() {
  int choice;
  double value, result;
  printf("1. Hours to Minutes\n2. Minutes to Seconds\n");
  printf("Select conversion type: ");
  scanf("%d", &choice);
  printf("Enter value: ");
  scanf("%lf", &value);

  switch (choice) {
    case 1:
      result = value * 60;
      printf("Result: %.2lf minutes\n", result);
      break;
    case 2:
      result = value * 60;
      printf("Result: %.2lf seconds\n", result);
      break;
    default: printf("Invalid choice\n"); break;
  }
}

void convertLength() {
  int choice;
  double value, result;
  printf("1. Meters to Kilometers\n2. Kilometers to Meters\n");
  printf("Select conversion type: ");
  scanf("%d", &choice);
  printf("Enter value: ");
  scanf("%lf", &value);

  switch (choice) {
    case 1:
      result = value / 1000;
      printf("Result: %.3lf kilometers\n", result);
      break;
    case 2:
      result = value * 1000;
      printf("Result: %.0lf meters\n", result);
      break;
    default: printf("Invalid choice\n"); break;
  }
}

void convertWeight() {
  int choice;
  double value, result;
  printf("1. Kilograms to Grams\n2. Grams to Kilograms\n");
  printf("Select conversion type: ");
  scanf("%d", &choice);
  printf("Enter value: ");
  scanf("%lf", &value);

  switch (choice) {
    case 1:
      result = value * 1000;
      printf("Result: %.0lf grams\n", result);
      break;
    case 2:
      result = value / 1000;
      printf("Result: %.3lf kilograms\n", result);
      break;
    default: printf("Invalid choice\n"); break;
  }
}

void convertStorage() {
  int choice;
  double value, result;
  printf("1. Megabytes to Kilobytes\n2. Kilobytes to Megabytes\n");
  printf("Select conversion type: ");
  scanf("%d", &choice);
  printf("Enter value: ");
  scanf("%lf", &value);

  switch (choice) {
    case 1:
      result = value * 1024;
      printf("Result: %.0lf kilobytes\n", result);
      break;
    case 2:
      result = value / 1024;
      printf("Result: %.3lf megabytes\n", result);
      break;
    default: printf("Invalid choice\n"); break;
  }
}

void convertTemperature() {
  int choice;
  double value, result;
  printf("1. Celsius to Fahrenheit\n2. Fahrenheit to Celsius\n");
  printf("Select conversion type: ");
  scanf("%d", &choice);
  printf("Enter value: ");
  scanf("%lf", &value);

  switch (choice) {
    case 1:
      result = (value * 9 / 5) + 32;
      printf("Result: %.2lf Fahrenheit\n", result);
      break;
    case 2:
      result = (value - 32) * 5 / 9;
      printf("Result: %.2lf Celsius\n", result);
      break;
    default: printf("Invalid choice\n"); break;
  }
}
