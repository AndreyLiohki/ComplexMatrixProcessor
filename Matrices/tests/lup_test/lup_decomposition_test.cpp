#include <gtest/gtest.h>
#include "../../include/matrixlib/decompositions/lup_decomposition.h"
#include "../../include/matrixlib/core/matrix.h"

using namespace Decompositions::LUP_Decomposition;
using Core::Matrix;

TEST(LUPDecompositionTest, BasicDecomposition) {
    Matrix<double> m(3, 3);
    m(0, 0) = 1; m(0, 1) = 2; m(0, 2) = 3;
    m(1, 0) = 4; m(1, 1) = 5; m(1, 2) = 6;
    m(2, 0) = 7; m(2, 1) = 8; m(2, 2) = 10;

    Lup_Decomposition<double> lup(m);
    
    const auto& L = lup.get_L();
    const auto& U = lup.get_U();
    const auto& P = lup.get_P();
    
    EXPECT_EQ(L.get_rows(), 3);
    EXPECT_EQ(L.get_columns(), 3);
    EXPECT_EQ(U.get_rows(), 3);
    EXPECT_EQ(U.get_columns(), 3);
    EXPECT_EQ(P.get_rows(), 3);
    EXPECT_EQ(P.get_columns(), 3);
    
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if (i > j) {
                EXPECT_EQ(U(i, j), 0);
            } else if (i < j) {
                EXPECT_EQ(L(i, j), 0);
            } else {
                EXPECT_EQ(L(i, i), 1);
            }
        }
    }
    
    Matrix<double> PA = P * m;
    Matrix<double> LU = L * U;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_NEAR(PA(i, j), LU(i, j), 1e-10);
        }
    }
}

TEST(LUPDecompositionTest, SingularMatrix) {
    Matrix<double> m(3, 3, 1.0);
    
    EXPECT_THROW({
        Lup_Decomposition<double> lup(m);
    }, std::runtime_error);
}

TEST(LUPDecompositionTest, NonSquareMatrix) {
    Matrix<double> m(3, 2);
    
    EXPECT_THROW({
        Lup_Decomposition<double> lup(m);
    }, std::invalid_argument);
}

TEST(LUPDecompositionTest, EmptyMatrix) {
    Matrix<double> m(0, 0);
    
    EXPECT_THROW({
        Lup_Decomposition<double> lup(m);
    }, std::invalid_argument);
}

TEST(LUPDecompositionTest, ComplexNumbers) {
    using Complex = std::complex<double>;
    Matrix<Complex> m(2, 2);
    m(0, 0) = {1, 0}; m(0, 1) = {2, 1};
    m(1, 0) = {3, -1}; m(1, 1) = {4, 0};
    
    Lup_Decomposition<Complex> lup(m);
    
    const auto& L = lup.get_L();
    const auto& U = lup.get_U();
    const auto& P = lup.get_P();
    
    Matrix<Complex> PA = P * m;
    Matrix<Complex> LU = L * U;
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            EXPECT_NEAR(PA(i, j).real(), LU(i, j).real(), 1e-10);
            EXPECT_NEAR(PA(i, j).imag(), LU(i, j).imag(), 1e-10);
        }
    }
}

TEST(LUPDecompositionTest, PermutationCount) {
    Matrix<double> m(3, 3);
    m(0, 0) = 0; m(0, 1) = 1; m(0, 2) = 2;
    m(1, 0) = 1; m(1, 1) = 2; m(1, 2) = 3;
    m(2, 0) = 2; m(2, 1) = 3; m(2, 2) = 5;
    
    Lup_Decomposition<double> lup(m);
    EXPECT_GT(lup.get_permutations(), 0);
}