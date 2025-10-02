#include <iostream>
#include <cmath>

int main() {
    double a, b, r, d, e;

    std::cin >> a >> b >> r >> d >> e;

    double coefficient_a = pow(d, 2) + 1;
    double coefficient_b = -2 * a + 2 * d * e - 2 * b * d;
    double coefficient_c = pow(a, 2) + pow(b, 2) + pow(e, 2) - pow(r, 2) - 2 * b * e;

    double discriminant = pow(coefficient_b, 2) - 4 * coefficient_a * coefficient_c;

    if (discriminant > 0) {
        double x_1 = (-coefficient_b + sqrt(discriminant)) / (2 * coefficient_a) + 0.0;
        double x_2 = (-coefficient_b - sqrt(discriminant)) / (2 * coefficient_a) + 0.0;

        std::cout << x_1 << " " << d * x_1 + e << "\n";
        std::cout << x_2 << " " << d * x_2 + e << "\n";
    } else if (discriminant == 0) {
        double x = (-coefficient_b) / (2 * coefficient_a) + 0.0;

        std::cout << x << " " << d * x + e;
    } else {
        std::cout << "No solutions";
    }
}
