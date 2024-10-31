#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void series();
void roots_of_quad();
void linear_equation();

void EquationSolver() {
  int choice, flag = 1;
  while (flag) {
    printf("1. Roots of quadratic.\n 2. Two linear equations\n3. Exit\n");
    printf("Enter your choice");
    scanf("%d ", &choice);
    switch (choice) {
      case 1: roots_of_quad(); break;
      case 2: linear_equation(); break;
      case 3:
        printf("Exiting...\n");
        flag = 0;
        break;
    }
  }
  return;
}

void SeriesCalculator() {
  series();
  return;
}

void series() {
  float first_term, second_term, last_term, common_diff, sum, nth_term;
  int sub, select, no_of_terms;
  int a, n, r, temp, i;
  float sum_1 = 0;
  int terms, first, denominator, diff;
  float sum1 = 0.0;

  printf("\nSelect subtopic");
  printf("\n1] Arithmetic progression.\n2] Geometric progression.\n3] "
         "Harmonic progression\n4] Fibonacci");
  printf("\nEnter your choice:- ");
  scanf("%d", &sub);
  switch (sub) {
    case 1:
      printf("Select the option as per your requirement : \n1.To find the "
             "sum of series.\n2.To find the nth term of the series.");
      scanf("%d", &select);
      switch (select) {
        case 1:
          printf("\nEnter the first term : ");
          scanf("%f", &first_term);
          printf("\nEnter the second term : ");
          scanf("%f", &second_term);
          printf("\nTotal number of terms : ");
          scanf("%d", &no_of_terms);
          common_diff = second_term - first_term;
          sum = (no_of_terms *
                 (2 * first_term + (no_of_terms - 1) * common_diff)) /
                2;
          printf("The sum of %d terms of the series is : %f", no_of_terms, sum);
          break;

        case 2:
          printf("\nEnter the first term : ");
          scanf("%f", &first_term);
          printf("\nEnter the second term : ");
          scanf("%f", &second_term);
          printf("\nTotal number of terms : ");
          scanf("%d", &no_of_terms);
          common_diff = second_term - first_term;
          nth_term = first_term + (no_of_terms - 1) * common_diff;
          printf("\nThe nth term of the series is : %f", nth_term);
          break;
      }

    case 2:
      printf("\nEnter First Number of an G.P Series:  ");
      scanf("%d", &a);
      printf("\nEnter the Total Numbers in this G.P Series:  ");
      scanf("%d", &n);
      printf("\nEnter the Common Ratio:  ");
      scanf("%d", &r);
      temp = a;
      printf("The G.P Series is  :  ");
      for (i = 0; i < n; i++) {
        printf("%d  ", temp);
        sum1 = sum1 + temp;
        temp = temp * r;
      }
      printf("\nThe Sum of Geometric Progression Series =  %f\n", sum1);
      break;
    case 3:
      printf("Enter the number of terms in HP series\n");
      scanf("%d", &terms);
      printf("Enter denominator of first term and common difference of HP "
             "series\n");
      scanf("%d %d", &first, &diff);

      denominator = first;
      printf("HP SERIES\n");
      for (i = 0; i < terms; i++) {
        printf("1/%d ", denominator);
        sum1 += 1 / (float)denominator;
        denominator += diff;
      }

      printf("\nSum of the HP series till %d terms is %f\n", terms, sum1);
    case 4:
      int fibn, fib1 = 0, fib2 = 1, fib3 = fib1 + fib2;
      printf("How many terms of the Fibonacci series should be displayed: ");
      scanf("%d", &fibn);
      printf("1 ");
      for (int i = 0; i < fibn; i++) {
        printf("%d ", fib3);
        fib1 = fib2;
        fib2 = fib3;
        fib3 = fib1 + fib2;
      }
  }
}

void roots_of_quad(void) {
  double a, b, c, discriminant, root1, root2, realPart, imagPart;
  printf("Enter coefficients a, b and c: ");
  scanf("%lf %lf %lf", &a, &b, &c);
  discriminant = b * b - 4 * a * c;
  if (discriminant > 0) {
    root1 = (-b + sqrt(discriminant)) / (2 * a);
    root2 = (-b - sqrt(discriminant)) / (2 * a);
    printf("Root 1 = %.2lf and Root 2 = %.2lf", root1, root2);
  } else if (discriminant == 0) {
    root1 = -b / (2 * a);
    root2 = -b / (2 * a);
    printf("Root 1 = Root2 = %.2lf;", root1);
  } else {
    realPart = -b / (2 * a);
    imagPart = sqrt(-discriminant) / (2 * a);
    printf("Root 1 = %.2lf+%.2lfi and Root2 = %.2f-%.2fi", realPart, imagPart,
           realPart, imagPart);
  }
}

void linear_equation() {
  float a1, b1, c1, a2, b2, c2;
  printf("Enter values of coefficients for first equation\n");
  scanf("%f%f%f", &a1, &b1, &c1);
  printf("Enter values of coefficients for second equation\n");
  scanf("%f%f%f", &a2, &b2, &c2);
  if (a1 / a2 == b1 / b2 && a1 / a2 != c1 / c2) {
    printf("Lines formed by these equation are parallel and have no  "
           "solution.");
  } else if (a1 / a2 == b1 / b2 && a1 / a2 == c1 / c2) {
    printf("Lines formed by these equation are overlaping and have "
           "infinite solution.");
  } else {
    float x = ((b1 * c2) - (b2 * c1)) / ((a1 * b2 - a2 * b1));
    float y = ((c1 * a2) - (c2 * a1)) / ((a1 * b2 - a2 * b1));
    printf("Unique Solution is (%.3f,%.3f)", x, y);
  }
}