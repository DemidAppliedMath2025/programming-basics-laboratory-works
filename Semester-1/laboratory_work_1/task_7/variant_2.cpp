#include <iostream>
#include <cmath>

double factorial(int number) {
    double new_num = 1;

    for (int i = 2; i < number + 1; ++i) {
        new_num *= i;
    }

    return new_num;
}

double power(double number, double _power) {
    double new_num = 1;

    for (int i = 0; i < _power; ++i) {
        new_num *= number;
    }

    return new_num;
}

double cos_by_row(double x) {
    double num = 1;
    double new_x = fmod(x, 2 * M_PI);

    for (int n = 1; n < 30; ++n) {
        num += power(-1, n) * ((power(new_x, 2 * n) / factorial(2 * n)));
    }

    return num;
}

double cos_by_recursion(double x, int n) {
    double new_x = fmod(x, 2 * M_PI);

    if (n == 30) {
        return 0;
    }

    return power(-1, n) * ((power(new_x, 2 * n) / factorial(2 * n))) + cos_by_recursion(new_x, n + 1);
}

int main() {
    int N, eps;
    double A, B;

    std::cin >> N >> A >> B >> eps;

    double step = (B - A) / N;
    double number = A;

    std::cout << "\n" << "      f1     f2     f3" << "\n";

    for (int n = 0; n < N; ++n) {
        number += step;

        if (fabs(cos_by_row(number)) > 1) {
            std::cout << number << ": " << "The number is outside the convergence of the series" << "\n";
        } else {
            std::cout << number << ": " << std::fixed << std::setprecision(eps) << cos(number) << " " << cos_by_row(number) << " " << cos_by_recursion(number, 0) << "\n";
        }
    }
}
