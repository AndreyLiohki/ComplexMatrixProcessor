#pragma once

#include <complex>

#include "../core/matrix.h"


namespace Decompositions {

	namespace QR_Decomposition {

		using Core::Traits::EpsilonType;
		using Core::Traits::is_complex;
		using Core::Traits::is_valid_matrix_type;
		using Core::Traits::default_epsilon;

		template<typename T>
		class Qr_Decomposition {
		public:

			const Core::Matrix<T>& get_Q() { return Q_; }
			const Core::Matrix<T>& get_R() { return R_; }
		
		
		private:
			static_assert(
				is_valid_matrix_type<T>::value,
				"Matrix<T> requires T to be either float, double, long double or ComplexNumber<float/double/long double>");

			Core::Matrix<T>Q_;
			Core::Matrix<T>R_;

			bool decomposed = false;

			bool is_decomposed() {
				return decomposed;
			}
		
			void computeDecomposition(const Core::Matrix<T>& matrix, const EpsilonType<T> epsilon = default_epsilon<T>()) {



			}
			//TODO
			void computeHausholderMatrix(const std::vector<T>& choosed_column) {
				T alpha = std::sqrt(compute_scalar_product(choosed_column, choosed_column));
			}

			template<typename T>
			T scalar_product(const std::vector<T>& vec1, const std::vector<T>& vec2, bool conjugate_first = true) {
				static_assert(is_valid_matrix_type<T>::value, "Unsupported type");

				if (vec1.size() != vec2.size()) {
					throw std::invalid_argument("Vectors must have the same size");
				}

				T result{ 0 };
				if constexpr (is_complex<T>::value) {
					if (conjugate_first) {
						for (size_t i = 0; i < vec1.size(); ++i) {
							result += std::conj(vec1[i]) * vec2[i];
						}
					}
					else {
						for (size_t i = 0; i < vec1.size(); ++i) {
							result += vec1[i] * vec2[i];
						}
					}
				}
				else {
					for (size_t i = 0; i < vec1.size(); ++i) {
						result += vec1[i] * vec2[i];
					}
				}
				return result;
			}
		};
	}
}