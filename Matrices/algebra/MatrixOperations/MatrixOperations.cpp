#include "Matrix.h"
#include "SquareMatrix.h"
#include "ComplexNumber.h"

namespace algebra {

	namespace properties {

		core::Matrix transpose(const core::Matrix& matrix) {
			core::Matrix transposedMatrix(matrix.getColumns(), matrix.getRows());
			for (size_t i = 0; i < matrix.getRows(); ++i) {
				for (size_t j = 0; j < matrix.getColumns(); ++j) {
					transposedMatrix(j, i) = matrix(i, j);
				}
			}

			return transposedMatrix;
		}

		core::SquareMatrix inverse(const core::SquareMatrix& matrix) {

		}

		core::Matrix hermitianConjugated(const core::Matrix& matrix) {
			core::Matrix hermitianConjugatedMatrix = transpose(matrix);
			for (size_t i = 0; i < hermitianConjugatedMatrix.getRows(); ++i) {
				for (size_t j = 0; j < hermitianConjugatedMatrix.getColumns(); ++j) {
					hermitianConjugatedMatrix(i, j) = core::getConjugated(hermitianConjugatedMatrix(i, j));
					
				}
			}

			return hermitianConjugatedMatrix;
		}

	}
}