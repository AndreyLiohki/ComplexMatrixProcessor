#pragma once

#include <iostream>
#include <complex>

#include "../core/matrix.h"
#include "../core/type_traits.h"

namespace Algebra {
	namespace Norms {

		using Core::Traits::is_complex;

		template<typename T>
		typename std::conditional_t<is_complex<T>::value, typename T::value_type,T>
		frobenius_norm(const Core::Matrix<T>& matrix) {
			using ReturnType = typename std::conditional_t<Core::is_complex<T>::value,
				typename T::value_type,T>;
			ReturnType result{};
			for (size_t i = 0; i < matrix.get_rows(); ++i) {
				for (size_t j = 0; j < matrix.get_columns(); ++j) {
					result += std::norm(matrix(i, j));
				}
			}
			return std::sqrt(result);
		}

		template<typename T>
		typename std::conditional_t < is_complex<T>::value, T, T>
			l_one_norm(const Core::Matrix<T>& matrix) {
			using ReturnType = T;
			ReturnType result{};
		}
	}

}