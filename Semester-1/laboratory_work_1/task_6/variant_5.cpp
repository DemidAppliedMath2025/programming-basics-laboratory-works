#include <vector>
#include <iostream>

int main() {
    std::vector<unsigned int> numbers;
    unsigned int input = 1;
    int i = -1;

    std::cout << "Enter as many numbers as you want. Once you're done, enter any symbol that is not a natural number" << "\n";

    while (true) {
        std::cin >> input;

        if (!input) {
            break;
        }

        i++;
        numbers.push_back(input);
    }

    std::cout << "No such elements that fulfill the condition";
}
