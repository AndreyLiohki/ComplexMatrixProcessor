#include "pch.h"
#include "../MatrixLib/include/matrixlib/core/matrix.h"

namespace {
	using namespace Core;

    TEST(MatrixAdditionTest, TwoConstMatrices) {
        const Matrix<double> matrix_1(2, 2, 1.0);
        const Matrix<double> matrix_2(2, 2, 3.0);

        auto result = matrix_1 + matrix_2;

        EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
        EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
        EXPECT_DOUBLE_EQ(result(1, 0), 4.0);
        EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
    }

    TEST(MatrixAdditionTest, RvalueLeft) {
        Matrix<double> matrix_1(2, 2, 1.0);
        const Matrix<double> matrix_2(2, 2, 3.0);

        auto result = std::move(matrix_1) + matrix_2;

        EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
        EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
        EXPECT_DOUBLE_EQ(result(1, 0), 4.0);
        EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
        EXPECT_EQ(matrix_1.get_rows(), 0);
    }

    TEST(MatrixAdditionTest, RvalueRight) {
        const Matrix<double> matrix_1(2, 2, 1.0);
        Matrix<double> matrix_2(2, 2, 3.0);

        auto result = matrix_1 + std::move(matrix_2);

        EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
        EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
        EXPECT_DOUBLE_EQ(result(1, 0), 4.0);
        EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
        EXPECT_EQ(matrix_2.get_rows(), 0); 
    }

    TEST(MatrixAdditionTest, TwoRvalues) {
        Matrix<double> matrix_1(2, 2, 1.0);
        Matrix<double> matrix_2(2, 2, 3.0);

        auto result = std::move(matrix_1) + std::move(matrix_2);

        EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
        EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
        EXPECT_DOUBLE_EQ(result(1, 0), 4.0);
        EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
        EXPECT_EQ(matrix_1.get_rows(), 0); 
        EXPECT_EQ(matrix_2.get_rows(), 0); 
    }

    TEST(MatrixAdditionTest, PlusEqualsInRvalueVersion) {
        Matrix<double> matrix_1(2, 2);
        matrix_1(0, 0) = 1.0; matrix_1(0, 1) = 2.0;
        matrix_1(1, 0) = 3.0; matrix_1(1, 1) = 4.0;

        Matrix<double> matrix_2(2, 2, 1.0);

        auto result = std::move(matrix_1) + matrix_2;

        EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
        EXPECT_DOUBLE_EQ(result(0, 1), 3.0);
        EXPECT_DOUBLE_EQ(result(1, 0), 4.0);
        EXPECT_DOUBLE_EQ(result(1, 1), 5.0);
    }

	TEST(matrix_substraction_test, simple_substraction) {
		Matrix<double> matrix_1(2, 2, 1.0);
		Matrix<double> matrix_2(2, 2, 3.0);

		auto result = matrix_1 - matrix_2;

		EXPECT_DOUBLE_EQ(result(0, 0), -2.0);
		EXPECT_DOUBLE_EQ(result(0, 1), -2.0);
		EXPECT_DOUBLE_EQ(result(1, 0), -2.0);
		EXPECT_DOUBLE_EQ(result(1, 1), -2.0);
	}
}
