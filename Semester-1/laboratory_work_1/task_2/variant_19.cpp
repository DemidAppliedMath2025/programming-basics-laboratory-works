#include <iostream>

int main() {
    std::string a_str, b_str, r_str, d_str, e_str;

    std::cin >> a_str >> b_str >> r_str >> d_str >> e_str;

    try {
        double a = std::stod(a_str);
        double b = std::stod(b_str);
        double r = std::stod(r_str);
        double d = std::stod(d_str);
        double e = std::stod(e_str);

        double coefficient_a = pow(d, 2) + 1;
        double coefficient_b = -2 * a + 2 * d * e - 2 * b * d;
        double coefficient_c = pow(a, 2) + pow(b, 2) + pow(e, 2) - pow(r, 2) - 2 * b * e;

        double discriminant = pow(coefficient_b, 2) - 4 * coefficient_a * coefficient_c;

        if (discriminant > 0) {
            double x_1 = (-coefficient_b + sqrt(discriminant)) / (2 * coefficient_a);
            double x_2 = (-coefficient_b - sqrt(discriminant)) / (2 * coefficient_a);

            std::cout << x_1 << " " << x_2;
        } else if (discriminant == 0) {
            double x = (-coefficient_b) / 2 * coefficient_a;

            std::cout << x;
        } else {
            std::cout << "No solutions";
        }
    } catch (...) {
        std::cout << "Some argument(s) is(are) not number(s)";

        return;
    }
}
