#include "pch.h"

#include "../MatrixLib/include/matrixlib/core/matrix.h"


namespace {

    using namespace Core;

    class DoubleMatrixSubstractionTest : public ::testing::Test {
    protected:
        void SetUp() override {
            m1 = Matrix<double>(2, 2, 1.0);
            m2 = Matrix<double>(2, 2, 2.0);
            m_empty = Matrix<double>(2, 2);
            m_non_uniform = Matrix<double>(2, 2);

            m_non_uniform(0, 0) = 1.0; m_non_uniform(0, 1) = 2.0;
            m_non_uniform(1, 0) = 3.0; m_non_uniform(1, 1) = 4.0;
        }

        Matrix<double> m1, m2, m_empty, m_non_uniform;
    };

    TEST_F(DoubleMatrixSubstractionTest, BasicAddition) {
        auto result = m1 - m2;

        EXPECT_FLOAT_EQ(result(0, 0), -1.0);
        EXPECT_FLOAT_EQ(result(0, 1), -1.0);
        EXPECT_FLOAT_EQ(result(1, 0), -1.0);
        EXPECT_FLOAT_EQ(result(1, 1), -1.0);
    }

    TEST_F(DoubleMatrixSubstractionTest, RvalueLeftAddition) {
        Matrix<double> temp = m1;
        auto result = std::move(temp) - m2;

        EXPECT_FLOAT_EQ(result(0, 0), -1.0);
        EXPECT_EQ(temp.get_rows(), 0);
    }

    TEST_F(DoubleMatrixSubstractionTest, RvalueRightAddition) {
        Matrix<double> temp = m2;
        auto result = m1 - std::move(temp);

        EXPECT_FLOAT_EQ(result(0, 0), -1.0);
        EXPECT_EQ(temp.get_rows(), 0);
    }

    TEST_F(DoubleMatrixSubstractionTest, TwoRvaluesAddition) {
        Matrix<double> temp1 = m1;
        Matrix<double> temp2 = m2;
        auto result = std::move(temp1) - std::move(temp2);

        EXPECT_FLOAT_EQ(result(0, 0), -1.0);
        EXPECT_EQ(temp1.get_rows(), 0);
        EXPECT_EQ(temp2.get_rows(), 0);
    }

    TEST_F(DoubleMatrixSubstractionTest, PlusEqualsOperator) {
        m1 -= m2;

        EXPECT_FLOAT_EQ(m1(0, 0), -1.0);
        EXPECT_FLOAT_EQ(m1(1, 1), -1.0);
    }

    TEST_F(DoubleMatrixSubstractionTest, EmptyMatrixAddition) {
        auto result = m1 - m_empty;

        EXPECT_FLOAT_EQ(result(0, 0), 1.0);
        EXPECT_FLOAT_EQ(result(1, 1), 1.0);
    }

    TEST_F(DoubleMatrixSubstractionTest, NonUniformAddition) {
        auto result = m_non_uniform - m1;

        EXPECT_FLOAT_EQ(result(0, 0), 0.0);
        EXPECT_FLOAT_EQ(result(0, 1), 1.0);
        EXPECT_FLOAT_EQ(result(1, 0), 2.0);
        EXPECT_FLOAT_EQ(result(1, 1), 3.0);
    }

    TEST_F(DoubleMatrixSubstractionTest, IncompatibleSizes) {
        Matrix<double> m_wrong_size(3, 2, 1.0);
        EXPECT_THROW(m1 + m_wrong_size, std::invalid_argument);
    }
}