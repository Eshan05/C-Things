// binarycalc.c

#include "binarycalc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long int toDecimal(const char *number, int base) {
  return strtoll(number, NULL, base);
}

void fromDecimal(long long int number, int base, char *result) {
  char digits[] = "0123456789ABCDEF";
  char buffer[65];
  int i = 0;
  if (number == 0) {
    result[i++] = '0';
  } else {
    while (number > 0) {
      buffer[i++] = digits[number % base];
      number /= base;
    }
    for (int j = i - 1; j >= 0; j--)
      result[i - 1 - j] = buffer[j];

    result[i] = '\0';
  }
}

void baseConversion() {
  char number[65];
  int fromBase, toBase;
  char result[65];
  printf("Enter the number: ");
  scanf("%s", number);
  printf("Enter the base of the number: ");
  scanf("%d", &fromBase);
  printf("Enter the base to convert to: ");
  scanf("%d", &toBase);

  long long int decimalValue = toDecimal(number, fromBase);
  fromDecimal(decimalValue, toBase, result);
  printf("Result: %s\n", result);
}

void binaryAddition() {
  unsigned int a, b, sum;
  printf("Enter first binary number (in decimal): ");
  scanf("%u", &a);
  printf("Enter second binary number (in decimal): ");
  scanf("%u", &b);
  sum = a ^ b;
  unsigned int carry = a & b;
  while (carry != 0) {
    carry <<= 1;
    unsigned int newSum = sum ^ carry;
    carry = sum & carry;
    sum = newSum;
  }

  printf("Result: %u (in decimal)\n", sum);
}

void twosComplement() {
  unsigned int num, n;
  printf("Enter a number in decimal: ");
  scanf("%u", &num);
  printf("Enter the number of bits: ");
  scanf("%u", &n);
  unsigned int mask = (1 << n) - 1;
  unsigned int comp = (~num & mask) + 1;
  printf("2's Complement: %u\n", comp);
}

// complement
void binarySubtraction() {
  unsigned int a, b;
  printf("Enter the minuend (first number in decimal): ");
  scanf("%u", &a);
  printf("Enter the subtrahend (second number in decimal): ");
  scanf("%u", &b);

  unsigned int onesComplementResult = a - b;
  printf("1's Complement Subtraction Result: %u\n", onesComplementResult);
  unsigned int twosComplementResult = a + (~b + 1);
  printf("2's Complement Subtraction Result: %u\n", twosComplementResult);
}

void BinaryCalculator() {
  int flag = 1;
  int choice;
  while (flag) {
    printf("1. Base Conversion\n2. Binary Addition\n3. Binary Subtraction\n4. "
           "2's Complement\n5. Exit\n");
    printf("Select an option: ");
    scanf("%d", &choice);
    switch (choice) {
      case 1: baseConversion(); break;
      case 2: binaryAddition(); break;
      case 3: binarySubtraction(); break;
      case 4: twosComplement(); break;
      case 5:
        printf("Exiting...\n");
        flag = 0;
        break;
      default: printf("Invalid option, please try again.\n"); break;
    }
  }
}
