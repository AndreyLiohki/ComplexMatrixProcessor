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
				"Matrix<T> requires T to be either float, double, long double or ComplexNumber<float/double/long double>");

			Core::Matrix<T> L_;
			Core::Matrix<T> U_;
			Core::Matrix<T> P_;

			bool decomposed = false;

			unsigned long long amount_of_permutations = 0;

			bool is_decomposed() {
				return decomposed;
			}

			void computeDecomposition(const Core::Matrix<T>& matrix, const EpsilonType<T> epsilon = default_epsilon<T>()) {
				Core::Matrix<T> copy_matrix = matrix;

				L_ = Core::Matrix<T>(matrix.get_rows(), matrix.get_columns(), 0);
				U_ = Core::Matrix<T>(matrix.get_rows(), matrix.get_columns(), 0);
				P_ = Core::Matrix<T>(matrix.get_rows(), matrix.get_columns(), 0);

				P_.identity_matrix(1.0);

				for (size_t i = 0; i < copy_matrix.get_columns(); ++i) {

					size_t row_to_swap = i;
					auto max_absolute_value = std::abs(matrix(i,i));
					for (size_t j = i+1; j < copy_matrix.get_rows(); ++j) {
						if (std::abs(copy_matrix(j, i)) > max_absolute_value) {
							max_absolute_value = std::abs(copy_matrix(j, i));
							row_to_swap = j;
						}
					}

					if (max_absolute_value < epsilon) {
						throw std::runtime_error("Matrix is singular or nearly singular");
					}

					if (row_to_swap != i) {
						copy_matrix.swap_rows(i, row_to_swap);
						P_.swap_rows(i, row_to_swap);
						amount_of_permutations +=1 ;
					}

					for (size_t j = i+1; j < copy_matrix.get_rows(); ++j) {
						copy_matrix(j, i) /= copy_matrix(i, i);
						for (size_t k = i+1; k < copy_matrix.get_columns(); ++k) {
							copy_matrix(j, k) -= copy_matrix(j, i) * copy_matrix(i, k);
						}
					}
				}

				for (size_t i = 0; i < copy_matrix.get_rows(); ++i) {
					for (size_t j = 0; j < copy_matrix.get_columns(); ++j) {
						if (i >= j) {
							if(i == j){
								L_(i, j) = 1;
								U_(i, j) = copy_matrix(i, j);
							}
							else {
								L_(i, j) = copy_matrix(i, j);
							}
						}
						else {
							U_(i, j) = copy_matrix(i, j);
						}
					}
				}
				decomposed = true;

			}

		public:

			explicit Lup_Decomposition(const Core::Matrix<T>& matrix) {
				if ((matrix.get_rows() != matrix.get_columns())){
					throw std::invalid_argument("LUP decomposition requires square matrix");
				}
				if (matrix.get_rows() == 0) {
					throw std::invalid_argument("Matrix must not be empty");
				}
				computeDecomposition(matrix);
			}

			const Core::Matrix<T>& get_L() const { return L_; }
			const Core::Matrix<T>& get_U() const { return U_; }
			const Core::Matrix<T>& get_P() const { return P_; }
			const unsigned long long get_permutations() const { return amount_of_permutations; }
		};

	}
}