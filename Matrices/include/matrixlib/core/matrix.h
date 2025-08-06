#pragma once

#include <iostream>
#include <vector>
#include <complex>

#include "type_traits.h"
#include "column.h"

namespace Core {

    using Core::Traits::is_valid_matrix_type;

	template<typename T>
	class Matrix {
	public:
        Matrix() noexcept : rows(0), columns(0) {}
        
        
        Matrix(size_t rows, size_t columns)
            noexcept(std::is_nothrow_constructible_v<std::vector<T>>)
            : data(rows, std::vector<T>(columns)),
            rows(rows),
            columns(columns) {}
        Matrix(size_t rows, size_t columns, const T& value)
            noexcept(std::is_nothrow_copy_constructible_v<T>)
            : data(rows, std::vector<T>(columns, value)),
            rows(rows),
            columns(columns) {}
        
        
        explicit Matrix(const std::vector<std::vector<T>>& data)
            : data(data),
            rows(data.size()),
            columns(data.empty() ? 0 : data[0].size())
        {
            check_rectangular();
        }
        
        
        Matrix(const Matrix& other) = default;
        Matrix(Matrix&& other) noexcept
            : data(std::move(other.data)),
            rows(other.rows),
            columns(other.columns){
            other.rows = other.columns = 0;  
        }
        
        ~Matrix() = default;

        Matrix& operator=(const Matrix& other) = default;
        Matrix& operator=(Matrix&& other) noexcept = default;

        [[nodiscard]] constexpr size_t get_rows() const noexcept { return rows; }
        [[nodiscard]] constexpr size_t get_columns() const noexcept { return columns; }

        [[nodiscard]] friend Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
            lhs.check_dimensions(rhs);
            Matrix result(lhs.rows, lhs.columns);
            for (size_t i = 0; i < lhs.rows; ++i) {
                for (size_t j = 0; j < lhs.columns; ++j) {
                    result.data[i][j] = lhs.data[i][j] + rhs.data[i][j];
                }
            }
            return result;
        }
        [[nodiscard]] friend Matrix operator+(Matrix&& lhs, const Matrix& rhs) {
            lhs += rhs;
            return std::move(lhs);
        }
        [[nodiscard]] friend Matrix operator+(const Matrix& lhs, Matrix&& rhs) {
            rhs += lhs;
            return std::move(rhs);
        }
        [[nodiscard]] friend Matrix operator+(Matrix&& lhs, Matrix&& rhs) {
            lhs += rhs;
            rhs = Matrix<T>();
            return std::move(lhs);
        }    
        
        
        [[nodiscard]] friend Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
            lhs.check_dimensions(rhs);
            Matrix result(lhs.rows, lhs.columns);
            for (size_t i = 0; i < lhs.rows; ++i) {
                for (size_t j = 0; j < lhs.columns; ++j) {
                    result.data[i][j] = lhs.data[i][j] - rhs.data[i][j];
                }
            }
            return result;
        }
        [[nodiscard]] friend Matrix operator-(Matrix&& lhs, const Matrix& rhs) {
            lhs -= rhs;
            return std::move(lhs);
        }
        [[nodiscard]] friend Matrix operator-(const Matrix& lhs, Matrix&& rhs) {
            for (size_t i = 0; i < lhs.rows; ++i) {
                for (size_t j = 0; j < lhs.columns; ++j) {
                    rhs(i, j) = lhs(i, j) - rhs(i, j);
                }
            }
            return std::move(rhs);
        }
        [[nodiscard]] friend Matrix operator-(Matrix&& lhs, Matrix&& rhs) {
            lhs -= rhs;
            rhs = Matrix<T>();
            return std::move(lhs);
        }
        
        
        [[nodiscard]] friend Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
            if (lhs.columns != rhs.rows) {
                throw std::invalid_argument("Incompatible matrix dimensions for multiplication");
            }
            Matrix result(lhs.rows, rhs.columns);
            for (size_t i = 0; i < lhs.rows; ++i) {
                for (size_t j = 0; j < rhs.columns; ++j) {
                    for (size_t k = 0; k < lhs.columns; ++k) {
                        result.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
                    }
                }
            }
            return result;
        }
        [[nodiscard]] friend Matrix operator*(const Matrix& matrix, T scalar) {
            Matrix result(matrix.rows, matrix.columns);
            for (size_t i = 0; i < matrix.rows; ++i) {
                for (size_t j = 0; j < matrix.columns; ++j) {
                    result.data[i][j] = matrix.data[i][j] * scalar;
                }
            }
            return result;
        }
        [[nodiscard]] friend Matrix operator*(T scalar, const Matrix& matrix) {
            return matrix * scalar;
        }
        [[nodiscard]] friend Matrix operator*(Matrix&& lhs, const Matrix& rhs) {
            if (lhs.columns != rhs.rows) {
                throw std::invalid_argument("Incompatible matrix dimensions for multiplication");
            }

            Matrix result(lhs.rows, rhs.columns);
            for (size_t i = 0; i < lhs.rows; ++i) {
                for (size_t j = 0; j < rhs.columns; ++j) {
                    result.data[i][j] = 0;
                    for (size_t k = 0; k < lhs.columns; ++k) {
                        result.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
                    }
                }
            }
            lhs = Matrix<T>();
            return result;
        }
        [[nodiscard]] friend Matrix operator*(const Matrix& lhs, Matrix&& rhs) {
            if (lhs.columns != rhs.rows) {
                throw std::invalid_argument("Incompatible matrix dimensions for multiplication");
            }

            Matrix result(lhs.rows, rhs.columns);
            for (size_t i = 0; i < lhs.rows; ++i) {
                for (size_t j = 0; j < rhs.columns; ++j) {
                    result.data[i][j] = 0;
                    for (size_t k = 0; k < lhs.columns; ++k) {
                        result.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
                    }
                }
            }
            rhs = Matrix<T>();
            return result;
        }
        [[nodiscard]] friend Matrix operator*(Matrix&& lhs, Matrix&& rhs) {
            if (lhs.columns != rhs.rows) {
                throw std::invalid_argument("Incompatible matrix dimensions for multiplication");
            }

            if (lhs.rows == lhs.rows && lhs.columns == rhs.columns) {
                for (size_t i = 0; i < lhs.rows; ++i) {
                    for (size_t j = 0; j < rhs.columns; ++j) {
                        T sum = 0;
                        for (size_t k = 0; k < lhs.columns; ++k) {
                            sum += lhs.data[i][k] * rhs.data[k][j];
                        }
                        lhs.data[i][j] = sum;
                    }
                }
                rhs = Matrix<T>();
                return std::move(lhs);
            }
            else {
                Matrix result(lhs.rows, rhs.columns);
                for (size_t i = 0; i < lhs.rows; ++i) {
                    for (size_t j = 0; j < rhs.columns; ++j) {
                        result.data[i][j] = 0;
                        for (size_t k = 0; k < lhs.columns; ++k) {
                            result.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
                        }
                    }
                }
                lhs = Matrix<T>();
                rhs = Matrix<T>();
                return result;
            }
        }
        
        friend bool operator==(const Matrix& lhs, const Matrix& rhs) {
            return lhs.data == rhs.data;
        }
        
        
        friend bool operator!=(const Matrix& lhs, const Matrix& rhs) {
            return !(lhs == rhs);
        }
        
        
        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
            for (const auto& row : matrix.data) {
                for (const auto& elem : row) {
                    os << elem << ' ';
                }
                os << '\n';
            }
            return os;
        }
 
        T& operator()(size_t i, size_t j) { return data[i][j]; }
        const T& operator()(size_t i, size_t j) const { return data[i][j]; }

        std::vector<T>& operator()(size_t i) { return data[i]; }
        const std::vector<T>& operator()(size_t i) const { return data[i]; }
        
        
        Matrix& operator+=(const Matrix& other) {
            check_dimensions(other);
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < columns; ++j) {
                    data[i][j] += other.data[i][j];
                }
            }
            return *this;
        }
        
        
        Matrix& operator-=(const Matrix& other) {
            check_dimensions(other);
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < columns; ++j) {
                    data[i][j] -= other.data[i][j];
                }
            }
            return *this;
        }
       
        
        Matrix& operator*=(T scalar) {
            for (auto& row : data) {
                for (auto& elem : row) {
                    elem *= scalar;
                }
            }
            return *this;
        }

        void identity_matrix(const T& value) {
            if (rows != columns) {
                throw std::invalid_argument("matrix must be square");
            }
            for (size_t i = 0; i < rows; ++i) {
                (*this)(i, i) = value;
            }
        }
        void fill(const T& value) {
            for (std::size_t i = 0; i < rows; ++i) {
                for (std::size_t j = 0; j < columns; ++j) {
                    (*this)(i, j) = value;
                }
            }
        }
        bool is_square() {
            return rows == columns;
        }
        void swap_rows(const size_t i, const size_t j) {
            if (i >= rows || j >= columns) {
                throw std::out_of_range("matrix indeces is out of range");
            }
           std::swap(data[i], data[j]);
        }

        Column_View<T> get_column(size_t j){
            if(j>=columns){
                throw std::out_of_range("Columns index out of range");
            }
            return Column_View<T>(&data[0][j], rows, columns);
        }
        Column_View<T> get_column(size_t j) const{
            if(j>=columns){
                throw std::out_of_range("Columns index out of range");
            }
            return Column_View<T>(&data[0][j], rows, columns);
        }

        auto begin() { return data.begin(); }
        auto end() { return data.end(); }
        
        
        auto begin() const { return data.begin(); }
        auto end() const { return data.end(); }
        
        
        auto cbegin() const { return data.cbegin(); }
        auto cend() const { return data.cend(); }
       

    private:
		static_assert(
			is_valid_matrix_type<T>::value,
			"Matrix<T> requires T to be either float, double or ComplexNumber<float/double>");

		
        std::vector<std::vector<T>> data;
		
        size_t rows;
		size_t columns;

        void check_rectangular() const {
            for (const auto& row : data) {
                if (row.size() != columns) {
                    throw std::invalid_argument("All rows must have the same length");
                }
            }
        }
        void check_dimensions(const Matrix& other) const {
            if (rows != other.rows || columns != other.columns) {
                throw std::invalid_argument("Matrix dimensions must agree");
            }
        }
    
        //TODO: оптимизировать умножение
        Matrix<T> multiply_classic(const Matrix& other) const{}
        Matrix<T> multiply_blocked(const Matrix& other, size_t block_size = 32) const{}
    };
}