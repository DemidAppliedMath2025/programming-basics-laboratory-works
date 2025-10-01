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
        std::string output;

        std::cout << "Now enter the numbers themselves" << "\n";
        std::cin >> input;

        while (!input) {
            std::cout << "The input is not a natural number";
            std::cin >> input;
        }

        numbers[0] = input;

        for (int i = 1; i < n; i++) {
            std::cin >> input;

            if (!input) {
                std::cout << "The input is not a natural number";
            }

            numbers[i] = input;

            double x1 = -sqrt(numbers[i] - numbers[i - 1]);
            double x2 = -sqrt(numbers[i] - numbers[i - 1]);

            !(((static_cast<int>(x1) >> 31) & 1) && ((static_cast<int>(x2) >> 31) & 1)) ? output += std::to_string(input) : output += "";
        }

        if (output.empty()) {
            std::cout << "No such elements that fit the condition";
        } else {
            std::cout << output;
        }
    } catch (...) {
        std::cout << "Argument is not an integer";
    }
}
