#pragma once

#include<iostream>
#include <complex>

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


		template<typename T>
		T trace(const Core::Matrix<T>& matrix) {
			if (!matrix.is_square()) {
				throw std::invalid_argument("It isnon-sqaure Matrix");
			}
			T result{};
			for (size_t i = 0; i < matrix.get_rows(); ++i) {
				result += matrix(i, i);
			}

			return result;
		}
		
		
		template<typename T>
		long rank(const Core::Matrix<T>& matrix, typename std::conditional_t<is_complex<T>::value,
			typename T::value_type, T> epsilon) {

			if (matrix.get_rows() == 0 || matrix.get_columns() == 0) {
				return 0;
			}

			Core::Matrix<T> work_matrix = matrix;
			long rank = 0;

			std::vector<bool> used_rows(matrix.get_rows(), false);

			for (size_t col = 0; col < matrix.get_columns(); ++col) {
				size_t pivot_row = 0;
				auto max_val = static_cast<decltype(epsilon)>(0);

				for (size_t row = 0; row < matrix.get_rows(); ++row) {
					if (!used_rows[row]) {
						auto current_val = std::abs(work_matrix(row, col));
						if (current_val > max_val) {
							max_val = current_val;
							pivot_row = row;
						}
					}
				}

				if (max_val < epsilon) {
					continue;
				}

				used_rows[pivot_row] = true;
				rank++;

				for (size_t j = col + 1; j < matrix.get_columns(); ++j) {
					work_matrix(pivot_row, j) /= work_matrix(pivot_row, col);
				}

				for (size_t row = 0; row < matrix.get_rows(); ++row) {
					if (!used_rows[row] && row != pivot_row) {
						for (size_t j = col + 1; j < matrix.get_columns(); ++j) {
							work_matrix(row, j) -= work_matrix(row, col) * work_matrix(pivot_row, j);
						}
					}
				}
			}

			return rank;
		}
	

		template <typename T>
		T determinant(const Decompositions::LUP_Decomposition::Lup_Decomposition<T>& decomposition) {
			T result{ 1 };
			for (size_t i = 0; i < decomposition.get_L().get_rows(); ++i) {
				result = result  * decomposition.get_U()(i, i);
			}

			return result* (decomposition.get_permutations()%2 == 0 ? 1:-1);
		}

}
}