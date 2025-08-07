#pragma once

#include<complex>

#include "type_traits.h"

namespace Core{

    using Core::Traits::is_complex;
    using Core::Traits::is_valid_matrix_type;

    template<typename T>
    class Column_View{
    public:
        Column_View(T* column_pointer, size_t size, size_t stride = 1)
            :column_pointer_(column_pointer), size_(size), stride_(stride){
                if (column_pointer_ == nullptr) {
            throw std::invalid_argument("Column pointer cannot be null");
            }
        }

        T& operator[](size_t i){
            return column_pointer_[i*stride_];
        }
        const T& operator[](size_t i) const{
            return column_pointer_[i*stride_];
        }

        T* begin(){ return column_pointer_; } 
        T* end(){ return column_pointer_ + size_ * stride_; }
        const T* begin() const { return column_pointer_; }
        const T* end() const { return column_pointer_ + size_ * stride_; }

        Column_View(const Column_View&) = default;
        Column_View& operator=(const Column_View&) = default;

        size_t get_size() const{ return size_;}

        Traits::NormType<T> vector_l2_norm() const {
            Traits::NormType<T> result{};
            for (size_t i = 0; i < size_; ++i) {
                if constexpr (Traits::is_complex<T>::value) {
                    result += std::norm((*this)[i]);
                } else {
                    result += (*this)[i] * (*this)[i];
                }
            }
            return std::sqrt(result);
        }

        Traits::NormType<T> vector_l1_norm() const {
            Traits::NormType<T> result{};
            for (size_t i = 0; i < size_; ++i) {
                result += std::abs((*this)[i]);
            }
            return result;
        }

        Traits::NormType<T> vector_max_norm() const {
            if (size_ == 0) return Traits::NormType<T>{};
            
            auto current_max = std::abs((*this)[0]);
            for (size_t i = 1; i < size_; ++i) {
                current_max = std::max(current_max, std::abs((*this)[i]));
            }
            return current_max;
        }

        Column_View<T> subview(const size_t start_at){
            if(start_at >= size_){
                throw std::invalid_argument("Start index is out of range");
            }

            return Column_View<T>(column_pointer_ + start_at * stride_, size_ - start_at, stride_);
        }
    
    private:

        static_assert(
			is_valid_matrix_type<T>::value,
			"Matrix<T> requires T to be either float, double or ComplexNumber<float/double>");
        T* column_pointer_;
        size_t size_;
        size_t stride_;

    };
    
}