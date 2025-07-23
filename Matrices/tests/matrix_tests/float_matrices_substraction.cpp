#include "pch.h"

#include "../MatrixLib/include/matrixlib/core/matrix.h"


namespace {

    using namespace Core;

    class FloatMatrixSubstractionTest : public ::testing::Test {
    protected:
        void SetUp() override {
            m1 = Matrix<float>(2, 2, 1.0f);
            m2 = Matrix<float>(2, 2, 2.0f);
            m_empty = Matrix<float>(2, 2);
            m_non_uniform = Matrix<float>(2, 2);

            m_non_uniform(0, 0) = 1.0f; m_non_uniform(0, 1) = 2.0f;
            m_non_uniform(1, 0) = 3.0f; m_non_uniform(1, 1) = 4.0f;
        }

        Matrix<float> m1, m2, m_empty, m_non_uniform;
    };

    TEST_F(FloatMatrixSubstractionTest, BasicAddition) {
        auto result = m1 - m2;

        EXPECT_FLOAT_EQ(result(0, 0), -1.0f);
        EXPECT_FLOAT_EQ(result(0, 1), -1.0f);
        EXPECT_FLOAT_EQ(result(1, 0), -1.0f);
        EXPECT_FLOAT_EQ(result(1, 1), -1.0f);
    }

    TEST_F(FloatMatrixSubstractionTest, RvalueLeftAddition) {
        Matrix<float> temp = m1;
        auto result = std::move(temp) - m2;

        EXPECT_FLOAT_EQ(result(0, 0), -1.0f);
        EXPECT_EQ(temp.get_rows(), 0);
    }

    TEST_F(FloatMatrixSubstractionTest, RvalueRightAddition) {
        Matrix<float> temp = m2;
        auto result = m1 - std::move(temp);

        EXPECT_FLOAT_EQ(result(0, 0), -1.0f);
        EXPECT_EQ(temp.get_rows(), 0);
    }

    TEST_F(FloatMatrixSubstractionTest, TwoRvaluesAddition) {
        Matrix<float> temp1 = m1;
        Matrix<float> temp2 = m2;
        auto result = std::move(temp1) - std::move(temp2);

        EXPECT_FLOAT_EQ(result(0, 0), -1.0f);
        EXPECT_EQ(temp1.get_rows(), 0);
        EXPECT_EQ(temp2.get_rows(), 0);
    }

    TEST_F(FloatMatrixSubstractionTest, PlusEqualsOperator) {
        m1 -= m2;

        EXPECT_FLOAT_EQ(m1(0, 0), -1.0f);
        EXPECT_FLOAT_EQ(m1(1, 1), -1.0f);
    }

    TEST_F(FloatMatrixSubstractionTest, EmptyMatrixAddition) {
        auto result = m1 - m_empty;

        EXPECT_FLOAT_EQ(result(0, 0), 1.0f);
        EXPECT_FLOAT_EQ(result(1, 1), 1.0f);
    }

    TEST_F(FloatMatrixSubstractionTest, NonUniformAddition) {
        auto result = m_non_uniform - m1;

        EXPECT_FLOAT_EQ(result(0, 0), 0.0f);
        EXPECT_FLOAT_EQ(result(0, 1), 1.0f);
        EXPECT_FLOAT_EQ(result(1, 0), 2.0f);
        EXPECT_FLOAT_EQ(result(1, 1), 3.0f);
    }

    TEST_F(FloatMatrixSubstractionTest, IncompatibleSizes) {
        Matrix<float> m_wrong_size(3, 2, 1.0f);
        EXPECT_THROW(m1 + m_wrong_size, std::invalid_argument);
    }
}