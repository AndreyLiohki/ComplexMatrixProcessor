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
			using ReturnType = typename std::conditional_t<is_complex<T>::value, typename T::value_type, T>;
			ReturnType result{};
			for (size_t i = 0; i < matrix.get_rows(); ++i) {
				for (size_t j = 0; j < matrix.get_columns(); ++j) {
					result += std::norm(matrix(i, j));
				}
			}
			return std::sqrt(result);
		}


		template<typename T>
		typename std::conditional_t <is_complex<T>::value, typename T::value_type, T>
			l_one_norm_columns(const Core::Matrix<T>& matrix) {
			using ReturnType = typename std::conditional_t<is_complex<T>::value, typename T::value_type,T>;			
			
			ReturnType result{};
			for (size_t i = 0; i < matrix.get_columns(); ++i) {
				ReturnType current_result{};
				for (size_t j = 0; j < matrix.get_rows(); ++j) {
					current_result += std::abs(matrix(j, i));
				}
				if (current_result > result) {
					result = current_result;
				}
			}

			return result;
		}


		template<typename T>
		typename std::conditional_t <is_complex<T>::value, typename T::value_type, T>
			l_one_norm_rows(const Core::Matrix<T>& matrix) {
			using ReturnType = typename std::conditional_t<is_complex<T>::value, typename T::value_type, T>;
			
			ReturnType result{};
			for (size_t i = 0; i < matrix.get_rows(); ++i) {
				ReturnType current_result{};
				for (size_t j = 0; j < matrix.get_columns(); ++j) {
					current_result += std::abs(matrix(i, j));
				}
				if (current_result > result) {
					result = current_result;
				}
			}

			return result;
		}


		template<typename T>
		typename std::conditional_t<is_complex<T>::value, typename T::value_type, T>
			max_norm(const Core::Matrix<T>& matrix) {
			using ReturnType = typename std::conditional_t<is_complex<T>::value, typename T::value_type, T>;
		
			ReturnType result{};

			for (size_t i = 0; i < matrix.get_rows(); ++i) {
				for (size_t j = 0; j < matrix.get_columns(); ++j) {
					result = std::max(result, std::abs(matrix(i, j)));
				}
			}

			return result;
		}
	}

}