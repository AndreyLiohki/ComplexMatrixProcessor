#pragma once

#include <complex>

#include "../core/matrix.h"

namespace Algebra {
	namespace Common_Functions {

		template<typename T>
		bool is_square_matrix(const Core::Matrix<T>& matrix) {
			return matrix.is_square;
		}
	
	}
}