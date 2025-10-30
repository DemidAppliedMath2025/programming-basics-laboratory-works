#include <iostream>
#include <algorithm>

int sort_alg(int x, int y) {
    return x >= 0 && y < 0;
}

int main() {
    int n;
    std::cin >> n;

    int array[100];

    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    std::sort(array, array + n, sort_alg);

    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << " ";
    }

    return 0;
}
