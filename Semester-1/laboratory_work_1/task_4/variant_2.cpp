#include <iostream>
#include <cmath>
#include <vector>

bool is_included_in_first_area(double x, double y) {
    if (x <= 0) {
        return sqrt(pow(x, 2) + pow(y, 2)) <= 2;
    } else {
        if (y > 0) {
            return y <= -x + 2;
        } else {
            return y >= x - 2;
        }
    }
}

bool is_included_in_second_area(double x, double y) {
    double new_x = fmod(x, 4);
    double new_y = fmod(y, 4);

    if (fmod(y, 8) > 4) {
        new_x += 2;
        new_x = fmod(new_x, 4);
    }

    return !(
        ((0 < new_x && new_x < 1) && (1 < new_y && new_y < 2)) ||
        ((2 < new_x && new_x < 3) && (0 < new_y && new_y < 1)) ||
        ((1 < new_x && new_x < 3) && (2 < new_y && new_y < 3)) ||
        ((2 < new_x && new_x < 4) && (3 < new_y && new_y < 4)) ||
        ((3 < new_x && new_x < 4) && (0 < new_y && new_y < 2))
    );
}

int main() {
    double x, y;

    std::cin >> x >> y;

    if (is_included_in_first_area(x, y)) {
        std::cout << "Is included in first area" << "\n";
    } else {
        std::cout << "Isn't included in first area" << "\n";
    }

    if (is_included_in_second_area(x, y)) {
        std::cout << "Is included in second area" << "\n";
    } else {
        std::cout << "Isn't included in second area" << "\n";
    }
}
