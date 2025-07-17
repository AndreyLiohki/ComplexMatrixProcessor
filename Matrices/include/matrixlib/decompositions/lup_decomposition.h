#pragma once

#include <complex>

#include "../core/type_traits.h"
#include "../core/matrix.h"

namespace Decompositions {
	namespace LUP_Decomposition {

		using Core::Traits::is_valid_matrix_type;
		using Core::Traits::EpsilonType;
		using Core::Traits::is_complex;
		using Core::Traits::default_epsilon;

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

			void computeDecomposition(const Core::Matrix<T>& matrix, const EpsilonType<T> epsilon = default_epsilon<T>()) {
				Core::Matrix<T> copy_matrix = matrix;

				L_ = Core::Matrix<T>(matrix.get_rows(), matrix.get_columns(), 0);
				U_ = Core::Matrix<T>(matrix.get_rows(), matrix.get_columns(), 0);
				P_ = Core::Matrix<T>(matrix.get_rows(), matrix.get_columns(), 0);

				P_.identity_matrix();
				L_.identity_matrix();

				for (size_t i = 0; i < copy_matrix.get_columns(); ++i) {

					size_t row_to_swap = -1;
					auto max_absolute_value = std::fabs(matrix(i,i));
					for (size_t j = i+1; j < copy_matrix.get_rows(); ++j) {
						if (std::fabs(copy_matrix(j, i)) > max_absolute_value) {
							max_absolute_value = std::fabs(copy_matrix(j, i));
							row_to_swap = j;
						}
					}

					if (max_absolute_value < epsilon) {
						throw std::runtime_error("Matrix is singular or nearly singular");
					}

					if (row_to_swap != i) {
						copy_matrix.swap_rows(i, row_to_swap);
						P_.swap_rows(i, row_to_swap);
					}
				}
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