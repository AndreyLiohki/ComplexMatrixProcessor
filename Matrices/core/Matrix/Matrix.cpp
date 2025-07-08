#include <iostream>
#include <vector>

#include "Matrix.h"

namespace core {

	Matrix::Matrix(const std::vector<std::vector<ComplexNumber>>& mat) :matrix(mat),
		rows(mat.size()), columns(mat.empty() ? 0 : mat[0].size()) {}

	Matrix::Matrix(const std::size_t& rows, const std::size_t& columns) : rows(rows), columns(columns) {
		matrix.resize(rows, std::vector<ComplexNumber>(columns));
	}

	Matrix::Matrix(const std::size_t& rows, const std::size_t& columns, const ComplexNumber& value) : rows(rows), columns(columns) {
		matrix.resize(rows, std::vector<ComplexNumber>(columns, value));
	}

	std::size_t Matrix::getRows() const {
		return rows;
	} 

	std::size_t Matrix::getColumns() const {
		return columns;
	}

	ComplexNumber& Matrix::operator()(const std::size_t& row, const std::size_t& column) {
		if (row >= rows || column >= columns)
			throw std::out_of_range("Matrix indexes out of range");

		return matrix[row][column];
	}

	const ComplexNumber& Matrix::operator()(const size_t& row, const size_t& column) const {
		if (row >= rows || column >= columns)
			throw std::out_of_range("Matrix imdexes out of range");

		return matrix[row][column];
	}

	std::ostream& operator<<(std::ostream& os, const Matrix& m) {
		for (size_t i = 0; i < m.getRows(); ++i) {
			for (size_t j = 0; j < m.getColumns(); ++j) {
				os << m(i, j) << "\t";
			}
			os << "\n";
		}
		return os;
	}

}//namespace Core