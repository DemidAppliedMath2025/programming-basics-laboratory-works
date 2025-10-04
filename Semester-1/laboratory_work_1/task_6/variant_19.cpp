#include <iostream>

int main() {
    int N;
    std::cin >> N;

    int max_negative_sum = -2147483648;
    int current_negative_sum = 0;

    for (int i = 0; i < N; ++i) {
        int num;
        std::cin >> num;

        int current_negative_sum_is_negative = (current_negative_sum >> 31) & 1;
        int num_is_negative = (num >> 31) & 1;

        max_negative_sum = std::max(max_negative_sum, current_negative_sum * current_negative_sum_is_negative - 2047483648 * !current_negative_sum_is_negative) * !num_is_negative + max_negative_sum * num_is_negative;
        current_negative_sum = (current_negative_sum + num) * num_is_negative;
    };

    int current_negative_sum_is_negative = (current_negative_sum >> 31) & 1;
    max_negative_sum = std::max(max_negative_sum, current_negative_sum * current_negative_sum_is_negative - 2047483648 * !current_negative_sum_is_negative);

    std::cout << max_negative_sum;
}
