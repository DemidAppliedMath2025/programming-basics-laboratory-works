#include <iostream>

int main() {
    int n, L;

    std::cin >> n;
    std::cin >> L;

    int *array = new int[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    int new_n = 0;
    int current_index = 0;

    while (current_index < n) {
        int current = array[current_index];
        int current_series_length = 1;

        while (current_index + current_series_length < n && array[current_index + current_series_length] == current) {
            current_series_length++;
        }

        if (current_series_length < L) {
            new_n++;
        } else {
            new_n += current_series_length;
        }

        current_index += current_series_length;
    }

    int *new_array = new int[new_n];
    new_n = 0;
    current_index = 0;

    while (current_index < n) {
        int current = array[current_index];
        int current_series_length = 1;

        while (current_index + current_series_length < n && array[current_index + current_series_length] == current) {
            current_series_length++;
        }

        if (current_series_length < L) {
            new_array[new_n] = 0;
            new_n++;
        } else {
            for (int d = 0; d < current_series_length; ++d) {
                new_array[new_n] = current;
                new_n++;
            }
        }

        current_index += current_series_length;
    }

    for (int i = 0; i < new_n; ++i) {
        std::cout << new_array[i] << " ";
    }

    delete[] array;
    delete[] new_array;

    return 0;
}
