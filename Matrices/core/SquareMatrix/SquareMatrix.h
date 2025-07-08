#pragma once

#include <iostream>
#include <vector>

#include "Matrix.h"

namespace core {

	class SquareMatrix :public Matrix {
	private:

	public:

		explicit SquareMatrix(std::size_t matrixSize);

	};

}//namespace Core
