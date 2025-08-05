#pragma once

#include <complex>

#include "../core/matrix.h"


namespace Decompositions {

	namespace QR_Decomposition {

		using Core::Traits::EpsilonType;
		using Core::Traits::is_complex;
		using Core::Traits::is_valid_matrix_type;
		using Core::Traits::default_epsilon;

		using Core::Matrix;
		
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
				T coefficient = ;
			}

			T scalar_product(const std::vector<T>& vector_1, const std::vector<T>& vector_2, bool conjugate_first = true) {
				static_assert(is_valid_matrix_type<T>::value, "Unsupported type");

				if (vector_1.size() != vector_2.size()) {
					throw std::invalid_argument("Vectors must have the same size");
				}

				T result{ 0 };
				if constexpr (is_complex<T>::value) {
					if (conjugate_first) {
						for (size_t i = 0; i < vector_1.size(); ++i) {
							result += std::conj(vector_1[i]) * vector_2[i];
						}
					}
					else {
						for (size_t i = 0; i < vector_1.size(); ++i) {
							result += vector_1[i] * vector_2[i];
						}
					}
				}
				else {
					for (size_t i = 0; i < vector_1.size(); ++i) {
						result += vector_1[i] * vector_2[i];
					}
				}
				return result;
			}
		
			std::vector<T> get_identity_vector(const size_t size_of_vector, const size_t position_of_1s) {
				std::vector<T> result(size_of_vector, T{ 0 });
				result[position_of_1s] = T{ 1 };
				return result;
			}

			std::vector<T> vector_summation(const std::vector<T>& vector_1, const std::vector<T>& vector_2) {
				if (vector_1.size() != vector_2.size()) {
					throw std::invalid_argument("incompatible vector sizes");
				}
				std::vector<T> result(vector_1.size());
				for (size_t i = 0; i < vector_1.size(); ++i) {
					result[i] = vector_1[i] + vector_2[i];
				}
				return result;
			}

			std::vector<T> vector_sustitution(const std::vector<T>& vector_1, const std::vector<T>& vector_2) {
				if (vector_1.size() != vector_2.size()) {
					throw std::invalid_argument("incompatible vector sizes");
				}
				std::vector<T> result(vector_1.size());
				for (size_t i = 0; i < vector_1.size(); ++i) {
					result[i] = vector_1[i] - vector_2[i];
				}
				return result;
			}
		
			std::vector<T> multiply_vector_on_scalar(std::vector<T>& vector_1, const T& alpha){
				for(size_t i = 0; i < vector_1.size(); ++i){

				}
			}

			T compute_coefficient_k(const std::vector<T>& choosed_column, const T& alpha, const size_t position_of_1s){
				std::vector<T> identity_vector = get_identity_vector(choosed_column.size(), position_of_1s);
				T result = 1/(std::sqrt(compute_scalar_product(choosed_column, vector)))
			}
		};
	}
}