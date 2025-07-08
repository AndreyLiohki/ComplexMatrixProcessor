#include "Matrix.h"
#include "SquareMatrix.h"

namespace algebra {

	namespace properties {

		core::Matrix transpose(const core::Matrix& matrix);

		core::SquareMatrix inverse(const core::SquareMatrix& matrix);

		core::Matrix conjugateTranspose(const core::Matrix& matrix);

	}
}