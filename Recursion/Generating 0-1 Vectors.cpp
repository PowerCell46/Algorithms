#include <iostream>
#include <sstream>


bool checkIfEndBinaryNumIsReached(const int* binaryRow, const int& size);

void printArrayRow(const int* row, const int& size);

void generateBinarySequence(const int& index, int*vector, const int& vectorSize);


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


void generateBinarySequence(const int& index, int*vector, const int& vectorSize) {
    if (index == vectorSize) {
        printArrayRow(vector, vectorSize);
        return;
    }

    for (int i = 0; i < 2; ++i) {
        vector[index] = i;
        generateBinarySequence(index + 1, vector, vectorSize);
    }
}


/*
0--
    00-
        000 -> 1. End
        001 -> 2. End

    01-
        010 -> 3. End
        011 -> 4. End
1--
    10-
        100 -> 5. End
        101 -> 6. End

    11-
        110 -> 7. End
        111 -> 8. End

----------
| 1. 000 |
|--------|
| 2. 001 |
|--------|
| 3. 010 |
|--------|
| 4. 011 |
|--------|
| 5. 100 |
|--------|
| 6. 101 |
|--------|
| 7. 110 |
|--------|
| 8. 111 |
----------
*/
