#pragma once
#include <iostream>
#include <vector>
#include "Matrix.h"
#include "ComplexNumbers.h"

using namespace std;

class SquareMatrix : public Matrix {
private:
    bool isZero(const ComplexNumber& z, double epsilon = 1e-10) {
        return z.getAbsoluteValue() < epsilon;
    }
public:

	SquareMatrix(size_t n) : Matrix(n,n){}
	SquareMatrix(const vector<vector<ComplexNumber>>& mat) : Matrix(mat) {
		if (mat.size() != mat[0].size()) {
			throw runtime_error("Matrix is not square");
		}
	}
	
	static SquareMatrix identity(size_t n) {
		SquareMatrix I(n);
		for (size_t i = 0; i < n; ++i) {
			I(i, i) = ComplexNumber(1, 0);
		}
		return I;
	}

	ComplexNumber trace() const {
		ComplexNumber tr;
		for (size_t i = 0; i < getRows(); ++i) {
			tr = tr + (*this)(i, i);
		}

		return tr;
	}
	bool isHermitian() const {
		return this->hermitianConjugated() == *this;
	}
	bool isUnitary() const {
		return this->hermitianConjugated() * (*this) == identity(size());
	}
    int rank(const Matrix& A) {
        Matrix temp = A;
        size_t rows = temp.getRows(), cols = temp.getColumns();
        size_t rank = 0;

        for (size_t col = 0, row = 0; col < cols && row < rows; ++col) {
            size_t pivotRow = row;
            while (pivotRow < rows && isZero(temp(pivotRow, col))) {
                ++pivotRow;
            }

            if (pivotRow == rows) continue;

            if (pivotRow != row) {
                for (size_t j = 0; j < cols; ++j)
                    swap(temp(pivotRow, j), temp(row, j));
            }

            ComplexNumber lead = temp(row, col);
            for (size_t j = 0; j < cols; ++j)
                temp(row, j) = temp(row, j) / lead;

            for (size_t i = row + 1; i < rows; ++i) {
                ComplexNumber factor = temp(i, col);
                for (size_t j = 0; j < cols; ++j) {
                    temp(i, j) = temp(i, j) - temp(row, j) * factor;
                }
            }

            ++row;
            ++rank;
        }

        return rank;
    }


};