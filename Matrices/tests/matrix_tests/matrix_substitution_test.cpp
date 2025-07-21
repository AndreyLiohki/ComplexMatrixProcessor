#include "pch.h"

#include "../MatrixLib/include/matrixlib/core/matrix.h"

namespace {

	using namespace Core;

    TEST(MatrixSubtractionTest, TwoConstMatrices) {
        Matrix<double> A(2, 2);
        A(0, 0) = 5.0; A(0, 1) = 3.0;
        A(1, 0) = 2.0; A(1, 1) = 7.0;

        Matrix<double> B(2, 2);
        B(0, 0) = 1.0; B(0, 1) = 4.0;
        B(1, 0) = 6.0; B(1, 1) = 2.0;

        auto result = A - B;

        EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
        EXPECT_DOUBLE_EQ(result(0, 1), -1.0);
        EXPECT_DOUBLE_EQ(result(1, 0), -4.0);
        EXPECT_DOUBLE_EQ(result(1, 1), 5.0);
    }

    TEST(MatrixSubtractionTest, RvalueLeft) {
        Matrix<double> A(2, 2, 5.0);
        const Matrix<double> B(2, 2, 3.0);

        auto result = std::move(A) - B;

        EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
        EXPECT_DOUBLE_EQ(result(1, 1), 2.0);
        EXPECT_EQ(A.get_rows(), 0);
    }

    TEST(MatrixSubtractionTest, ConstLvalueMinusRvalue) {
        const Matrix<double> A(2, 2, 5.0);
        Matrix<double> B(2, 2, 3.0);

        auto result = A - std::move(B);

        EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
        EXPECT_DOUBLE_EQ(result(1, 1), 2.0);
        EXPECT_EQ(B.get_rows(), 0);
    }

    TEST(MatrixSubtractionTest, TwoRvalues) {
        Matrix<double> A(2, 2, 5.0);
        Matrix<double> B(2, 2, 3.0);

        auto result = std::move(A) - std::move(B);

        EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
        EXPECT_DOUBLE_EQ(result(1, 1), 2.0);
        EXPECT_EQ(A.get_rows(), 0);
        EXPECT_EQ(B.get_rows(), 0);
    }

    TEST(MatrixSubtractionTest, IncompatibleDimensions) {
        Matrix<double> A(2, 3);
        Matrix<double> B(3, 2);

        EXPECT_THROW(A - B, std::invalid_argument);
    }

    TEST(MatrixSubtractionTest, CompoundAssignment) {
        Matrix<double> A(2, 2);
        A(0, 0) = 5.0; A(0, 1) = 3.0;
        A(1, 0) = 2.0; A(1, 1) = 7.0;

        Matrix<double> B(2, 2);
        B(0, 0) = 1.0; B(0, 1) = 4.0;
        B(1, 0) = 6.0; B(1, 1) = 2.0;

        A -= B;

        EXPECT_DOUBLE_EQ(A(0, 0), 4.0);
        EXPECT_DOUBLE_EQ(A(0, 1), -1.0);
        EXPECT_DOUBLE_EQ(A(1, 0), -4.0);
        EXPECT_DOUBLE_EQ(A(1, 1), 5.0);
    }
}