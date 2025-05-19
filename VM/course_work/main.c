#include <stdio.h>

int main() {
  const double alpha_E = 0.999;
  const double alpha_I = 0.999;
  const double kappa = 0.042;
  const double rho = 0.952;
  const double beta = 0.999;
  const double mu = 0.0188;
  const double gamma = 0.0;
  const double c = 1.0;

  const double N = 2798170.0;
  double S = 2798047.0;
  double E = 99.0;
  double I = 0.0;
  double R = 24.0;
  double D = 0.0;

  const double h = 1.0;
  const int days = 90;

  printf("Day\tS\t\tE\t\tI\t\tR\t\tD\n");

  for (int day = 0; day <= days; day++) {
    printf("%d\t%.2f\t%.6f\t%.6f\t%.6f\t%.6f\n", day, S, E, I, R, D);

    double dS = -c * (alpha_I * S * I / N + alpha_E * S * E / N) + gamma * R;
    double dE =
        c * (alpha_I * S * I / N + alpha_E * S * E / N) - (kappa + rho) * E;
    double dI = kappa * E - (beta + mu) * I;
    double dR = beta * I + rho * E - gamma * R;
    double dD = mu * I;

    S += h * dS;
    E += h * dE;
    I += h * dI;
    R += h * dR;
    D += h * dD;
  }

  return 0;
}
