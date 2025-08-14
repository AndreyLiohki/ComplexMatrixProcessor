#include <gtest/gtest.h>

#include <complex>

#include "../include/matrixlib/algebra/matrix_properties.h"
#include "../include/matrixlib/core/matrix.h"


using namespace Algebra::Properties;
using namespace Core;

TEST(MatrixUtilsTest, IsApproximatelyZeroFloatingPoint) {
    EXPECT_TRUE(::is_approximately_zero(0.0f, 1e-6f));
    EXPECT_TRUE(is_approximately_zero(1e-7f, 1e-6f));
    EXPECT_FALSE(is_approximately_zero(1e-5f, 1e-6f));
    EXPECT_TRUE(is_approximately_zero(-1e-7f, 1e-6f));
    EXPECT_FALSE(is_approximately_zero(-1e-5f, 1e-6f));
}

TEST(MatrixUtilsTest, IsApproximatelyZeroComplex) {
    using Complex = std::complex<float>;
    EXPECT_TRUE(is_approximately_zero(Complex(0, 0), 1e-6f));
    EXPECT_TRUE(is_approximately_zero(Complex(1e-7f, 1e-7f), 1e-6f));
    EXPECT_FALSE(is_approximately_zero(Complex(1e-5f, 0), 1e-6f));
    EXPECT_FALSE(is_approximately_zero(Complex(0, 1e-5f), 1e-6f));
}

TEST(MatrixUtilsTest, IsZeroMatrix) {
    Matrix<float> zero3x3(3, 3, 0.0f);
    Matrix<float> almostZero3x3(3, 3, 1e-7f);
    Matrix<float> nonZero3x3(3, 3, 1.0f);
    nonZero3x3(1,1) = 0.0f;
    
    EXPECT_TRUE(is_zero_matrix(zero3x3));
    EXPECT_TRUE(is_zero_matrix(almostZero3x3, 1e-6f));
    EXPECT_FALSE(is_zero_matrix(nonZero3x3));
    EXPECT_FALSE(is_zero_matrix(almostZero3x3, 1e-8f));
}

TEST(MatrixUtilsTest, MatrixSparsity) {
    Matrix<double> dense(2, 2, 1.0);
    Matrix<double> sparse(3, 3, 0.0);
    sparse(1,1) = 1.0;
    
    auto denseSparsity = matrix_sparsity(dense);
    auto sparseSparsity = matrix_sparsity(sparse);
    
    EXPECT_EQ(denseSparsity.first, 0);
    EXPECT_EQ(denseSparsity.second, 4);
    
    EXPECT_EQ(sparseSparsity.first, 8);
    EXPECT_EQ(sparseSparsity.second, 1);
}

TEST(MatrixUtilsTest, IsSymmetric) {
    Matrix<double> symmetric(3, 3, 0.0);
    symmetric(0,0)=1; symmetric(0,1)=2; symmetric(0,2)=3;
    symmetric(1,1)=4; symmetric(1,2)=5; symmetric(2,2)=6;
    symmetric(1,0)=2; symmetric(2,0)=3; symmetric(2,1)=5;
    
    Matrix<double> nonSymmetric(2, 2, 0.0);
    nonSymmetric(0,0)=1; nonSymmetric(0,1)=2;
    nonSymmetric(1,0)=3; nonSymmetric(1,1)=4;
    
    Matrix<double> notSquare(2, 3, 0.0);
    
    EXPECT_TRUE(is_symmetric(symmetric));
    EXPECT_FALSE(is_symmetric(nonSymmetric));
    EXPECT_FALSE(is_symmetric(notSquare));
}

TEST(MatrixUtilsTest, IsHermitian) {
    using Complex = std::complex<double>;
    Matrix<Complex> hermitian(2, 2);
    hermitian(0,0) = Complex(1, 0);
    hermitian(0,1) = Complex(2, 3);
    hermitian(1,0) = Complex(2, -3);
    hermitian(1,1) = Complex(4, 0);
    
    Matrix<Complex> nonHermitian(2, 2);
    nonHermitian(0,0) = Complex(1, 1);
    nonHermitian(0,1) = Complex(2, 3);
    nonHermitian(1,0) = Complex(2, -3);
    nonHermitian(1,1) = Complex(4, 0);
    
    EXPECT_TRUE(is_hermitian(hermitian));
    EXPECT_FALSE(is_hermitian(nonHermitian));
}

TEST(MatrixUtilsTest, IsSkewSymmetric) {
    Matrix<float> skewSymm(3, 3, 0.0);
    skewSymm(0,1)= 2; skewSymm(0,2)= 3;
    skewSymm(1,0)=-2; skewSymm(1,2)= 4;
    skewSymm(2,0)=-3; skewSymm(2,1)=-4;
    
    Matrix<float> nonSkewSymm(2, 2);
    nonSkewSymm(0,0)=0; nonSkewSymm(0,1)=1;
    nonSkewSymm(1,0)=1; nonSkewSymm(1,1)=0;
    
    EXPECT_TRUE(is_skew_symmetric(skewSymm));
    EXPECT_FALSE(is_skew_symmetric(nonSkewSymm));
}

TEST(MatrixUtilsTest, IsAntiHermitian) {
    using Complex = std::complex<double>;
    Matrix<Complex> antihermitian(2, 2);
    antihermitian(0,0) = Complex(0, 1); 
    antihermitian(0,1) = Complex(2, 3);
    antihermitian(1,0) = Complex(-2, 3);
    
    Matrix<Complex> nonAntihermitian(2, 2);
    nonAntihermitian(0,0) = Complex(1, 1);
    nonAntihermitian(0,1) = Complex(2, 3);
    nonAntihermitian(1,0) = Complex(-2, 3);
    
    EXPECT_TRUE(is_antihermitian(antihermitian));
    EXPECT_FALSE(is_antihermitian(nonAntihermitian));
}