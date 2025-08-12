#pragma once

#include <complex>
#include <numeric>

#include "../core/matrix.h"
#include "../algebra/matrix_operations.h"


namespace Decompositions {

	namespace QR_Decomposition {

		using Core::Traits::EpsilonType;
		using Core::Traits::is_complex;
		using Core::Traits::is_valid_matrix_type;
		using Core::Traits::default_epsilon;

		using Core::Matrix;

		using namespace Algebra::Operations;

		template<typename T>
		class Qr_Decomposition {
		public:

			const Core::Matrix<T>& get_Q() const{ return Q_; }
			const Core::Matrix<T>& get_R() const{ return R_; }
		
			explicit Qr_Decomposition(const Matrix<T> matrix){
				if ((matrix.get_rows() != matrix.get_columns())){
					throw std::invalid_argument("LUP decomposition requires square matrix");
				}
				if (matrix.get_rows() == 0) {
					throw std::invalid_argument("Matrix must not be empty");
				}

				R_ = matrix;
				Q_ = Core::Matrix<T>(matrix.get_rows(), matrix.get_columns(), 0);
				Q_.identity_matrix(T {1});
				compute_decomposition(matrix);
			}
		
			void recompute_decomposition(const Matrix<T> matrix){
				if ((matrix.get_rows() != matrix.get_columns())){
					throw std::invalid_argument("LUP decomposition requires square matrix");
				}
				if (matrix.get_rows() == 0) {
					throw std::invalid_argument("Matrix must not be empty");
				}

				R_ = matrix;
				Q_ = Core::Matrix<T>(matrix.get_rows(), matrix.get_columns(), 0);
				Q_.identity_matrix(T {1});
				compute_decomposition(matrix);
			}
		private:
			static_assert(
				is_valid_matrix_type<T>::value,
				"Matrix<T> requires T to be either float, double, long double or ComplexNumber<float/double/long double>");

			Matrix<T>Q_;
			Matrix<T>R_;

			bool decomposed = false;

			bool is_decomposed() {
				return decomposed;
			}
			
			void compute_decomposition(const Matrix<T>& matrix, const EpsilonType<T> epsilon = default_epsilon<T>()){
				Matrix<T> identity(matrix.get_rows(), matrix.get_columns(), 0);
				identity.identity_matrix(1);

				const size_t n = matrix.get_rows();
				const size_t m = matrix.get_columns();

				for(size_t k = 0; k < m; ++k){

					// berechnen alpha
					T alpha{0};
					for(size_t i = k; i < n; ++i){
						alpha+= matrix(i, k) * matrix(i,k);
					}
					alpha = std::sqrt(alpha);
					if(std::abs(alpha) < epsilon) continue;
					if(matrix(k,k) > 0) alpha = -alpha;

					//berechnen s-ae
					std::vector<T> intermediate_vector(m-k);
					for(size_t i = 0; i < intermediate_vector.size(); ++i){
						if(i == 0){
							intermediate_vector[i] = matrix(i+k, k) - alpha;
						}else{
							intermediate_vector[i] = matrix(i+k, k);
						}	
					}

					//berechnen k
					T coefficient{0};
					for(size_t i = k; i < n; ++i){
						coefficient += matrix(i,k) * intermediate_vector[i-k];
					}
					coefficient = 1/std::sqrt(2*coefficient);

					//berechnen omega
					std::vector<T> omega(n, 0);
					for(size_t i = k; i<n;++i){
						omega[i] = coefficient * intermediate_vector[i-k];
					}

					//berechnen die Matrix von Haußholder
					Matrix<T> Vn(omega, true);
					Matrix<T> hausholder_matrix;
					if constexpr(is_complex<T>::value){
						hausholder_matrix = identity - 2 * Vn * transpose(Algebra::Operations::hermitian_matrix(Vn));
					}else{
						hausholder_matrix = identity - 2 * Vn * transpose(Vn);
					}


					//Transformationen durchführen
					R_ = hausholder_matrix * R_;
					Q_ = Q_ * hausholder_matrix;
				}
			}
		};
	}
}