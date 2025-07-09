#pragma once

#include <vector>
#include <iostream>

#include "ComplexNumber.h"

namespace LineareAlgebra::Core {

	template<typename T>
	class Matrix {
	private:

		static_assert(
			std::is_floating_point_v<T> ||
			std::is_same_v<T, ComplexNumber<typename T::value_type>>,
			"Matrix<T> requires T to be either a floating-point type or ComplexNumber"
		);

		std::vector<std::vector<T>> data_;
		size_t rows_;
		size_t columns_;


        void check_rectangular() const {
            for (const auto& row : data_) {
                if (row.size() != columns_) {
                    throw std::invalid_argument("All rows must have the same length");
                }
            }
        }
        void check_dimensions(const Matrix& other) const {
            if (rows_ != other.rows_ || columns_ != other.columns_) {
                throw std::invalid_argument("Matrix dimensions must agree");
            }
        }
    
    public:

        Matrix() noexcept : rows_(0), columns_(0) {}
        Matrix(size_t rows, size_t columns)
            noexcept(std::is_nothrow_constructible_v<std::vector<T>>)
            : data_(rows, std::vector<T>(columns)),
            rows_(rows),
            columns_(columns) {}
        Matrix(size_t rows, size_t columns, const T& value)
            noexcept(std::is_nothrow_copy_constructible_v<T>)
            : data_(rows, std::vector<T>(columns, value)),
            rows_(rows),
            columns_(columns) {}
        explicit Matrix(const std::vector<std::vector<T>>& data)
            : data_(data),
            rows_(data.size()),
            columns_(data.empty() ? 0 : data[0].size())
        {
            check_rectangular();
        }
        Matrix(const Matrix& other) = default;
        Matrix(Matrix&& other) noexcept = default;

        Matrix& operator=(const Matrix& other) = default;
        Matrix& operator=(Matrix&& other) noexcept = default;

        [[nodiscard]] size_t rows() const noexcept { return rows_; }
        [[nodiscard]] size_t columns() const noexcept { return columns_; }
        [[nodiscard]] const std::vector<std::vector<T>>& data() const noexcept { return data_; }
	
        [[nodiscard]] friend Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
            lhs.check_dimensions(rhs);
            Matrix result(lhs.rows_, lhs.columns_);
            for (size_t i = 0; i < lhs.rows_; ++i) {
                for (size_t j = 0; j < lhs.columns_; ++j) {
                    result.data_[i][j] = lhs.data_[i][j] + rhs.data_[i][j];
                }
            }
            return result;
        }
        [[nodiscard]] friend Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
            lhs.check_dimensions(rhs);
            Matrix result(lhs.rows_, lhs.columns_);
            for (size_t i = 0; i < lhs.rows_; ++i) {
                for (size_t j = 0; j < lhs.columns_; ++j) {
                    result.data_[i][j] = lhs.data_[i][j] - rhs.data_[i][j];
                }
            }
            return result;
        }
        [[nodiscard]] friend Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
            if (lhs.columns_ != rhs.rows_) {
                throw std::invalid_argument("Incompatible matrix dimensions for multiplication");
            }
            Matrix result(lhs.rows_, rhs.columns_);
            for (size_t i = 0; i < lhs.rows_; ++i) {
                for (size_t j = 0; j < rhs.columns_; ++j) {
                    for (size_t k = 0; k < lhs.columns_; ++k) {
                        result.data_[i][j] += lhs.data_[i][k] * rhs.data_[k][j];
                    }
                }
            }
            return result;
        }
        [[nodiscard]] friend Matrix operator*(const Matrix& matrix, T scalar) {
            Matrix result(matrix.rows_, matrix.columns_);
            for (size_t i = 0; i < matrix.rows_; ++i) {
                for (size_t j = 0; j < matrix.columns_; ++j) {
                    result.data_[i][j] = matrix.data_[i][j] * scalar;
                }
            }
            return result;
        }
        [[nodiscard]] friend Matrix operator*(T scalar, const Matrix& matrix) {
            return matrix * scalar;
        }
        friend bool operator==(const Matrix& lhs, const Matrix& rhs) {
            return lhs.data_ == rhs.data_;
        }
        friend bool operator!=(const Matrix& lhs, const Matrix& rhs) {
            return !(lhs == rhs);
        }
        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
            for (const auto& row : matrix.data_) {
                for (const auto& elem : row) {
                    os << elem << ' ';
                }
                os << '\n';
            }
            return os;
        }

        T& operator()(size_t i, size_t j) { return data_[i][j]; }
        const T& operator()(size_t i, size_t j) const { return data_[i][j]; }
        Matrix& operator+=(const Matrix& other) {
            check_dimensions(other);
            for (size_t i = 0; i < rows_; ++i) {
                for (size_t j = 0; j < columns_; ++j) {
                    data_[i][j] += other.data_[i][j];
                }
            }
            return *this;
        }
        Matrix& operator-=(const Matrix& other) {
            check_dimensions(other);
            for (size_t i = 0; i < rows_; ++i) {
                for (size_t j = 0; j < columns_; ++j) {
                    data_[i][j] -= other.data_[i][j];
                }
            }
            return *this;
        }
    };
}