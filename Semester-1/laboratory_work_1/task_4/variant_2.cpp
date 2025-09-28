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
    int y_row = static_cast<int>(ceil(y));
    int x_column = static_cast<int>(ceil(x));

    if (x > 10 || y > 10) {
        return false;
    }

    const int N = 10;
    int table[N][N] = {
        {1, 1, 0, 0, 1, 1, 0, 0, 1, 1},
        {0, 1, 1, 0, 0, 1, 1, 0, 0, 1},
        {1, 0, 0, 1, 1, 0, 0, 1, 1, 0},
        {1, 1, 0, 0, 1, 1, 0, 0, 1, 1},
        {0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
        {1, 0, 0, 1, 1, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 1, 1, 0, 0, 1},
        {0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
        {1, 1, 0, 0, 1, 1, 0, 0, 1, 1},
        {0, 1, 1, 0, 0, 1, 1, 0, 0, 1}
    };

    if ((x_column - 1 < x && x < x_column) && (y_row - 1 < y && y < y_row) && !(table[y_row - 1][x_column - 1])) {
        return false;
    } else {
        if (table[y_row - 1][x_column - 1]) {
            return true;
        }

        if (x == x_column && y != y_row && x != 10) {
            if (table[y_row - 1][x_column]) {
                return true;
            }
        } else if (x != x_column && y == y_row && y != 10) {
            if (table[y_row][x_column - 1]) {
                return true;
            }
        } else if (x == x_column && y == y_row) {
            if (table[y_row - 1][x_column] || table[y_row][x_column] || table[y_row][x_column - 1]) {
                return true;
            }
        }

        return false;
    }
}

int main() {
    std::string x_str, y_str;

    std::cin >> x_str;
    std::cin >> y_str;

    try {
        double x = std::stod(x_str);
        double y = std::stod(y_str);

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
    } catch (...) {
        std::cout << "Some argument(s) is(are) not number(s)";
    }
}
