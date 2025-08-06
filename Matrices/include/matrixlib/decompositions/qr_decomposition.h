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
				for(size_t i = 0; i < matrix.get_columns(); ++i){

					const Column_View<T> s = matrix.get_column(i).subview(i);

					T alpha = std::copysign(compute_norm(s), s[0]);

					std::vector<T> omega(s.get_size());
					omega[0] = s[0] - alpha;
					for(size_t i = 1; i < omega.size(); ++i){
						omega[i] = s[i];
					}

					const T omega_norm = compute_norm(omega);
					if(omega_norm < epsilon) continue;
					for(size_t i = 0; i < omega.size(); ++i){
						omega[i] /= omega_norm;
					}

				}
				


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