#include "pch.h"

#include "../MatrixLib/include/matrixlib/core/matrix.h"


namespace {

    using namespace Core;

    class DoubleMatrixAdditionTest : public ::testing::Test {
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

    TEST_F(DoubleMatrixAdditionTest, BasicAddition) {
        auto result = m1 + m2;

        EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
        EXPECT_DOUBLE_EQ(result(0, 1), 3.0);
        EXPECT_DOUBLE_EQ(result(1, 0), 3.0);
        EXPECT_DOUBLE_EQ(result(1, 1), 3.0);
    }

    TEST_F(DoubleMatrixAdditionTest, RvalueLeftAddition) {
        Matrix<double> temp = m1;
        auto result = std::move(temp) + m2;

        EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
        EXPECT_EQ(temp.get_rows(), 0);
    }

    TEST_F(DoubleMatrixAdditionTest, RvalueRightAddition) {
        Matrix<double> temp = m2;
        auto result = m1 + std::move(temp);

        EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
        EXPECT_EQ(temp.get_rows(), 0);
    }

    TEST_F(DoubleMatrixAdditionTest, TwoRvaluesAddition) {
        Matrix<double> temp1 = m1;
        Matrix<double> temp2 = m2;
        auto result = std::move(temp1) + std::move(temp2);

        EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
        EXPECT_EQ(temp1.get_rows(), 0);
        EXPECT_EQ(temp2.get_rows(), 0);
    }

    TEST_F(DoubleMatrixAdditionTest, PlusEqualsOperator) {
        m1 += m2;

        EXPECT_DOUBLE_EQ(m1(0, 0), 3.0);
        EXPECT_DOUBLE_EQ(m1(1, 1), 3.0);
    }

    TEST_F(DoubleMatrixAdditionTest, EmptyMatrixAddition) {
        auto result = m1 + m_empty;

        EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
        EXPECT_DOUBLE_EQ(result(1, 1), 1.0);
    }

    TEST_F(DoubleMatrixAdditionTest, NonUniformAddition) {
        auto result = m_non_uniform + m2;

        EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
        EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
        EXPECT_DOUBLE_EQ(result(1, 0), 5.0);
        EXPECT_DOUBLE_EQ(result(1, 1), 6.0);
    }

    TEST_F(DoubleMatrixAdditionTest, IncompatibleSizes) {
        Matrix<double> m_wrong_size(3, 2, 1.0);
        EXPECT_THROW(m1 + m_wrong_size, std::invalid_argument);
    }
}