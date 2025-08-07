#pragma once

#include <complex>
#include <numeric>

#include "../core/matrix.h"
#include "../core/column.h"
#include "../algebra/matrix_operations.h"


namespace Decompositions {

	namespace QR_Decomposition {

		using Core::Traits::EpsilonType;
		using Core::Traits::is_complex;
		using Core::Traits::is_valid_matrix_type;
		using Core::Traits::default_epsilon;

		using Core::Matrix;
		using Core::Column_View;

		using namespace Algebra::Operations;

		template<typename T>
		class Qr_Decomposition {
		public:

			const Core::Matrix<T>& get_Q() { return Q_; }
			const Core::Matrix<T>& get_R() { return R_; }
		
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
				computeDecomposition(matrix);
			}
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
				Matrix<T> identity(matrix.get_rows(), matrix.get_columns(), 0);
				identity.identity_matrix(T {1});
				
				for(size_t k = 0; k < matrix.get_columns(); ++k){
					Column_View<T> current_column = R_.get_column(k).subview(k);

					T alpha = current_column.vector_l2_norm();
					if(std::abs(alpha) < epsilon) continue;
					if (current_column[0] > 0) alpha = -alpha;
					
					std::vector<T> intermediate_vector(current_column.get_size(), 0);
					for(size_t i = 0; i < intermediate_vector.size(); ++i){
						if(i == 0){
							intermediate_vector[i] = current_column[i] - alpha;
						}else{
							intermediate_vector[i] = current_column[i];
						}
					}

					T coefficient = compute_k(current_column, intermediate_vector);

					std::vector<T> omega(R_.get_columns(), 0);
					for(size_t i = k; i < omega.size(); ++i){
						omega[i] = coefficient * intermediate_vector[i];
					}

					Matrix<T> Vn(omega);
					Vn = transpose(Vn) * Vn;
					Matrix<T> hausholder_matrix = identity - 2 * Vn;

					R_ = hausholder_matrix *R_;
					std::cout << R_ << std::endl;
					
					Q_ = Q_* hausholder_matrix;
					std::cout << Q_ << std::endl;
				}
				
				decomposed = true;

			}

			T compute_k(const Column_View<T>& column, const std::vector<T>& intermediate_column){
				if(column.get_size() != intermediate_column.size()){
					throw std::invalid_argument("wrong operand sizes");
				}

				T result{0};

				for(size_t i = 0; i < column.get_size(); ++i){
					result +=column[i]*intermediate_column[i];
				}

				result = 2 * result;

				return 1/std::sqrt(result);
			}

			
		};
	}
}