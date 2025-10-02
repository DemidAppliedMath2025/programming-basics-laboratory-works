#include <iostream>

bool expression_a(int x, int y, int z) {
    return !(!x && y || x && !y) || x || x && z;
}

bool expression_b(int x, int y, int z) {
    return !(x || z && (x || !z)) || (!x && y || x && !y);
}

int main() {
    std::cout << "x y z A B" << "\n";

    for (int x = 0; x < 2; x ++) {
        for (int y = 0; y < 2; y++) {
            for (int z = 0; z < 2; z++) {
                std::cout << x << " " << y << " " << z << " " << expression_a(x, y, z) << " " << expression_b(x, y, z) << "\n";
            }
        }
    }
}
