#include <iostream>
#include <cmath>

double factorial(int number) {
    double new_num = 1;

    for (int i = 2; i < number + 1; i++) {
        new_num *= i;
    }

    return new_num;
}

double power(double number, double _power) {
    double new_num = 1;

    for (int i = 0; i < _power; i++) {
        new_num *= number;
    }

    return new_num;
}

double cos_by_row(double x) {
    double num = 1;

    for (int n = 1; n < 30; n++) {
        num += power(-1, n) * ((power(x, 2 * n) / factorial(2 * n)));
    }

    return num;
}

double cos_by_recursion(double x, int n) {
    if (n == 30) {
        return 0;
    }

    return power(-1, n) * ((power(x, 2 * n) / factorial(2 * n))) + cos_by_recursion(x, n + 1);
}

int main() {
    std::string N_str, A_str, B_str, eps_str;

    std::cin >> N_str >> A_str >> B_str >> eps_str;

    try {
        int N = std::stoi(N_str);
        double A = std::stod(A_str);
        double B = std::stod(B_str);
        int eps = std::stoi(eps_str);

        std::vector<double> numbers;

        std::cout << "\nEnter N amount of points (x)\n";

        for (int n = 0; n < N; n++) {
            std::string number_str;
            std::cin >> number_str;
            double number = std::stod(number_str);

            if (A <= number && number <= B) {
                numbers.push_back(number);
            } else {
                std::cout << "This point (x) is out of range [A; B]\n";
            }
        }

        std::cout << "\n";

        for (double x : numbers) {
            std::cout << std::fixed << std::setprecision(eps)  << cos(x) << " " << cos_by_row(x) << " " << cos_by_recursion(x, 0) << "\n";
        }

    } catch (...) {
        std::cout << "Some argument(s) is(are) not number(s)";
    }
}
