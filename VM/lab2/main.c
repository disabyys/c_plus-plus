#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EXP 2.718281
#define EPSILON 1e-6
#define STEP 0.1

double f(double);
void locate_root(double *, double *, double);
double steffensense_method(double);

int main() {
  double border_a, border_b;

  printf("Enter the border a:___\b\b");
  scanf("%lf", &border_a);
  printf("Enter the border b:___\b\b");
  scanf("%lf", &border_b);

  locate_root(&border_a, &border_b, STEP);
  printf("Root is located in the interval [%.1f; %.1f]\n", border_a, border_b);

  double root =
      steffensense_method((border_a + border_b) / 2); // middle of interval
  printf("root = %f\n", root);
  printf("%f\n", f(2.0));
  return 0;
}

void locate_root(double *a, double *b, double step) {
  while (*a < *b) {
    if (f(*a) * f(*a + step) < 0) // the root in the interval
    {
      *b = *a + step;
      return;
    }
    *a += step;
  }
  *a = *b = 0;
  fprintf(stderr, "the interval does not contain a root.\n");
  exit(EXIT_FAILURE);
}

double steffensense_method(double x0) {
  double fx0 = f(x0);
  double x1;

  while (fabs(fx0) > EPSILON) {
    x1 = x0 - (pow(f(x0), 2)) / (f(x0 + f(x0)) - f(x0));
    fx0 = f(x1);
    x0 = x1;
  }

  return x0;
}

double f(double x) {
  return 3 - 0.5 * sqrt(x) - pow(EXP, (-0.5 * (pow(x, 2))));
}
