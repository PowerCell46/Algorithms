#include <iostream>
#include <sstream>

struct MatrixElement {
    int row;
    int column;
    int element;
};

class SparseMatrix {
    int rows; // Matrix dimensions
    int columns; // Matrix dimensions
    int nonZeroElements; // Number of non-empty values
    MatrixElement **matrixElements; // Dynamic array of the non-empty values
    int currentMatrixElementIndex; // Index for keeping track of the currently added non-empty value

public:
    SparseMatrix(const int &rows, const int &columns, const int &nonZeroElements)
        : rows(rows), columns(columns), nonZeroElements(nonZeroElements),
          matrixElements(new MatrixElement *[nonZeroElements]{}), currentMatrixElementIndex(-1) {}

    SparseMatrix(const SparseMatrix& other) :
        rows(other.rows), columns(other.columns), nonZeroElements(other.nonZeroElements),
        matrixElements(new MatrixElement *[other.nonZeroElements]{}), currentMatrixElementIndex(other.currentMatrixElementIndex) {
        for (int i = 0; i < other.currentMatrixElementIndex + 1; ++i) {
            const MatrixElement* otherCurrentMatrixElement = *(other.matrixElements + i);
            *(this->matrixElements + i) = new MatrixElement{
                otherCurrentMatrixElement->row,
                otherCurrentMatrixElement->column,
                otherCurrentMatrixElement->element};
        }
    }

    ~SparseMatrix() {
        for (int i = 0; i < this->currentMatrixElementIndex + 1; ++i)
            if (this->matrixElements)
                delete this->matrixElements[i];
        delete[] this->matrixElements;
    }

    SparseMatrix& operator=(const SparseMatrix& other) {
        if (this == &other)
            return *this;

        for (int i = 0; i < this->currentMatrixElementIndex + 1; ++i)
            delete this->matrixElements[i];
        delete[] this->matrixElements;

        this->rows = other.rows;
        this->columns = other.columns;
        this->nonZeroElements = other.nonZeroElements;
        this->matrixElements = new MatrixElement *[other.nonZeroElements];
        this->currentMatrixElementIndex = other.currentMatrixElementIndex;

        for (int i = 0; i < other.currentMatrixElementIndex + 1; ++i) {
            const MatrixElement* otherCurrentMatrixElement = *(other.matrixElements + i);
            *(this->matrixElements + i) = new MatrixElement{
                otherCurrentMatrixElement->row,
                otherCurrentMatrixElement->column,
                otherCurrentMatrixElement->element};
        }
        return *this;
    }

    SparseMatrix(SparseMatrix&& other) noexcept // Move constructor
    : rows(other.rows), columns(other.columns), nonZeroElements(other.nonZeroElements),
      matrixElements(other.matrixElements), currentMatrixElementIndex(other.currentMatrixElementIndex) {
        other.matrixElements = nullptr;
        other.currentMatrixElementIndex = -1;
    }

    void addElement(const int &row, const int &column, const int &element) {
        if (this->currentMatrixElementIndex + 1 >= this->nonZeroElements)
            return;
        *(this->matrixElements + (++this->currentMatrixElementIndex)) = new MatrixElement{row, column, element};
    }

    [[nodiscard]] int getElement(const int &row, const int &column) const {
        for (int i = 0; i < this->currentMatrixElementIndex + 1; ++i)
            if (row == this->matrixElements[i]->row && column == this->matrixElements[i]->column)
                return this->matrixElements[i]->element;

        return 0;
    }

    SparseMatrix operator+(const SparseMatrix &other) const {
        // if (other.columns == this->columns && other.rows == this->rows) {
        SparseMatrix resultAddition{
            this->rows,
            this->columns,
            this->nonZeroElements + other.nonZeroElements
        };

        for (int i = 0; i < this->currentMatrixElementIndex + 1; ++i) {
            for (int j = 0; j < other.currentMatrixElementIndex + 1; ++j) {
                if (
                    this->matrixElements[i]->column == other.matrixElements[j]->column &&
                    this->matrixElements[i]->row == other.matrixElements[j]->row
                ) {
                    resultAddition.addElement(
                        this->matrixElements[i]->row,
                        this->matrixElements[i]->column,
                        this->matrixElements[i]->element + other.matrixElements[j]->element
                    );
                    goto elementFound;
                }
            }
            resultAddition.addElement(
                this->matrixElements[i]->row,
                this->matrixElements[i]->column,
                this->matrixElements[i]->element
            );
        elementFound:
        }

        for (int i = 0; i < other.currentMatrixElementIndex + 1; ++i) {
            for (int j = 0; j < this->currentMatrixElementIndex + 1; ++j) {
                if (
                    other.matrixElements[i]->column == this->matrixElements[j]->column &&
                    other.matrixElements[i]->row == this->matrixElements[j]->row
                )
                    goto elementFound2;
            }
            resultAddition.addElement(
                other.matrixElements[i]->row,
                other.matrixElements[i]->column,
                other.matrixElements[i]->element
            );
        elementFound2:
        }

        resultAddition.nonZeroElements = resultAddition.currentMatrixElementIndex + 1;
        return resultAddition;
        // }
    }

    friend std::ostream &operator<<(std::ostream &os, const SparseMatrix &sparseMatrix);
};

std::ostream &operator<<(std::ostream &os, const SparseMatrix &sparseMatrix) {
    for (int i = 0; i < sparseMatrix.rows; ++i) {
        for (int j = 0; j < sparseMatrix.columns; ++j)
            os << sparseMatrix.getElement(i, j) << ' ';
        os << '\n';
    }

    return os;
}

int main() {
    SparseMatrix sparseMatrix{4, 5, 5};
    sparseMatrix.addElement(0, 2, 7);
    sparseMatrix.addElement(1, 0, 2);
    sparseMatrix.addElement(1, 3, 5);
    sparseMatrix.addElement(2, 0, 9);
    sparseMatrix.addElement(3, 4, 4);


    SparseMatrix sparseMatrix2{4, 5, 5};
    sparseMatrix2.addElement(0, 2, 7);
    sparseMatrix2.addElement(1, 0, 2);
    sparseMatrix2.addElement(1, 3, 5);
    sparseMatrix2.addElement(2, 0, 9);
    sparseMatrix2.addElement(3, 4, 4);

    SparseMatrix result = sparseMatrix + sparseMatrix2;
    std::cout << result;

    return 0;
}

// 0  0  14 0  0
// 4  0  0  10 0
// 18 0  0  0  0
// 0  0  0  0  8
