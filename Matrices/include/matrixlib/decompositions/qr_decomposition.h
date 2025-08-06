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
					const Column_View<T> column = matrix.get_column(i);
				}
				


			}
			
			T compute_norm(const Column_View<T>& column) const {
                return std::sqrt(std::inner_product(column.begin(), column.end(), column.begin(), T(0)));
            }

            T compute_norm(const std::vector<T>& vector) const {
                return std::sqrt(std::inner_product(vector.begin(), vector.end(), vector.begin(), T(0)));
            }


			Column_View<T> get_vector_s(const Column_View<T>& column, const size_t column_number, const size_t position){
				Column_View<T> result = R_.get_column(column_number).subview(position);

				return result;
			}
			
		};
	}
}