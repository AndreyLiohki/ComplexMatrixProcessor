#include <gtest/gtest.h>

#include <complex>
#include <vector>

#include "../../include/matrixlib/algebra/numerical_characteristics.h"

using namespace Core;
using namespace Decompositions;
using namespace Algebra::Characteristics;
using std::complex;
using std::vector;

TEST(LinearAlgebraTest, TraceFunction) {
    Matrix<double> mat1(3, 3);
    mat1(0,0) = 1.0; mat1(0,1) = 2.0; mat1(0,2) = 3.0;
    mat1(1,0) = 4.0; mat1(1,1) = 5.0; mat1(1,2) = 6.0;
    mat1(2,0) = 7.0; mat1(2,1) = 8.0; mat1(2,2) = 9.0;
    EXPECT_DOUBLE_EQ(trace(mat1), 15.0);

    Matrix<float> mat2(2, 2);
    mat2(0,0) = 1.5f; mat2(0,1) = 2.5f;
    mat2(1,0) = 3.5f; mat2(1,1) = 4.5f;
    EXPECT_FLOAT_EQ(trace(mat2), 6.0f);

    Matrix<complex<double>> mat3(2, 2);
    mat3(0,0) = {1.0, 2.0}; mat3(0,1) = {3.0, 4.0};
    mat3(1,0) = {5.0, 6.0}; mat3(1,1) = {7.0, 8.0};
    EXPECT_EQ(trace(mat3), complex<double>(8.0, 10.0));
}

TEST(LinearAlgebraTest, RankFunction) {
    Matrix<double> full_rank(3, 3);
    full_rank(0,0) = 1.0; full_rank(1,1) = 1.0; full_rank(2,2) = 1.0;
    EXPECT_EQ(rank(full_rank, 1e-10), 3);

    Matrix<double> rank_def(3, 3);
    rank_def(0,0) = 1.0; rank_def(0,1) = 2.0;
    rank_def(1,0) = 2.0; rank_def(1,1) = 4.0;
    EXPECT_EQ(rank(rank_def, 1e-10), 1);

    using Complex = std::complex<double>;
    Matrix<Complex> complex_mat(2, 2);
    complex_mat(0,0) = Complex(1,0); 
    complex_mat(1,1) = Complex(0,1);
    EXPECT_EQ(rank(complex_mat, 1e-10), 2);

    Matrix<double> empty(0, 0);
    EXPECT_EQ(rank(empty, 1e-10), 0);
}

TEST(LinearAlgebraTest, DeterminantFunction) {
    Matrix<double> mat1(2, 2);
    mat1(0,0) = 1.0; mat1(0,1) = 2.0;
    mat1(1,0) = 3.0; mat1(1,1) = 4.0;
    auto lup1 = LUP_Decomposition::Lup_Decomposition(mat1);
    EXPECT_DOUBLE_EQ(determinant(lup1), -2.0);

    Matrix<float> mat2(3, 3, 0.0f);
    mat2(0,0) = 2.0f; mat2(1,1) = 3.0f; mat2(2,2) = 4.0f;
    auto lup2 = LUP_Decomposition::Lup_Decomposition(mat2);
    EXPECT_FLOAT_EQ(determinant(lup2), 24.0f);
}

TEST(LinearAlgebraTest, EigenValuesFunction) {
    Matrix<double> mat1(2, 2);
    mat1(0,0) = 2.0; mat1(0,1) = 1.0;
    mat1(1,0) = 1.0; mat1(1,1) = 2.0;
    auto qr1 = QR_Decomposition::Qr_Decomposition(mat1);
    auto ev1 = eigen_values(qr1, 50);
    EXPECT_NEAR(ev1[0], 3.0, 1e-6);
    EXPECT_NEAR(ev1[1], 1.0, 1e-6);

    // Тест с complex<double>
    Matrix<complex<double>> mat2(2, 2);
    mat2(0,0) = {0.0, -1.0}; mat2(0,1) = {0.0, 0.0};
    mat2(1,0) = {0.0, 0.0}; mat2(1,1) = {0.0, 1.0};
    auto qr2 = QR_Decomposition::Qr_Decomposition(mat2);
    auto ev2 = eigen_values(qr2, 50);
    std::vector<double> imag_parts = {ev2[0].imag(), ev2[1].imag()};
    std::sort(imag_parts.begin(), imag_parts.end());
    EXPECT_NEAR(imag_parts[0], -1.0, 1e-6);
    EXPECT_NEAR(imag_parts[1], 1.0, 1e-6);
}