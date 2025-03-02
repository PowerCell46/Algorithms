#include <iostream>
#include <vector>
#include <sstream>

#define END 'e'
#define WALL '*'
#define VISITED 'v'


void find_all_paths(const int &row, const int &col, char **matrix, const int &rowSize, const int &colSize, const char &direction, std::vector<char> &pathVector) {
    if (row < 0 || col < 0 || row >= rowSize || col >= colSize) // Out of the matrix
        return;
    if (matrix[row][col] == WALL) { // Hitting a wall
        return;
    }
    if (matrix[row][col] == VISITED) { // Hitting a visited place
        return;
    }

    pathVector.push_back(direction); // Add the direction

    if (matrix[row][col] == END) { // Hitting the end
        for (std::vector<char>::iterator iter = pathVector.begin() + 1; iter != pathVector.end(); ++iter)
            std::cout << *iter << ' ';
        std::cout << '\n';
        pathVector.pop_back();
        return;
    }

    matrix[row][col] = VISITED; 

    find_all_paths(row + 1, col, matrix, rowSize, colSize, 'D', pathVector);
    find_all_paths(row - 1, col, matrix, rowSize, colSize, 'U', pathVector);
    find_all_paths(row, col + 1, matrix, rowSize, colSize, 'R', pathVector);
    find_all_paths(row, col - 1, matrix, rowSize, colSize, 'L', pathVector);

    pathVector.pop_back();
    matrix[row][col] = '-';
}


int main() {
    int rows, cols;
    std::cin >> rows >> cols;

    char **matrix = new char *[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new char[cols];

        for (int j = 0; j < cols; ++j)
            std::cin >> matrix[i][j];
    }

    std::vector<char> pathVector;
    find_all_paths(0, 0, matrix, rows, cols, '.', pathVector);

    for (int i = 0; i < rows; ++i)
        delete[] matrix[i];
    delete[] matrix;

    return 0;
}

/*
3
3
---
-*-
--e
*/
