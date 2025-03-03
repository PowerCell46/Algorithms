#include <iostream>
#include <sstream>


void reverseArray(int* arr, const int& arrSize, const int& index) {
    if (index == arrSize / 2)
        return;
    arr[index] ^= arr[arrSize - 1 - index];
    arr[arrSize - 1 - index] ^= arr[index];
    arr[index] ^= arr[arrSize - 1 - index];

    reverseArray(arr, arrSize, index + 1);
}


int main() {
    int* arr = new int[4]{1, 2, 3, 4};

    reverseArray(arr, 4, 0);

    for (int i = 0; i < 4; ++i)
        std::cout << arr[i] << ' ';

    return 0;
}
