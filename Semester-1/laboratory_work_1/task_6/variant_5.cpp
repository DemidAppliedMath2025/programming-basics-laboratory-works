#include <vector>
#include <iostream>

int main() {
    std::string n_str;

    std::cout << "Enter the amount of numbers you want to input" << "\n";
    std::cin >> n_str;

    try {
        int n = std::stoi(n_str);
        int input;
        int numbers[n];

        for (int i = 0; i < n; i++) {
            std::cin >> input;

            if (!input) {
                std::cout << "The input is not a natural number";
            }

            numbers[i] = input;
        }

        std::cout << "No such elements that fulfill the condition";
    } catch (...) {
        std::cout << "Argument is not an integer";
    }
}
