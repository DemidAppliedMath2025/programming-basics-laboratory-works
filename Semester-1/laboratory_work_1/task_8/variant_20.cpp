#include <iostream>
#include <cmath>

double f1(double x) {
    return asin(x) / sqrt(3);
}

double f2(double x) {
    return -cos(exp(x));
}

double f3(double x) {
    return std::log(std::abs(x - 1)) / 2 - std::log(std::abs(x + 1)) / 2;
}

double f4(double x) {
    return sqrt(x * x + 1) * atan(x) - std::log(sqrt(x * x + 1) + x);
}

double rectangle_method(double a, double b, double n, double (*func)(double)) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        double xi = a + i * h;
        sum += h * func(xi);
    }

    return sum;
}

double trapezoid_method(double a, double b, double n, double (*func)(double)) {
    double h = (b - a) / n;
    double sum = func(a) + func(b);

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += 2 * func(x);
    }

    return (h / 2.0) * sum;
}

double simpson_method(double a, double b, double n, double (*func)(double)) {
    if (fmod(n, 2) != 0) {
        n++;
    }

    double h = (b - a) / n;
    double sum = func(a) + func(b);

    for (int i = 1; i < n; i++) {
        double x_i = a + i * h;

        if (i % 2 == 0) {
            sum += 2 * func(x_i);
        } else {
            sum += 4 * func(x_i);
        }
    }

    return (h / 3.0) * sum;
}

void first_integral() {
    double rectangle_meth = rectangle_method(4, 3, 1000, f1);
    double trapezoid_meth = trapezoid_method(4, 3, 1000, f1);
    double simpson_meth = simpson_method(4, 3, 1000, f1);

    std::cout << "1" << "\n";

    if (std::isnan(rectangle_meth) || std::isnan(trapezoid_meth) || std::isnan(simpson_meth)) {
        std::cout << "Integral value does not belong to R" << "\n\n";
    } else if (rectangle_meth == INFINITY || trapezoid_meth == INFINITY || simpson_meth == INFINITY) {
        std::cout << "The integral diverges" << "\n\n";
    } else {
        std::cout << rectangle_method(4, 3, 1000, f1) << "\n";
        std::cout << trapezoid_method(4, 3, 1000, f1) << "\n";
        std::cout << simpson_method(4, 3, 1000, f1) << "\n\n";
    }
}

void second_integral() {
    double rectangle_meth = rectangle_method(-2 * M_PI / 7, 2 * M_PI / 7, 1000, f2);
    double trapezoid_meth = trapezoid_method(-2 * M_PI / 7, 2 * M_PI / 7, 1000, f2);
    double simpson_meth = simpson_method(-2 * M_PI / 7, 2 * M_PI / 7, 1000, f2);

    std::cout << "2" << "\n";

    if (std::isnan(rectangle_meth) || std::isnan(trapezoid_meth) || std::isnan(simpson_meth)) {
        std::cout << "Integral value does not belong to R" << "\n\n";
    } else if (rectangle_meth == INFINITY || trapezoid_meth == INFINITY || simpson_meth == INFINITY) {
        std::cout << "The integral diverges" << "\n\n";
    } else {
        std::cout << rectangle_method(-2 * M_PI / 7, 2 * M_PI / 7, 1000, f2) << "\n";
        std::cout << trapezoid_method(-2 * M_PI / 7, 2 * M_PI / 7, 1000, f2) << "\n";
        std::cout << simpson_method(-2 * M_PI / 7, 2 * M_PI / 7, 1000, f2) << "\n\n";
    }
}

void third_integral() {
    double rectangle_meth = rectangle_method(-7, -1, 1000, f3);
    double trapezoid_meth = trapezoid_method(-7, -1, 1000, f3);
    double simpson_meth = simpson_method(-7, -1, 1000, f3);

    std::cout << "3" << "\n";

    if (std::isnan(rectangle_meth) || std::isnan(trapezoid_meth) || std::isnan(simpson_meth)) {
        std::cout << "Integral value does not belong to R" << "\n\n";
    } else if (rectangle_meth == INFINITY || trapezoid_meth == INFINITY || simpson_meth == INFINITY) {
        std::cout << "The integral diverges" << "\n\n";
    } else {
        std::cout << rectangle_method(-7, -1, 1000, f3) << "\n";
        std::cout << trapezoid_method(-7, -1, 1000, f3) << "\n";
        std::cout << simpson_method(-7, -1, 1000, f3) << "\n\n";
    }
}

void fourth_integral() {
    double rectangle_meth = rectangle_method(-2 * M_PI, 2 * M_PI, 1000, f4);
    double trapezoid_meth = trapezoid_method(-2 * M_PI, 2 * M_PI, 1000, f4);
    double simpson_meth = simpson_method(-2 * M_PI, 2 * M_PI, 1000, f4);

    std::cout << "4" << "\n";

    if (std::isnan(rectangle_meth) || std::isnan(trapezoid_meth) || std::isnan(simpson_meth)) {
        std::cout << "Integral value does not belong to R" << "\n\n";
    } else if (rectangle_meth == INFINITY || trapezoid_meth == INFINITY || simpson_meth == INFINITY) {
        std::cout << "The integral diverges" << "\n\n";
    } else {
        std::cout << rectangle_method(-2 * M_PI, 2 * M_PI, 1000, f4) << "\n";
        std::cout << trapezoid_method(-2 * M_PI, 2 * M_PI, 1000, f4) << "\n";
        std::cout << simpson_method(-2 * M_PI, 2 * M_PI, 1000, f4) << "\n";
    }
}

int main() {
    first_integral();
    second_integral();
    third_integral();
    fourth_integral();
}
