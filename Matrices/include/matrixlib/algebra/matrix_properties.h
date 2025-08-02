#pragma once


#include "../core/matrix.h"
#include "../core/type_traits.h"
#include "../algebra/common_functions.h"
#include "../algebra/matrix_operations.h"

namespace Algebra {
	namespace Properties {

		using Core::Traits::is_complex;
		using Core::Traits::EpsilonType;
		using Core::Traits::default_epsilon;


		template<typename T>
		[[nodiscard]] constexpr 
			typename std::enable_if<std::is_floating_point_v<T>, bool>::type
			is_approximately_zero(const T value, const EpsilonType<T> epsilon) noexcept{
			return std::fabs(value) < epsilon;
		}
		template<typename T>
		[[nodiscard]] constexpr 
			typename std::enable_if<is_complex<T>::value, bool>::type
			is_approximately_zero(const T& value, const EpsilonType<T> epsilon) noexcept{
			return std::norm(value) < (epsilon * epsilon);
		}


		template<typename T>
		[[nodiscard]] bool is_zero_matrix(const Core::Matrix<T>& matrix,
			EpsilonType<T> epsilon = default_epsilon<T>()) noexcept{
			for (size_t i = 0; i < matrix.get_rows(); ++i) {
				for (size_t j = 0; j < matrix.get_columns(); ++j) {
					if (!is_approximately_zero(matrix(i, j), epsilon)) {
						return false;
					}
				}
			}
			return true;
		}


		template<typename T>
		[[nodiscard]] std::pair<size_t, size_t> matrix_sparsity(const Core::Matrix<T>& matrix,
			EpsilonType<T> epsilon = default_epsilon<T>()) noexcept{
			std::pair<size_t, size_t> amount{ 0,0 };

			for (size_t i = 0; i < matrix.get_rows(); ++i) {
				for (size_t j = 0; j < matrix.get_columns(); ++j) {
					if (!is_approximately_zero(matrix(i, j), epsilon)) {
						amount.second++;
					}
					else {
						amount.first++;
					}
				}
			}

			return amount;
		}


		template<typename T>
		[[nodiscard]] constexpr bool is_symmetric(const Core::Matrix<T>& matrix,
			EpsilonType<T> epsilon = default_epsilon<T>()) noexcept {
			if (!matrix.is_square()) {
				return false;
			}
			for (size_t i = 0; i < matrix.get_rows(); ++i) {
				for (size_t j = i + 1; j < matrix.get_columns(); ++j) {
					if (!is_approximately_zero(matrix(i, j) - matrix(j, i), epsilon)) {
						return false;
					}
				}
			}
			return true;
		}


		template<typename T>
		[[nodiscard]] constexpr 
			typename std::enable_if_t<is_complex<T>::value, bool>
			is_hermitian(const Core::Matrix<T>& matrix, EpsilonType<T> epsilon = default_epsilon<T>()) noexcept {

			if (!matrix.is_square()) {
				return false;
			}

			const size_t n = matrix.get_rows();

			for (size_t i = 0; i < n; ++i) {
				if (!is_approximately_zero(std::imag(matrix(i, i)), epsilon)) {
					return false;
				}
			}
			for (size_t i = 0; i < n; ++i) {
				for (size_t j = i + 1; j < n; ++j) {
					if (!is_approximately_zero(matrix(i, j) - std::conj(matrix(j, i)), epsilon)) {
						return false;
					}
				}
			}
			return true;
		}


		template<typename T>
		[[nodiscard]] constexpr bool is_skew_symmetric(const Core::Matrix<T>& matrix, EpsilonType<T> epsilon = default_epsilon<T>()) noexcept {
			for (size_t i = 0; i < matrix.get_rows(); ++i){
				for (size_t j = i+1; j < matrix.get_columns(); ++j) {
					if (!is_approximately_zero(matrix(i, j) - (-matrix(j, i)), epsilon)) {
						return false;
					}
				}
			}
			return true;
		}
	

		template <typename T>
		[[nodiscard]] constexpr typename std::enable_if_t<is_complex<T>::value, bool>
			is_antihermitian(const Core::Matrix<T>& matrix,
				EpsilonType<T> epsilon = default_epsilon<T>()) noexcept{
			if (!matrix.is_square()) {
				return false;
			}
			
			for (size_t i = 0; i < matrix.get_rows(); ++i) {
				if (!is_approximately_zero(std::real(matrix(i, i)), epsilon)) {
					return false;
				}
			}
			for (size_t i = 0; i < matrix.get_rows(); ++i) {
				for (size_t j = 0; j < matrix.get_columns(); ++j) {
					if (!is_approximately_zero(matrix(i, j) - (-std::conj(matrix(j, i))), epsilon)) {
						return false;
					}
				}
			}
			return true;
		}
	

	}
}