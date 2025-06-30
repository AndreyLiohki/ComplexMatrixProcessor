#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "ComplexNumbers.h"

using namespace std;

class Matrix {
private:
	vector<vector<ComplexNumber>> matrix;
	size_t rows;
	size_t columns;
	static bool checkMatricesSize(const size_t& firstMatrixRows, const size_t& firstMatrixColumns, const size_t& secondMatrixRows, const size_t& secondMatrixColumns) {
		return (firstMatrixRows == secondMatrixRows && firstMatrixColumns == secondMatrixColumns);
	}
	static bool checkMatricesSizesForMultiplication(const size_t& firstMatrixColumns, const size_t& secondMatrixRows) {
		return (firstMatrixColumns == secondMatrixRows);
	}
public:
	Matrix(const vector<vector<ComplexNumber>>& mat) :matrix(mat),
		rows(mat.size()), columns(mat.empty() ? 0 : mat[0].size()) {}
	Matrix(const size_t& rows, const size_t& columns) : rows(rows), columns(columns) {
		matrix.resize(rows, vector<ComplexNumber>(columns));
	}
	Matrix(const size_t& rows, const size_t& columns, const ComplexNumber& value)
		: rows(rows), columns(columns) {
		matrix.resize(rows, vector<ComplexNumber>(columns, value));
	}

	size_t getRows() const {
		return rows;
	}
	size_t getColumns() const {
		return columns;
	}
	
	static Matrix zero(const size_t& rows, const size_t& columns) {
		Matrix matr(rows, columns, ComplexNumber(0,0));
		return matr;
	}

	bool isHermitian() const {
		Matrix hermConjug = this->hermitianConjugated();
		return hermConjug == *this;
	}
	double frobeniusNorm() const {
		double answer = 0;
		for (size_t i = 0; i < this->rows; ++i) {
			for (size_t j = 0; j < this->columns; ++j) {
				answer += this->matrix[i][j].getAbsoluteValue() * this->matrix[i][j].getAbsoluteValue();
			}
		}
		return sqrt(answer);
	}
	Matrix transpose()const {
		Matrix transposedMatrix(this->columns, this->rows);
		for (size_t i = 0; i < this->rows; ++i) {
			for (size_t j = 0; j < this->columns; ++j) {
				transposedMatrix(j, i) = matrix[i][j];
			}
		}
		return transposedMatrix;
	}
	Matrix hadamardProduct(const Matrix& other) const {
		if (!checkMatricesSize(this->rows, this->columns, other.rows, other.columns)) {
			throw runtime_error("Cannot find hadamard production");
		}
		Matrix hadamardProductionResult(this->rows, this->columns);
		for (size_t i = 0; i < this->rows; ++i) {
			for (size_t j = 0; j < this->columns; ++j) {
				hadamardProductionResult(i, j) = this->matrix[i][j] * other.matrix[i][j];
			}
		}

		return hadamardProductionResult;
	}
	Matrix conjugatedMatrix() const {
		Matrix conjugationResult(this->rows, this->columns);

		for (size_t i = 0; i < this->rows; ++i) {
			for (size_t j = 0; j < this->columns; ++j) {
				ComplexNumber conjugatedElement(this->matrix[i][j].getRe(), -1 * this->matrix[i][j].getIm());
				conjugationResult(i, j) = conjugatedElement;
			}
		}

		return conjugationResult;
	}
	Matrix hermitianConjugated() const {
		return this->conjugatedMatrix().transpose();
	}

	bool operator==(const Matrix& other) const {
		if (rows != other.rows || columns != other.columns) {
			return false;
		}

		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < columns; ++j) {
				if (!(this->matrix[i][j] == other.matrix[i][j]))
					return false;
			}
		}

		return true;
	}
	void operator=(const Matrix& other){
		this->matrix = other.matrix;
		this->rows = other.rows;
		this->columns = other.columns;
	}
	Matrix operator+(const Matrix& other) const {
		if (!checkMatricesSize(this->rows, this->columns, other.rows, other.columns)) {
			throw runtime_error("Matrices sizes differ");
		}
		Matrix sumResult(this->rows, this->columns);
		for (size_t i = 0; i < this->rows; ++i) {
			for (size_t j = 0; j < this->columns; ++j) {
				sumResult(i, j) = this->matrix[i][j] + other.matrix[i][j];
			}
		}

		return sumResult;
	}
	Matrix operator-(const Matrix& other) const {
		if (!checkMatricesSize(this->rows, this->columns, other.rows, other.columns)) {
			throw runtime_error("Matrices sizes differ");
		}
		Matrix diffResult(this->rows, this->columns);
		for (size_t i = 0; i < this->rows; ++i) {
			for (size_t j = 0; j < this->columns; ++j) {
				diffResult(i, j) = this->matrix[i][j] - other.matrix[i][j];
			}
		}

		return diffResult;
	}
	Matrix operator*(const Matrix& other) const {
		if (!checkMatricesSizesForMultiplication(this->columns, other.rows)) {
			throw runtime_error("Invalid sizes. Impossible to multiply matrices");
		}
		Matrix productionResult(this->rows, other.columns);
		for (size_t i = 0; i < this->rows; ++i) {
			for (size_t j = 0; j < other.columns; ++j) {
				ComplexNumber sum;
				for (size_t k = 0; k < this->columns; ++k) {
					sum = sum + (this->matrix[i][k] * other.matrix[k][j]);
				}
				productionResult(i, j) = sum;
			}
		}

		return productionResult;
	}
	Matrix operator*(const ComplexNumber& value) const {
		Matrix scalarProduction(this->rows, this->columns);
		for (size_t i = 0; i < this->rows; ++i) {
			for (size_t j = 0; j < this->columns; ++j) {
				scalarProduction(i, j) = this->matrix[i][j] * value;
			}
		}
		return scalarProduction;
	}


	ComplexNumber& operator()(const size_t& row, const size_t& column) {
		if (row >= rows || column >= columns)
			throw out_of_range("Matrix indexes out of range");

		return matrix[row][column];
	}
	const ComplexNumber& operator()(const size_t& row, const size_t& column) const {
		if (row >= rows || column >= columns)
			throw out_of_range("Matrix imdexes out of range");

		return matrix[row][column];
	}
	friend ostream& operator<<(ostream& os, const Matrix& m) {
		for (size_t i = 0; i < m.getRows(); ++i) {
			for (size_t j = 0; j < m.getColumns(); ++j) {
				os << m(i, j) << "\t";
			}
			os << "\n";
		}
		return os;
	}
};