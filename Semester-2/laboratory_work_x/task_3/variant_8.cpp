#include <iostream>
#include <cmath>
#include <fstream>

int n;

int *read_array_from_file(const char *file_path) {
    std::ifstream in(file_path);

    in >> n;
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        in >> arr[i];
    }

    in.close();

    return arr;
}

int *array_remove_number_by_index(const int *array, int index, int arr_length) {
    int *new_array = new int[arr_length - 1];

    for (int i = 0; i < arr_length; ++i) {
        if (i < index) {
            new_array[i] = array[i];
        } else if (i > index) {
            new_array[i - 1] = array[i];
        }
    }

    return new_array;
}

int array_get_index_of_max_positive_odd_number(const int *array, int array_length) {
    int index = -1;
    int max_positive_odd_number = 0;

    for (int i = 0; i < array_length; ++i) {
        if (array[i] > max_positive_odd_number && array[i] % 2 != 0 && array[i] > 0) {
            index = i;
            max_positive_odd_number = array[i];
        }
    }

    return index;
}

int array_get_index_of_min_positive_even_number(const int *array, int array_length) {
    int index = -1;
    int min_positive_even_number = INT_MAX;

    for (int i = 0; i < array_length; ++i) {
        if (array[i] < min_positive_even_number && array[i] % 2 == 0 && array[i] > 0) {
            index = i;
            min_positive_even_number = array[i];
        }
    }

    return index;
}

bool number_is_perfect(int number) {
    if (number <= 1) {
        return false;
    }

    int divisors_sum = 1;

    for (int d = 2; d < round(sqrt(number)) + 1; ++d) {
        if (number % d == 0) {
            divisors_sum += d;
            divisors_sum += number / d;
        }
    }

    return divisors_sum == number;
}

int *array_get_first_two_perfect_numbers_indexes(int *array, int array_length) {
    int first_index = -1;
    int second_index = -1;
    int count = 0;

    for (int i = 0; i < array_length; ++i) {
        if (number_is_perfect(array[i])) {
            if (count == 0){
                first_index = i;
            } else if (count == 1) {
                second_index = i;

                break;
            }

            count++;
        }
    }

    return new int[2] {first_index, second_index};
}

void write_array_to_file(const char* filename, int *array, int array_length) {
    std::ofstream out(filename, std::ios::trunc);

    for (int i = 0; i < array_length; i++) {
        out << array[i] << " ";
    }

    out << "\n";

    out.close();
}

int main() {
    int *arr = read_array_from_file("C:\\Users\\Fenek\\CLionProjects\\lab_2\\task_3_input.txt");
    int new_n = n;

    for (int i = 0; i < 2; ++i) {
        int count = 0;
        int max_positive_odd_number_index = array_get_index_of_max_positive_odd_number(arr, new_n);
        int min_positive_even_number_index = array_get_index_of_min_positive_even_number(arr, new_n);
        int *perfect_numbers = array_get_first_two_perfect_numbers_indexes(arr, new_n);
        int first_perfect_number_index = perfect_numbers[0];
        int second_perfect_number_index = perfect_numbers[1];

        if (max_positive_odd_number_index != -1) {
            int *new_arr = array_remove_number_by_index(arr, max_positive_odd_number_index, new_n);
            arr = new_arr;

            count++;

            if (min_positive_even_number_index != -1 && min_positive_even_number_index > max_positive_odd_number_index) {
                min_positive_even_number_index--;
            }
            if (first_perfect_number_index != -1 && first_perfect_number_index > max_positive_odd_number_index) {
                first_perfect_number_index--;
            }
            if (second_perfect_number_index != -1 && second_perfect_number_index > max_positive_odd_number_index) {
                second_perfect_number_index--;
            }
        }
        if (min_positive_even_number_index != -1) {
            int *new_arr = array_remove_number_by_index(arr, min_positive_even_number_index, new_n);
            arr = new_arr;

            count++;

            if (first_perfect_number_index != -1 && first_perfect_number_index > min_positive_even_number_index) {
                first_perfect_number_index--;
            }
            if (second_perfect_number_index != -1 && second_perfect_number_index > min_positive_even_number_index) {
                second_perfect_number_index--;
            }
        }
        if (first_perfect_number_index != -1) {
            int *new_arr = array_remove_number_by_index(arr, first_perfect_number_index, new_n);
            arr = new_arr;

            count++;

            if (second_perfect_number_index != -1 && second_perfect_number_index > first_perfect_number_index) {
                second_perfect_number_index--;
            }
        }
        if (second_perfect_number_index != -1) {
            int *new_arr = array_remove_number_by_index(arr, second_perfect_number_index, new_n);
            arr = new_arr;

            count++;
        }

        new_n -= count;
        delete[] perfect_numbers;

        write_array_to_file("C:\\Users\\Fenek\\CLionProjects\\lab_2\\task_3_output.txt", arr, new_n);
    }

    delete[] arr;
}
