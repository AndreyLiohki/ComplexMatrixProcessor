#pragma once

#include <complex>

#include "../core/type_traits.h"
#include "../core/matrix.h"

namespace Decompositions {
	namespace LUP_Decomposition {

		using Core::Traits::is_valid_matrix_type;

		template<typename T>
		class Lup_Decomposition {
		private:
			static_assert(
				is_valid_matrix_type<T>::value,
				"Matrix<T> requires T to be either float, double or ComplexNumber<float/double>");

			Core::Matrix<T> L_;
			Core::Matrix<T> U_;
			Core::Matrix<T> P_;

			bool decomposed = false;

			bool is_decomposed() {
				return decomposed;
			}

			void computeDecomposition(const Core::Matrix<T>& matrix) {
				Core::Matrix<T> copy_matrix = matrix;

				L_ = Core::Matrix<T>(matrix.get_rows(), matrix.get_columns(), 0);
				U_ = Core::Matrix<T>(matrix.get_rows(), matrix.get_columns(), 0);
				P_ = Core::Matrix<T>(matrix.get_rows(), matrix.get_columns());

				P_.identity_matrix();
			}

		public:

			explicit Lup_Decomposition(const Core::Matrix<T>& matrix) {
				if ((matrix.get_rows() != matrix.get_columns())){
					throw std::invalid_argument("LUP decomposition requires square matrix");
				}
				if (matrix.get_rows()) {
					throw std::invalid_argument("Matrix must not be empty");
				}
			}

			const Core::Matrix<T>& getL() const { return L_; }
			const Core::Matrix<T>& getU() const { return U_; }
			const Core::Matrix<T>& getP() const { return P_; }
		};

	}
}