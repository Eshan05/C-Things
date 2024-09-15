#include <stdio.h>
#include <stdlib.h>

#define add(a, b)      ((a) + (b))
#define subtract(a, b) ((a) - (b))
#define multiply(a, b) ((a) * (b))
#define divide(a, b)   ((double)(a) / (double)(b))
#define pi             3.14159265358979323846
#define radians(x)     (((x) * pi) / 180.0)

long long binExp(long long a, long long b) {
  long long res = 1;
  while (b > 0) {
    if (b & 1) res *= a;
    a *= a;
    b >>= 1;
  }
  return res;
}

double nroot(double x, int n) {
  if (n <= 0) return 0.0 / 0.0;
  if (x < 0 && n % 2 == 0) return 0.0 / 0.0;
  if (x == 0) return 0;
  double low = (x < 1) ? x : 0;
  double high = (x < 1) ? 1 : x;
  double eps = 1e-9;
  while (high - low > eps) {
    double mid = (low + high) / 2;
    double midPower = binExp(mid, n);
    if (midPower > x) high = mid;
    else low = mid;
  }
  return low;
}

double factorial(int n) {
  double f = 1;
  for (int i = 1; i <= n; i++)
    f *= i;
  return f;
}

double loge(double x) {
  if (x <= 0) return -1.0 / 0.0;
  if (x == 1) return 0.0;
  double cnt = 0, it = 20, powe = 1, res = 0;
  double z = (x - 1) / (x + 1);
  double step = (x - 1) / (x + 1);
  while (cnt <= it) {
    double y = (1 / powe) * z;
    res += y;
    z *= step;
    powe += 2;
    cnt++;
  }
  return 2 * res;
}

double sin(double x) {
  double res = 0.0, sign = 1.0, n = 1, term = x;
  while (term > 1e-10 || term < -1e-10) {
    res += term;
    n += 2;
    sign = -sign;
    term *= (x * x) / (n * (n - 1));
    term *= sign;
  }
  return res;
}

double cos(double x) {
  double res = 0.0, sign = 1.0, n = 0, term = 1.0;
  while (term > 1e-10 || term < -1e-10) {
    res += term;
    n += 2;
    sign = -sign;
    term *= (x * x) / (n * (n - 1));
    term *= sign;
  }
  return res;
}

double arcsin(double x) {
  if (x < -1 || x > 1) return -1.0 / 0.0;
  if (x < -0.5 || x > 0.5) {
    if (x > 0.5) return pi / 2 - arcsin(nroot((1 - x * x), 2));
    return -pi / 2 + arcsin(nroot((1 - x * x), 2));
  }

  double res = 0.0, term = x;
  int n = 1;
  while (term > 1e-10 || term < -1e-10) {
    res += term;
    term *= (x * x) * (2 * n - 1) / (2 * n + 1);
    n++;
  }
  return res;
}

double arccos(double x) {
  if (x < -1 || x > 1) return -1.0 / 0.0;
  return pi / 2 - arcsin(x);
}

double arctan(double x) {
  double result = 0.0, term = x;
  int n = 1;
  while (term > 1e-10 || term < -1e-10) {
    result += term;
    term *= -(x * x) * (2 * n - 1) / (2 * n + 1);
    n++;
  }
  return result;
}

double arctan2(double y, double x) {
  if (x > 0) return arctan(y / x);
  else if (x < 0 && y >= 0) return arctan(y / x) + pi;
  else if (x < 0 && y < 0) return arctan(y / x) - pi;
  else if (x == 0 && y > 0) return pi / 2;
  else if (x == 0 && y < 0) return -pi / 2;
  else return -1.0 / 0.0;
}

void AreaCalculator() {
}
void VolumeCalculator() {
}
void MultiplicationTable() {
}
void BinaryCalculator() {
}
void EquationSolver() {
}
void ConversionCalculator() {
}
void SeriesCalculator() {
}

void displayOther() {
  printf("=== Other calculators ===\n");
  printf("\t1. Area Calculator\n");
  printf("\t2. Volume Calculator\n");
  printf("\t3. Multiplication Table\n");
  printf("\t4. Basic Binary Calculator\n");
  printf("\t5. Equation Solver\n");
  printf("\t6. Conversion Calculator\n");
  printf("\t7. Series Calculator\n");
  printf(
      "\t8. First number as argument for inverse trigonometric functions \n");
  printf("\t9. Find root of first number to any whole number\n");
  printf("\t0. Exit\n");

  int ch, flag = 1;
  double ffirst = 0.0;
  do {
    printf("\nEnter your choice for other calculators: ");
    scanf("%d", &ch);
    switch (ch) {
      case 1: AreaCalculator();
      case 2: VolumeCalculator();
      case 4: BinaryCalculator();
      case 5: EquationSolver();
      case 6: ConversionCalculator();
      case 7: SeriesCalculator();
      case 8:
        printf("The first number was: ");
        scanf("%lf", &ffirst);
        printf("arcsin(%lf) = %lf\n", ffirst, arcsin(ffirst));
        printf("arccos(%lf) = %lf\n", ffirst, arccos(ffirst));
        printf("arctan(%lf) = %lf\n", ffirst, arctan(ffirst));
        break;
      case 9:
      case 0:
    }
  } while (flag);
}

int main() {
  printf("=== Calculator ===\n");
  printf("1. Enter two numbers\n");
  printf("2. Add both numbers\n");
  printf("3. Subtract both numbers\n");
  printf("4. Multiply both numbers\n");
  printf("5. Divide first by second\n");
  printf("6. Find first number raised to second\n");
  printf("7. Find log with any positive base, of first number\n");
  printf("8. Use first number as argument for trigonometric functions\n");
  printf("9. Access other calculators\n");
  printf("0. Exit\n");

  int ch, flag = 1;
  float first = 0.0, second = 0.0;
  do {
    printf("\nEnter your choice: ");
    scanf("%d", &ch);
    switch (ch) {
      case 1:
        printf("Enter first number: ");
        scanf("%f", &first);
        printf("Enter second number: ");
        scanf("%f", &second);
        break;
      case 2:
        float addition = add(first, second);
        printf("Addition of %f and %f is: %f\n", first, second, addition);
        break;
      case 3:
        float subtraction = subtract(first, second);
        printf("Subtraction of %f and %f is: %f\n", first, second, subtraction);
        break;
      case 4:
        float multiplication = multiply(first, second);
        printf("Multiplication of %f and %f is: %f\n", first, second,
               multiplication);
        break;
      case 5:
        float division = divide(first, second);
        printf("Division of %f by %f is: %f\n", first, second, division);
        break;
      case 6:
        long long exponentiation =
            binExp((long long)(first), (long long)(second));
        printf("Exponentiation of %d raised to %d is: %lld\n", first, second,
               exponentiation);
        break;
      case 7:
        if (first <= 0) {
          printf("Logarithm undefined for non-positive values.\n");
          break;
        }
        printf("Natural logarithm of %d is: %f\n", first, loge(first));
        unsigned int base;
        printf("Choose your desired base: ");
        scanf("%u", &base);
        if (base <= 0) {
          printf("Logarithm base must be positive.\n");
          break;
        }
        printf("Logarithm with base %u is: %f\n", base,
               loge(first) / loge(base));
        break;
      case 8: {
        double radian = radians(first);
        printf("The number in radians: %f\n", radian);
        printf("sin(%d) = %f\n", first, sin(radian));
        printf("cos(%d) = %f\n", first, cos(radian));
        printf("tan(%d) = %f\n", first, sin(radian) / cos(radian));
        printf("cot(%d) = %f\n", first, cos(radian) / sin(radian));
        printf("sec(%d) = %f\n", first, 1 / cos(radian));
        printf("csc(%d) = %f\n", first, 1 / sin(radian));
      } break;
      case 9: displayOther(); break;
      case 0: flag = 0; break;
      default: printf("Invalid choice\n");
    }
  } while (flag);

  return 0;
}
