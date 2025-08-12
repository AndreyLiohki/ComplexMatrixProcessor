#pragma once

#include <complex>
#include <vector>

#include "../core/matrix.h"
#include "../core/type_traits.h"
#include "../decompositions/lup_decomposition.h"

namespace Algebra {
	namespace Operations {

		using Core::Traits::is_complex;

		template<typename T>
		Core::Matrix<T> transpose(const Core::Matrix<T>& matrix) {
			Core::Matrix<T> result(matrix.get_columns(), matrix.get_rows());
			for (size_t i = 0; i < matrix.get_rows(); ++i) {
				for (size_t j = 0; j < matrix.get_columns(); ++j) {
					result(j, i) = matrix(i, j);
				}
			}

			return result;
		}
		template<typename T>
		Core::Matrix<T> transpose(Core::Matrix<T>&& matrix) {
			Core::Matrix<T> result(matrix.get_columns(), matrix.get_rows());
			for (size_t i = 0; i < matrix.get_rows(); ++i) {
				for (size_t j = 0; j < matrix.get_columns(); ++j) {
					result(j, i) = std::move(matrix(i, j));
				}
			}

			return result;
		}


		template<typename T>
		typename std::enable_if <is_complex<T>::value, Core::Matrix<T>>::type
			hermitian_matrix(const Core::Matrix<T>& matrix) {
			Core::Matrix<T> result(matrix.get_columns(), matrix.get_rows());
			for (size_t i = 0; i < matrix.get_rows(); ++i) {
				for (size_t j = 0; j < matrix.get_columns(); ++j) {
					result(j, i) = std::conj(matrix(i, j));
				}
			}

			return result;
		}
		template<typename T>
		typename std::enable_if_t<is_complex<T>::value, Core::Matrix<T>>
			hermitian_matrix(Core::Matrix<T>&& matrix) {
			for (auto& row : matrix) {
				for (auto& elem : row) {
					elem = std::conj(elem);
				}
			}
			return transpose(std::move(matrix));
		}


	}
}