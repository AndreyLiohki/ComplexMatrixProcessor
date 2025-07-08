#pragma once

#include <iostream>
#include <vector>

#include "ComplexNumber.h"

namespace core {

	class Matrix {
	private:
		std::vector<std::vector<ComplexNumber>> matrix;
		std::size_t rows;
		std::size_t columns;
	public:
		Matrix(const std::vector<std::vector<ComplexNumber>>& mat);
		Matrix(const std::size_t& rows, const std::size_t& columns);
		Matrix(const std::size_t& rows, const std::size_t& columns, const ComplexNumber& value);

		std::size_t getRows() const;
		std::size_t getColumns() const;

		ComplexNumber& operator()(const std::size_t& row, const std::size_t& columns);
		const ComplexNumber& operator()(const std::size_t& row, const std::size_t& column) const;

		friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
	};

}//namespace Core