#include <gtest/gtest.h>

#include <complex>

#include "../include/matrixlib/algebra/matrix_operations.h"


using namespace Core;
using namespace Algebra::Operations;

TEST(MatrixOperationsTest, TransposeConstMatrix) {
    Matrix<double> mat(2, 3);
    mat(0,0) = 1.0; mat(0,1) = 2.0; mat(0,2) = 3.0;
    mat(1,0) = 4.0; mat(1,1) = 5.0; mat(1,2) = 6.0;

    auto transposed = transpose(mat);
    
    ASSERT_EQ(transposed.get_rows(), 3);
    ASSERT_EQ(transposed.get_columns(), 2);
    EXPECT_DOUBLE_EQ(transposed(0,0), 1.0);
    EXPECT_DOUBLE_EQ(transposed(1,0), 2.0);
    EXPECT_DOUBLE_EQ(transposed(2,0), 3.0);
    EXPECT_DOUBLE_EQ(transposed(0,1), 4.0);
    EXPECT_DOUBLE_EQ(transposed(1,1), 5.0);
    EXPECT_DOUBLE_EQ(transposed(2,1), 6.0);

    EXPECT_DOUBLE_EQ(mat(0,0), 1.0);
    EXPECT_DOUBLE_EQ(mat(0,1), 2.0);
}

TEST(MatrixOperationsTest, TransposeRvalueMatrix) {
    Matrix<double> mat(2, 2);
    mat(0,0) = 1; mat(0,1) = 2;
    mat(1,0) = 3; mat(1,1) = 4;

    auto transposed = transpose(std::move(mat));
    
    ASSERT_EQ(transposed.get_rows(), 2);
    ASSERT_EQ(transposed.get_columns(), 2);
    EXPECT_EQ(transposed(0,0), 1);
    EXPECT_EQ(transposed(1,0), 2);
    EXPECT_EQ(transposed(0,1), 3);
    EXPECT_EQ(transposed(1,1), 4);
}

TEST(MatrixOperationsTest, HermitianConstMatrix) {
    using Complex = std::complex<double>;
    Matrix<Complex> mat(2, 2);
    mat(0,0) = Complex(1, 1); mat(0,1) = Complex(2, 3);
    mat(1,0) = Complex(4, 5); mat(1,1) = Complex(6, 7);

    auto hermitian = hermitian_matrix(mat);
    
    ASSERT_EQ(hermitian.get_rows(), 2);
    ASSERT_EQ(hermitian.get_columns(), 2);
    EXPECT_EQ(hermitian(0,0), Complex(1, -1));
    EXPECT_EQ(hermitian(1,0), Complex(2, -3));
    EXPECT_EQ(hermitian(0,1), Complex(4, -5));
    EXPECT_EQ(hermitian(1,1), Complex(6, -7));

    EXPECT_EQ(mat(0,0), Complex(1, 1));
    EXPECT_EQ(mat(0,1), Complex(2, 3));
}

TEST(MatrixOperationsTest, HermitianRvalueMatrix) {
    using Complex = std::complex<float>;
    Matrix<Complex> mat(1, 2);
    mat(0,0) = Complex(1.0f, 2.0f);
    mat(0,1) = Complex(3.0f, 4.0f);

    auto hermitian = hermitian_matrix(std::move(mat));
    
    ASSERT_EQ(hermitian.get_rows(), 2);
    ASSERT_EQ(hermitian.get_columns(), 1);
    EXPECT_EQ(hermitian(0,0), Complex(1.0f, -2.0f));
    EXPECT_EQ(hermitian(1,0), Complex(3.0f, -4.0f));

}

TEST(MatrixOperationsTest, HermitianSFINAE) {

    using Complex = std::complex<double>;
    Matrix<Complex> mat(1, 1);
    mat(0,0) = Complex(1, 0);
    EXPECT_NO_THROW(hermitian_matrix(mat));
}

TEST(MatrixOperationsTest, EmptyMatrix) {
    Matrix<double> mat(0, 0);
    auto transposed = transpose(mat);
    EXPECT_EQ(transposed.get_rows(), 0);
    EXPECT_EQ(transposed.get_columns(), 0);

    using Complex = std::complex<double>;
    Matrix<Complex> cmat(0, 0);
    auto hermitian = hermitian_matrix(cmat);
    EXPECT_EQ(hermitian.get_rows(), 0);
    EXPECT_EQ(hermitian.get_columns(), 0);
}