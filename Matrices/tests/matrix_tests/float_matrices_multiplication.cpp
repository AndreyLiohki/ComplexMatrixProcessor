#include "pch.h"
#include "../MatrixLib/include/matrixlib/core/matrix.h"

namespace {
    using namespace Core;

    class FloatMatrixMultiplicationTest : public ::testing::Test {
    protected:
        void SetUp() override {
            m1 = Matrix<float>(2, 2, 1.0f);
            m2 = Matrix<float>(2, 2, 2.0f);

            m3 = Matrix<float>(2, 3);
            m3(0, 0) = 1.0f; m3(0, 1) = 2.0f; m3(0, 2) = 3.0f;
            m3(1, 0) = 4.0f; m3(1, 1) = 5.0f; m3(1, 2) = 6.0f;

            m4 = Matrix<float>(3, 2);
            m4(0, 0) = 7.0f;  m4(0, 1) = 8.0f;
            m4(1, 0) = 9.0f;  m4(1, 1) = 10.0f;
            m4(2, 0) = 11.0f; m4(2, 1) = 12.0f;

            m_empty = Matrix<float>(2, 2);
        }

        Matrix<float> m1, m2, m3, m4, m_empty;
    };

    TEST_F(FloatMatrixMultiplicationTest, SquareMatricesMultiplication) {
        auto result = m1 * m2;

        EXPECT_FLOAT_EQ(result(0, 0), 4.0f);
        EXPECT_FLOAT_EQ(result(0, 1), 4.0f);
        EXPECT_FLOAT_EQ(result(1, 0), 4.0f);
        EXPECT_FLOAT_EQ(result(1, 1), 4.0f);
    }

    TEST_F(FloatMatrixMultiplicationTest, RectangularMatricesMultiplication) {
        auto result = m3 * m4;

        EXPECT_FLOAT_EQ(result(0, 0), 58.0f);
        EXPECT_FLOAT_EQ(result(0, 1), 64.0f);
        EXPECT_FLOAT_EQ(result(1, 0), 139.0f);
        EXPECT_FLOAT_EQ(result(1, 1), 154.0f);
    }

    TEST_F(FloatMatrixMultiplicationTest, RvalueLeftMultiplication) {
        Matrix<float> temp = m1;
        auto result = std::move(temp) * m2;

        EXPECT_FLOAT_EQ(result(0, 0), 4.0f);
        EXPECT_EQ(temp.get_rows(), 0);
    }

    TEST_F(FloatMatrixMultiplicationTest, RvalueRightMultiplication) {
        Matrix<float> temp = m2;
        auto result = m1 * std::move(temp);

        EXPECT_FLOAT_EQ(result(0, 0), 4.0f);
        EXPECT_EQ(temp.get_rows(), 0);
    }

    TEST_F(FloatMatrixMultiplicationTest, TwoRvaluesMultiplication) {
        Matrix<float> temp1 = m1;
        Matrix<float> temp2 = m2;
        auto result = std::move(temp1) * std::move(temp2);

        EXPECT_FLOAT_EQ(result(0, 0), 4.0f);
        EXPECT_EQ(temp1.get_rows(), 0);
        EXPECT_EQ(temp2.get_rows(), 0);
    }

    TEST_F(FloatMatrixMultiplicationTest, ScalarMultiplicationRight) {
        auto result = m3 * 2.0f;

        EXPECT_FLOAT_EQ(result(0, 0), 2.0f);
        EXPECT_FLOAT_EQ(result(0, 1), 4.0f);
        EXPECT_FLOAT_EQ(result(1, 2), 12.0f);
    }

    TEST_F(FloatMatrixMultiplicationTest, ScalarMultiplicationLeft) {
        auto result = 2.0f * m3;

        EXPECT_FLOAT_EQ(result(0, 0), 2.0f);
        EXPECT_FLOAT_EQ(result(0, 1), 4.0f);
        EXPECT_FLOAT_EQ(result(1, 2), 12.0f);
    }

    TEST_F(FloatMatrixMultiplicationTest, EmptyMatrixMultiplication) {
        auto result = m1 * m_empty;

        EXPECT_FLOAT_EQ(result(0, 0), 0.0f);
        EXPECT_FLOAT_EQ(result(1, 1), 0.0f);
    }

    TEST_F(FloatMatrixMultiplicationTest, IncompatibleSizes) {
        Matrix<float> m_wrong_size(3, 2, 1.0f);
        EXPECT_THROW(m1 * m_wrong_size, std::invalid_argument);
    }
}