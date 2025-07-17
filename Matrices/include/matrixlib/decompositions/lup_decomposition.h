#pragma once

#include <complex>

#include "../core/type_traits.h"
#include "../core/matrix.h"
#include "../core/type_traits.h"

namespace Decompositions {
	namespace LUP_Decomposition {

		using Core::Traits::is_valid_matrix_type;

		template<typename T>
		class Lup_Decomposition {
		private:
			static_assert(
				is_valid_matrix_type<T>::value,
				"Matrix<T> requires T to be either float, double or ComplexNumber<float/double>");

			Core::Matrix<T> L_;
			Core::Matrix<T> U_;
			Core::Matrix<T> P_;

			void computeDecomposition(const Core::Matrix<T>& matrix) {

			}

		public:

			explicit Lup_Decomposition(const Core::Matrix<T>& matrix) {

			}

			const Core::Matrix<T>& getL() const { return L_; }
			const Core::Matrix<T>& getU() const { return U_; }
			const Core::Matrix<T>& getP() const { return P_; }
		};

	}
}