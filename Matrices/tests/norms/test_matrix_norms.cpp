#include <gtest/gtest.h>
#include <complex>

#include "../../include/matrixlib/algebra/norms.h" 
#include "../../include/matrixlib/core/matrix.h"

using namespace Algebra::Norms;
using namespace Core;

template<typename T>
Matrix<T> make_matrix(std::vector<std::vector<T>> values) {
    size_t rows = values.size();
    size_t cols = values[0].size();
    Matrix<T> mat(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            mat(i, j) = values[i][j];
    return mat;
}

TEST(NormsTest, FrobeniusNormReal) {
    auto mat = make_matrix<double>({
        {1.0, 2.0},
        {3.0, 4.0}
    });
    double expected = std::sqrt(1 + 4 + 9 + 16);
    EXPECT_DOUBLE_EQ(frobenius_norm(mat), expected);
}

TEST(NormsTest, InductiveL1NormColumnsReal) {
    auto mat = make_matrix<double>({
        {1.0, -2.0},
        {3.0, 4.0}
    });
    EXPECT_DOUBLE_EQ(inductive_l_one_norm_columns(mat), 6.0);
}

TEST(NormsTest, InductiveL1NormRowsReal) {
    auto mat = make_matrix<double>({
        {1.0, -2.0},
        {3.0, 4.0}
    });
    EXPECT_DOUBLE_EQ(inductive_l_one_norm_rows(mat), 7.0);
}

TEST(NormsTest, MaxNormReal) {
    auto mat = make_matrix<double>({
        {1.0, -2.0},
        {3.0, 4.5}
    });
    EXPECT_DOUBLE_EQ(max_norm(mat), 4.5);
}

TEST(NormsTest, L1NormReal) {
    auto mat = make_matrix<double>({
        {1.0, -2.0},
        {3.0, 4.0}
    });
    EXPECT_DOUBLE_EQ(l1_norm(mat), 10.0);
}
