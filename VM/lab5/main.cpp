#include <iostream>
#include <cmath>
#include <limits>

double f(double x) {
    return exp(-x * x); 
}

double integrate(double a, double b, int N) {
    double h = (b - a) / N; 
    double integral = 0.0;

    for (int i = 0; i < N; i++) {
        integral += f(a + i * h); 
    }

    integral *= h; 

    return integral;
}

int main() {
    double epsylon;
    
    std::cout << "Введите желаемую погрешность (epsylon): ";
    std::cin >> epsylon;

    double a = -5.0;
    double b = 5.0;

    int N = 1; 
    double integral_prev = 0.0;
    double integral_current = integrate(a, b, N);
    
    do {
        integral_prev = integral_current;
        N *= 2; 
        integral_current = integrate(a, b, N);
    } while (fabs(integral_current - integral_prev) > epsylon && N < std::numeric_limits<int>::max() / 2);
    
    std::cout << "Приближенное значение интеграла: " << integral_current << std::endl;

    return 0;
}
