#pragma once

#include <iostream>
#include <omp.h>

#include "../core/matrix.h"
#include "../core/square_matrix.h"
#include "../core/type_traits.h"
#include "../algebra/matrix_operations.h"

namespace Algebra {
	namespace Properties {

		using Core::Traits::is_complex;
		using Core::Traits::EpsilonType;
		using Core::Traits::default_epsilon;

		template<typename T>
		typename std::enable_if<std::is_floating_point_v<T>, bool>::type
			is_approximately_zero(const T value, const EpsilonType<T> epsilon) {
				return std::abs(value) < epsilon;
		}

		template<typename T>
		typename std::enable_if<is_complex<T>::value, bool>::type
			is_approximately_zero(const T& value, const EpsilonType<T> epsilon) {
				return std::norm(value) < (epsilon * epsilon);
		}

		template<typename T>
		bool is_rectangle(const Core::Matrix<T>& matrix) {
			return matrix.get_rows() != matrix.get_columns();
		}

		template<typename T>
		bool is_zero_matrix(const Core::Matrix<T>& matrix,
			EpsilonType<T> epsilon = default_epsilon<T>()) {
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
		std::pair<size_t, size_t> matrix_sparsity(const Core::Matrix<T>& matrix,
			EpsilonType<T> epsilon = default_epsilon<T>()) {
			std::pair<size_t, size_t> amount{0,0};

			#pragma omp parallel for reduction(+:amount.first, amount.second)
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
		bool is_symmetric(const Core::Matrix<T>& matrix, 
			EpsilonType<T> epsilon = default_epsilon<T>()) {
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
	}
}