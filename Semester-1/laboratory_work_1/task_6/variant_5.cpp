#include <vector>
#include <iostream>

int main() {
    int n;

    std::cout << "Enter the amount of numbers you want to input" << "\n";
    std::cin >> n;

    int input;
    int numbers[n];
    std::string output;

    std::cout << "Now enter the numbers themselves" << "\n";
    std::cin >> input;

    numbers[0] = input;

    for (int i = 1; i < n; ++i) {
        std::cin >> input;

        if (!input) {
            std::cout << "The input is not a natural number";
        }

        numbers[i] = input;

        double x1 = -sqrt(numbers[i - 1] - numbers[i]);
        double x2 = -sqrt(numbers[i - 1] - numbers[i]);

        !(((static_cast<int>(x1) >> 31) & 1) && ((static_cast<int>(x2) >> 31) & 1)) ? output += std::to_string(input) : output += "";
    }

    if (output.empty()) {
        std::cout << "No such elements that fit the condition";
    } else {
        std::cout << output;
    }
}
