#pragma once

#include <complex>
#include <vector>

#include "../core/matrix.h"
#include "../algebra/matrix_operations.h"
#include "../core/type_traits.h"

namespace Decompositions{
    namespace SVD_Decomposition{

        using Core::Traits::is_complex;
        using Core::Traits::norm_value_type;
        using Core::Traits::is_valid_matrix_type;
        using Core::Traits::default_epsilon;

        using Core::Matrix;

        using namespace Algebra::Operations;
    
        template<typename T>
        class Svd_Decomposition{
        public:
            const Matrix<T>& get_S() const { return S_; }
            const Matrix<T>& get_V() const { return V_; }
            const Matrix<T>& get_D() const { return D_; }

            explicit Svd_Decomposition(const Matrix<T>& matrix){

            }
        private:
            static_assert(
				is_valid_matrix_type<T>::value,
				"Matrix<T> requires T to be either float, double, long double or ComplexNumber<float/double/long double>");

            Matrix<T> S_;
            Matrix<T> V_;
            Matrix<T> D_;

            bool decomposed = false;

            bool is_decomposed(){
                return decomposed;
            }
        };
    }
}