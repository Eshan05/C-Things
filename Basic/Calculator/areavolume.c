#include "areavolume.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI     3.14159265358979323846
#define ABS(x) ((x) < 0 ? -(x) : (x))

void circleCalc();
void triangleCalc();
void quadrilateralArea();
void calculateAreaParallelogram();
void calculateAreaRectangle();
void calculateAreaTrapezium();
void calculateAreaGeneralQuadrilateral();
double areaOfGeneralQuadrilateral(double x1, double y1, double x2, double y2,
                                  double x3, double y3, double x4, double y4);

void AreaCalculator() {
  int flag = 1, one;
  while (flag) {
    printf("1. Circle\n2. Triangle.\n3. Quadrilaterals\n4. Exit\n ");
    printf("Select an option: ");
    scanf("%d", &one);
    switch (one) {
      case 1: circleCalc(); break;
      case 2: triangleCalc(); break;
      case 3: quadrilateralArea(); break;
      case 4:
        printf("Exiting...");
        flag = 0;
        break;
    }
  }
  return;
}

void circleCalc() {
  int sub, select;
  float radius, area, Circumference;
  printf("Select sub-option: ");
  printf("\n1] Area of circle\n2] Circumference of circle.");
  scanf("%d", &sub);
  switch (sub) {
    case 1:
      printf("Select an option: \n1.To find "
             "area\n2.To find the radius");
      scanf("%d", &select);
      switch (select) {
        case 1:
          printf("Enter the radius of circle : ");
          scanf("%f", &radius);
          area = 3.14 * radius * radius;
          printf("The area of the circle is %f", area);
          break;

        case 2:
          printf("Enter the area of the circle : ");
          scanf("%f", &area);
          radius = sqrt(area / 3.14);
          printf("\nThe radius of the circle is : %f", radius);
          break;
        default: printf("Invalid choice.");
      }

    case 2:
      printf("Select an option : \n1.To find "
             "circumference\n2.To find radius");
      scanf("%d", &select);
      switch (select) {
        case 1:
          printf("Enter the radius of circle : ");
          scanf("%f", &radius);
          Circumference = 2 * 3.14 * radius;
          printf("\nThe Circumference of the circle is : %f", Circumference);
          break;

        case 2:
          printf("Enter the Circumference of the circle : ");
          scanf("%f", &Circumference);
          radius = Circumference / (2 * 3.14);
          printf("\nThe radius of the circle is : %f", radius);
          break;
        default: printf("Invalid choice.");
      }
    default: printf("Invalid choice.");
  }
}

void triangleCalc(void) {
  int sub, given;
  float side1, side2, side3, perimeter;
  float height, base, area;
  float half_perimeter, s;
  printf("Select One:");
  printf("\n1] Area of triangle.\n2]Perimeter\n");
  scanf("%d", &sub);
  switch (sub) {
    case 1:
      printf("Select an option based on given information:"
             "\n1.Height and Base of triangle to find Area."
             "\n2.Area and Base of triangle to find Height."
             "\n3.Height and Area of triangle to find Base."
             "\n4.Three sides to find Area. (Heron's Formula)\n");
      scanf("%d", &given);
      switch (given) {
        case 1:
          printf("Enter Height:");
          scanf("%f", &height);
          printf("Enter Base:");
          scanf("%f", &base);
          area = (base * height) / 2.00;
          printf("Area of triangle is %.2f", area);
          break;

        case 2:
          printf("Enter Area:");
          scanf("%f", &area);
          printf("Enter Base:");
          scanf("%f", &base);
          height = (2.00 * area) / base;
          printf("Height of triangle is %.2f", height);
          break;
        case 3:
          printf("Enter Height:");
          scanf("%f", &height);
          printf("Enter Area:");
          scanf("%f", &area);
          base = (2.00 * area) / height;
          printf("Base of triangle is %.2f", base);
          break;
        case 4:
          printf("Enter three sides of triangle:\n");
          scanf("%f%f%f", &side1, &side2, &side3);
          half_perimeter = (side1 + side2 + side3) / 2;
          s = half_perimeter;
          area = sqrt(s * (s - side1) * (s - side2) * (s - side3));
          printf("Area of triangle is %.2f", area);
          break;
      }

      break;
    case 2:
      printf("Enter the length of all three sides of the triangle:\n");
      scanf("%f%f%f", &side1, &side2, &side3);
      perimeter = side1 + side2 + side3;
      printf("perimeter of triangle: %.2f\n", perimeter);
      break;
  }
}

void quadrilateralArea() {
  int choice;
  while (1) {
    printf("Select the type of quadrilateral to calculate area:\n");
    printf("1. Parallelogram\n");
    printf("2. Rectangle\n");
    printf("3. Trapezium\n");
    printf("4. General Quadrilateral\n");
    printf("5. Exit\n");
    printf("Enter your choice (1-5): ");
    scanf("%d", &choice);

    switch (choice) {
      case 1: calculateAreaParallelogram(); break;
      case 2: calculateAreaRectangle(); break;
      case 3: calculateAreaTrapezium(); break;
      case 4: calculateAreaGeneralQuadrilateral(); break;
      case 5: return;
      default: printf("Invalid choice. Please try again.\n");
    }
  }
}

void calculateAreaParallelogram() {
  double base, height;
  printf("Enter the base and height of the parallelogram: ");
  scanf("%lf %lf", &base, &height);
  printf("Area of the parallelogram: %.2lf\n", base * height);
}

void calculateAreaRectangle() {
  double length, width;
  printf("Enter the length and width of the rectangle: ");
  scanf("%lf %lf", &length, &width);
  printf("Area of the rectangle: %.2lf\n", length * width);
}

void calculateAreaTrapezium() {
  double a, b, height;
  printf("Enter the lengths of the two parallel sides and the height of the "
         "trapezium: ");
  scanf("%lf %lf %lf", &a, &b, &height);
  printf("Area of the trapezium: %.2lf\n", ((a + b) / 2) * height);
}

void calculateAreaGeneralQuadrilateral() {
  double x1, y1, x2, y2, x3, y3, x4, y4;
  printf("Enter the coordinates of the four vertices of the quadrilateral:\n");
  printf("Vertex 1 (x1 y1): ");
  scanf("%lf %lf", &x1, &y1);
  printf("Vertex 2 (x2 y2): ");
  scanf("%lf %lf", &x2, &y2);
  printf("Vertex 3 (x3 y3): ");
  scanf("%lf %lf", &x3, &y3);
  printf("Vertex 4 (x4 y4): ");
  scanf("%lf %lf", &x4, &y4);

  double area = areaOfGeneralQuadrilateral(x1, y1, x2, y2, x3, y3, x4, y4);
  printf("Area of the general quadrilateral: %.2lf\n", area);
}

double areaOfGeneralQuadrilateral(double x1, double y1, double x2, double y2,
                                  double x3, double y3, double x4, double y4) {
  return ABS((x1 * y2 + x2 * y3 + x3 * y4 + x4 * y1 -
              (y1 * x2 + y2 * x3 + y3 * x4 + y4 * x1)) /
             2.0);
}

void VolumeCalculator() {
  int choice, sub;
  float l, b, h, sur_area, vol, r;

  printf("1] Surface Area\n2] Volume");
  printf("\nEnter your choice");
  scanf("%d", &choice);
  switch (choice) {
    case 1:

      printf("1. Cube\n2. Cuboid\n3. Sphere\n4. Cylinder\n5.Cone");
      printf("Give your preferred choice : ");
      scanf("%d", &sub);
      switch (sub) {
        case 1:
          printf("Enter the edge length of cube : ");
          scanf("%f", &l);
          sur_area = 6 * l * l;
          printf("The surface area of cube is : %f", sur_area);
          break;

        case 2:
          printf("Enter the length of the cuboid : ");
          scanf("%f", &l);
          printf("Enter the height of the cuboid : ");
          scanf("%f", &h);
          printf("Enter the breadth of the cuboid : ");
          scanf("%f", &b);
          sur_area = 2 * (l * b + b * h + h * l);
          printf("The surface area of cuboid is : %f", sur_area);
          break;

        case 3:
          printf("Enter the radius of the sphere : ");
          scanf("%f", &r);
          sur_area = 4 * PI * r * r;
          printf("The surface area of sphere is : %f", sur_area);
          break;

        case 4:
          printf("Enter the height of the cylinder : ");
          scanf("%f", &h);
          printf("Enter the radius of circular base of the cylinder : ");
          scanf("%f", &r);
          sur_area = 2 * PI * r * (r + h);
          printf("The surface area of the cylinder is : %f", sur_area);
          break;

        case 5:
          printf("Enter the radius of circular base of the cone : ");
          scanf("%f", &r);
          printf("Enter the slant height of the cone : ");
          scanf("%f", &l);
          sur_area = 4 * PI * r * r;
          printf("The surface area of cone is : %f", sur_area);
          break;
      }

    case 2:

      printf("1. Cube\n2. Cuboid\n3. Sphere\n4. Cylinder\n5.Cone");
      printf("\nGive your preferred choice : ");
      scanf("%d", &sub);
      switch (sub) {
        case 1:
          printf("\nEnter the edge of the cube : ");
          scanf("%f", &l);
          vol = l * l * l;
          printf("\nThe volume of cube is : %f", vol);
          break;

        case 2:
          printf("\nEnter the length of the cuboid : ");
          scanf("%f", &l);
          printf("\nEnter the height of the cuboid : ");
          scanf("%f", &h);
          printf("\nEnter the breadth of the cuboid : ");
          scanf("%f", &b);
          vol = l * b * h;
          printf("\nThe volume of cuboid is : %f", vol);
          break;

        case 3:
          printf("\nEnter the radius of sphere : ");
          scanf("%f", &r);
          vol = (4 * PI * r * r * r) / 3;
          printf("\nThe volume of sphere is : %f", vol);
          break;

        case 4:
          printf("\nEnter The radius of cylinder : ");
          scanf("%f", &r);
          printf("\nEnter the height of cylinder : ");
          scanf("%f", &h);
          vol = PI * r * r * h;
          printf("\nThe volume of cylinder is : %f", vol);
          break;

        case 5:
          printf("\nEnter the radius of base of cone : ");
          scanf("%f", &r);
          printf("\nEnter the height of the cone : ");
          scanf("%f", &h);
          vol = (PI * r * r * h) / 3;
          printf("\nThe volume of cone is : %f", vol);
          break;
      }
  }
}
