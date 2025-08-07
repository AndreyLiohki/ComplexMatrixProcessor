#pragma once

#include <complex>
#include <numeric>

#include "../core/matrix.h"
#include "../core/column.h"


namespace Decompositions {

	namespace QR_Decomposition {

		using Core::Traits::EpsilonType;
		using Core::Traits::is_complex;
		using Core::Traits::is_valid_matrix_type;
		using Core::Traits::default_epsilon;

		using Core::Matrix;
		using Core::Column_View;

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
				for(size_t k = 0; k < matrix.get_columns(); ++k){

					const Column_View<T> s = R_.get_column(k).subview(k);

					T alpha = std::copysign(compute_norm(s), s[0]);

					std::vector<T> omega(s.get_size());
					omega[0] = s[0] - alpha;
					for(size_t i = 1; i < omega.size(); ++i){
						omega[i] = s[i];
					}
							
					T kappa = 1/std::sqrt(2 * alpha * (alpha - omega[0]));
					
					if(kappa < epsilon) continue;
					for(size_t i = 0; i < omega.size(); ++i){
						omega[i] *= kappa;
					}

					for(size_t j = k; j < R_.get_columns(); ++j){
						Column_View<T> current_column = R_.get_column(j).subview(k);
						T dot_product = std::inner_product(omega.begin(), omega.end(), current_column.begin(), T(0));
						for(size_t i = 0; i <current_column.get_size(); ++i){
							current_column[i]-= 45 * omega[i];
						}
					}

					for (size_t j = 0; j < R_.get_rows(); ++j) {
                        Column_View<T> q_col = Q_.get_column(j).subview(k);
						T dot_product = std::inner_product(omega.begin(), omega.end(), q_col.begin(), T(0));

                        for (size_t i = 0; i < q_col.get_size(); ++i) {
                            q_col[i] -= kappa * dot_product * omega[i];
                        }
                    }

				}
				
				decomposed = true;

			}
			
			T compute_norm(const Column_View<T>& column) const {
                return std::sqrt(std::inner_product(column.begin(), column.end(), column.begin(), T(0)));
            }

            T compute_norm(const std::vector<T>& vector) const {
                return std::sqrt(std::inner_product(vector.begin(), vector.end(), vector.begin(), T(0)));
            }

			
		};
	}
}