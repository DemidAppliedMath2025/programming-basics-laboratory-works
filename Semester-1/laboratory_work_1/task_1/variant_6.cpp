#include <cmath>
#include <iostream>
#include <iomanip>

double expression_a(double p, double q) {
    double denominator = pow((sqrt(pow(p, 3)) / sqrt(p) + p), 0.25) / pow(pow((p - q), 3), 0.125);
    double divisor = pow(sqrt(p) / (sqrt(p) - sqrt(q)) - sqrt(p / q) + 1, 0.25);

    return denominator / divisor;
}

double expression_b(double p, double q) {
    return 1 / (pow(p - q, 0.125));
}

int main() {
    std::string str_p, str_q;

    std::cin >> str_p >> str_q;

    try {
        double p = std::stod(str_p);
        double q = std::stod(str_q);

        if (!(p != q && p >= 0 && q > 0 && sqrt(p) / (sqrt(p) - sqrt(q)) - sqrt(p / q) + 1 > 0)) {
            std::cout << "Numbers don't fit in range";
        } else {
            std::cout << std::fixed << std::setprecision(6) << expression_a(p, q) - expression_b(p, q);
        }
    } catch (...) {
        std::cout << "Some argument(s) is(are) not number(s)";
    }
}
