#include <iostream>

#include "Matrix.h"
#include "SquareMatrix.h"
#include "ComplexNumber.h"

namespace algebra {

	namespace properties {

		long rank(const core::Matrix& matrix);

		long nullity(const core::Matrix& matrix);

		long coherence(const core::Matrix& matrix);

		bool isSquare(const core::Matrix& matrix);

		namespace square {

			core::ComplexNumber determinant(const core::SquareMatrix& matrix);

			core::ComplexNumber trace(const core::SquareMatrix& matrix);

			double conditionNumber(const core::SquareMatrix& matrix);

			double spectralRadius(const core::SquareMatrix& matrix);

			bool isSymmetric(const core::SquareMatrix& matrix);

			bool isHermitian(const core::SquareMatrix& matrix);

			bool isSkewSymmetric(const core::SquareMatrix& matrix);

			bool isDiagonal(const core::SquareMatrix& matrix);

			bool isIdentity(const core::SquareMatrix& matrix);

			bool isUpperTriangle(const core::SquareMatrix& matrix);

			bool isLowerTriangle(const core::SquareMatrix& matrix);

			bool isInvertible(const core::SquareMatrix& matrix);

			bool isOrthogonal(const core::SquareMatrix& matrix);

			bool isUnitary(const core::SquareMatrix& matrix);

			bool isPositiveDefinite(const core::SquareMatrix& matrix);

			bool isSingular(const core::SquareMatrix& matrix);
		}

	}
	
}