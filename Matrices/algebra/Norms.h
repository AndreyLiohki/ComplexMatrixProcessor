#include "Matrix.h"
#include "SquareMatrix.h"

namespace algebra {

	namespace norms {

		double frobenius(const core::Matrix& matrix);

		double l1Columns(const core::Matrix& matrix);

		double l1Rows(const core::Matrix& matrix);

		double spectral(const core::Matrix& matrix);

		double nuclear(const core::Matrix& matrix);

	}

}
