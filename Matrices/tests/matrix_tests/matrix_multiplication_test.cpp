#include "pch.h"

#include "../MatrixLib/include/matrixlib/core/matrix.h"

namespace {
	using namespace Core;

	TEST(MatrixMultiplicationTest, TwoConstMatrices) {
		Matrix<double> matrix_1(2, 2);
		Matrix<double> matrix_2(2, 2);

		matrix_1(0, 0) = 2.0;
		matrix_1(0, 1) = 3.0;
		matrix_1(1, 0) = 1.0;
		matrix_1(1, 1) = 4.0;

		matrix_2(0, 0) = 1.0;
		matrix_2(0, 1) = 4.0;
		matrix_2(1, 0) = 2.0;
		matrix_2(1, 1) = 5.0;
		
		auto result = matrix_1 * matrix_2;

		EXPECT_DOUBLE_EQ(result(0, 0), 8.0);
		EXPECT_DOUBLE_EQ(result(0, 1), 23.0);
		EXPECT_DOUBLE_EQ(result(1, 0), 9.0);
		EXPECT_DOUBLE_EQ(result(1, 1), 24.0);

	}

    TEST(MatrixMultiplicationTest, MatrixScalarRight) {
        Matrix<double> A(2, 2);
        A(0, 0) = 1.0; A(0, 1) = 2.0;
        A(1, 0) = 3.0; A(1, 1) = 4.0;

        auto result = A * 2.5;

        EXPECT_DOUBLE_EQ(result(0, 0), 2.5);
        EXPECT_DOUBLE_EQ(result(0, 1), 5.0);
        EXPECT_DOUBLE_EQ(result(1, 0), 7.5);
        EXPECT_DOUBLE_EQ(result(1, 1), 10.0);
    }

    TEST(MatrixMultiplicationTest, ScalarMatrixLeft) {
        Matrix<double> A(2, 2);
        A(0, 0) = 1.0; A(0, 1) = 2.0;
        A(1, 0) = 3.0; A(1, 1) = 4.0;

        auto result = 2.5 * A;

        EXPECT_DOUBLE_EQ(result(0, 0), 2.5);
        EXPECT_DOUBLE_EQ(result(0, 1), 5.0);
        EXPECT_DOUBLE_EQ(result(1, 0), 7.5);
        EXPECT_DOUBLE_EQ(result(1, 1), 10.0);
    }

    TEST(MatrixMultiplicationTest, IncompatibleDimensions) {
        Matrix<double> A(2, 3);
        Matrix<double> B(4, 2);

        EXPECT_THROW(A * B, std::invalid_argument);
    }

    TEST(MatrixMultiplicationTest, NonSquareMatrices) {
        Matrix<double> A(2, 3);
        A(0, 0) = 1.0; A(0, 1) = 2.0; A(0, 2) = 3.0;
        A(1, 0) = 4.0; A(1, 1) = 5.0; A(1, 2) = 6.0;

        Matrix<double> B(3, 2);
        B(0, 0) = 7.0; B(0, 1) = 8.0;
        B(1, 0) = 9.0; B(1, 1) = 10.0;
        B(2, 0) = 11.0; B(2, 1) = 12.0;

        auto result = A * B;

        EXPECT_DOUBLE_EQ(result(0, 0), 58.0);  
        EXPECT_DOUBLE_EQ(result(0, 1), 64.0);   
        EXPECT_DOUBLE_EQ(result(1, 0), 139.0);
        EXPECT_DOUBLE_EQ(result(1, 1), 154.0);  
    }
}