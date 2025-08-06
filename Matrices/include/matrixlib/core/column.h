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
            :column_pointer_(column_pointer), size_(size), stride_(stride){}

        T& operator[](size_t i){
            return column_pointer_[i*stride_];
        }
        const T& operator[](size_t i) const{
            return column_pointer_[i*stride_];
        }

        T* begin(){ return column_pointer_; } 
        T* end(){ return column_pointer_ + size_ * stride_; }

        size_t get_size() const{ return size_;}

        typename std::conditional_t<is_complex<T>::value, typename T::value_type, T>
            vector_l2_norm() const{
                using ReturnType = typename std::conditional_t<is_complex<T>::value, typename T::value_type, T>;
                ReturnType result{};
                for(size_t i = 0; i < size_; ++i){
                    result+=std::norm((*this)[i]);
                }
                return std::sqrt(result);
        }

        typename std::conditional_t<is_complex<T>::value, typename T::value_type, T>
            vector_l1_norm() const{
                using ReturnType = typename std::conditional_t<is_complex<T>::value, typename T::value_type, T>;
                ReturnType result{};
                for(size_t i = 0; i < size_; ++i){
                    result += std::abs((*this)[i]);
                }
                return result;
        }

        typename std::conditional_t<is_complex<T>::value, typename T::value_type, T>
            vector_max_norm() const{
                using ReturnType = typename std::conditional_t<is_complex<T>::value, typename T::value_type, T>;

                ReturnType result{};

                for(size_t i = 0; i < size_; ++i){
                    result = std::max(result, std::abs((*this)[i]));
                }

                return result;
        }

        Column_View<T> subview(const size_t start_at){
            if(start_at >= size_){
                throw std::invalid_argument("Start index is out of range");
            }

            return Column_View<T>(column_pointer_ + start_at * stride_, size_ - start_at, stride_);
        }
    private:
        T* column_pointer_;
        size_t size_;
        size_t stride_;

    };
    
}