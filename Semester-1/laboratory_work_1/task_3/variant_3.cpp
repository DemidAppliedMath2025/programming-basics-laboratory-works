#include <iostream>

int main() {
    // "ИКС+ИСК=КСИ";

    for (int i = 0; i < 10; ++i) {
        for (int k = 0; k < 10; ++k) {
            for (int s = 0; s < 10; ++s) {
                int first = i * 100 + k * 10 + s;
                int second = i * 100 + s * 10 + k;
                int third = k * 100 + s * 10 + i;

                if (first + second == third && first != second != third) {
                    std::cout << "I: " << i << "\n";
                    std::cout << "K: " << k << "\n";
                    std::cout << "S: " << s << "\n";
                    std::cout << "\n";
                }
            }
        }
    }
}
