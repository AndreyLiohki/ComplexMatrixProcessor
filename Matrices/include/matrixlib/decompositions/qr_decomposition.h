#pragma once

#include <complex>

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
			
			T scalar_product(const Column_View<T>& column_1, const Column_View<T>& column_2){
				if(column_1.get_size() != column_2.get_size()){
					throw std::invalid_argument("Columns must have same size for scalar production computation");
				}

				T result{};

				for(size_t i = 0; i < column_1.get_size(); ++i){
					if constexpr(is_complex<T>::value){
						result += column_1[i] * std::conj(column_2[i]);
					}else{
						result += column_1[i] * column_2[i];
					}
				}

				return result;
			}
		
			
		};
	}
}