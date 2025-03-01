#include <iostream>
#include <sstream>


bool checkIfEndBinaryNumIsReached(const int* binaryRow, const int& size);

void printArrayRow(const int* row, const int& size);


int main() {
    int rowSize;
    std::cin >> rowSize;

    int* binaryRow = new int[rowSize]{};

    while (!checkIfEndBinaryNumIsReached(binaryRow, rowSize)) { // Repeat while the whole row != all 1s
        for (int i = rowSize - 1; i > -1; --i) { // Iterate from the last digit to the first one
            if (binaryRow[i] == 1) // If the current one is = 1: skip it
                continue;

            ++binaryRow[i]; // If it's = 0: increment it
            for (int j = i + 1; j < rowSize; ++j) // Make all digits to the right 0s
                binaryRow[j] = 0;

            printArrayRow(binaryRow, rowSize);
            break;
        }
    }

    delete[] binaryRow;

    return 0;
}


bool checkIfEndBinaryNumIsReached(const int* binaryRow, const int& size) {
    for (int i = 0; i < size; ++i)
        if (binaryRow[i] != 1)
            return false;
    return true;
}


void printArrayRow(const int* row, const int& size) {
    for (int i = 0; i < size; ++i)
        std::cout << row[i] << ' ';
    std::cout << '\n';
}
