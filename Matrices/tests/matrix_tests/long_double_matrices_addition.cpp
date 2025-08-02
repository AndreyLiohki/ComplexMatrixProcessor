#include <gtest/gtest.h>

#include "../include/matrixlib/core/matrix.h"


namespace {

    using namespace Core;

    const long double epsilon = 1e-12L;

    class LongDoubleMatrixAdditionTest : public ::testing::Test {
    protected:
        void SetUp() override {
            m1 = Matrix<long double>(2, 2, 1.0);
            m2 = Matrix<long double>(2, 2, 2.0);
            m_empty = Matrix<long double>(2, 2);
            m_non_uniform = Matrix<long double>(2, 2);

            m_non_uniform(0, 0) = 1.0; m_non_uniform(0, 1) = 2.0;
            m_non_uniform(1, 0) = 3.0; m_non_uniform(1, 1) = 4.0;
        }

        Matrix<long double> m1, m2, m_empty, m_non_uniform;
    };

    TEST_F(LongDoubleMatrixAdditionTest, BasicAddition) {
        auto result = m1 + m2;

        EXPECT_NEAR(result(0, 0), 3.0, epsilon);
        EXPECT_NEAR(result(0, 1), 3.0, epsilon);
        EXPECT_NEAR(result(1, 0), 3.0, epsilon);
        EXPECT_NEAR(result(1, 1), 3.0, epsilon);
    }

    TEST_F(LongDoubleMatrixAdditionTest, RvalueLeftAddition) {
        Matrix<long double> temp = m1;
        auto result = std::move(temp) + m2;

        EXPECT_NEAR(result(0, 0), 3.0, epsilon);
        EXPECT_EQ(temp.get_rows(), 0);
    }

    TEST_F(LongDoubleMatrixAdditionTest, RvalueRightAddition) {
        Matrix<long double> temp = m2;
        auto result = m1 + std::move(temp);

        EXPECT_NEAR(result(0, 0), 3.0, epsilon);
        EXPECT_EQ(temp.get_rows(), 0);
    }

    TEST_F(LongDoubleMatrixAdditionTest, TwoRvaluesAddition) {
        Matrix<long double> temp1 = m1;
        Matrix<long double> temp2 = m2;
        auto result = std::move(temp1) + std::move(temp2);

        EXPECT_NEAR(result(0, 0), 3.0, epsilon);
        EXPECT_EQ(temp1.get_rows(), 0);
        EXPECT_EQ(temp2.get_rows(), 0);
    }

    TEST_F(LongDoubleMatrixAdditionTest, PlusEqualsOperator) {
        m1 += m2;

        EXPECT_NEAR(m1(0, 0), 3.0, epsilon);
        EXPECT_NEAR(m1(1, 1), 3.0, epsilon);
    }

    TEST_F(LongDoubleMatrixAdditionTest, EmptyMatrixAddition) {
        auto result = m1 + m_empty;

        EXPECT_NEAR(result(0, 0), 1.0, epsilon);
        EXPECT_NEAR(result(1, 1), 1.0, epsilon);
    }

    TEST_F(LongDoubleMatrixAdditionTest, NonUniformAddition) {
        auto result = m_non_uniform + m2;

        EXPECT_NEAR(result(0, 0), 3.0, epsilon);
        EXPECT_NEAR(result(0, 1), 4.0, epsilon);
        EXPECT_NEAR(result(1, 0), 5.0, epsilon);
        EXPECT_NEAR(result(1, 1), 6.0, epsilon);
    }

    TEST_F(LongDoubleMatrixAdditionTest, IncompatibleSizes) {
        Matrix<long double> m_wrong_size(3, 2, 1.0);
        EXPECT_THROW(m1 + m_wrong_size, std::invalid_argument);
    }
}