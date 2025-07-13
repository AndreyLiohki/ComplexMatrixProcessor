#pragma once

#include <iostream>
#include <complex>

namespace Core {

	template<typename T>
	class SquareMatrix : public Matrix<T> {
	public:

		explicit SquareMatrix(size_t size) noexcept: Matrix<T>(size, size) {}
		explicit SquareMatrix(const std::vector<std::vector<T>>& data) : Matrix<T>(data) {
			if (this->getRows() != this->getColumns()) {
				throw std::invalid_argument("SquareMatrix requires square dimensions");
			}
		}
		SquareMatrix(size_t size, const T& value) noexcept(std::is_nothrow_copy_constructible_v<T>) : Matrix<T>(size, size, value) {}
		
	private:


	};

}