#include "pch.h"

#include "../MatrixLib/include/matrixlib/core/matrix.h"

namespace {
	using namespace Core;

    class MatrixUtilityFunctionsTest : public ::testing::Test {
    protected:
        void SetUp() override {
            m3x3 = Matrix<double>(3, 3);
            m2x3 = Matrix<double>(2, 3);
            m_filled = Matrix<double>(2, 2, 5.0);
        }

        Matrix<double> m3x3, m2x3, m_filled;
        const double epsilon = 1e-9;
    };

    TEST_F(MatrixUtilityFunctionsTest, IdentityMatrixSetsDiagonal) {
        m3x3.identity_matrix(1.0);

        EXPECT_NEAR(m3x3(0, 0), 1.0, epsilon);
        EXPECT_NEAR(m3x3(1, 1), 1.0, epsilon);
        EXPECT_NEAR(m3x3(2, 2), 1.0, epsilon);

        EXPECT_NEAR(m3x3(0, 1), 0.0, epsilon);
        EXPECT_NEAR(m3x3(1, 2), 0.0, epsilon);
    }

    TEST_F(MatrixUtilityFunctionsTest, IdentityMatrixThrowsForNonSquare) {
        EXPECT_THROW(m2x3.identity_matrix(1.0), std::invalid_argument);
    }

    TEST_F(MatrixUtilityFunctionsTest, FillSetsAllValues) {
        const double fill_value = 3.14;
        m3x3.fill(fill_value);

        for (size_t i = 0; i < m3x3.get_rows(); ++i) {
            for (size_t j = 0; j < m3x3.get_columns(); ++j) {
                EXPECT_NEAR(m3x3(i, j), fill_value, epsilon);
            }
        }
    }

    TEST_F(MatrixUtilityFunctionsTest, FillOverwritesExistingValues) {
        const double new_value = 2.0;
        m_filled.fill(new_value);

        for (size_t i = 0; i < m_filled.get_rows(); ++i) {
            for (size_t j = 0; j < m_filled.get_columns(); ++j) {
                EXPECT_NEAR(m_filled(i, j), new_value, epsilon);
            }
        }
    }

    TEST_F(MatrixUtilityFunctionsTest, IsSquareTrueForSquareMatrix) {
        EXPECT_TRUE(m3x3.is_square());
    }

    TEST_F(MatrixUtilityFunctionsTest, IsSquareFalseForRectangularMatrix) {
        EXPECT_FALSE(m2x3.is_square());
    }

    TEST_F(MatrixUtilityFunctionsTest, IsSquareTrueForEmptyMatrix) {
        Matrix<double> empty;
        EXPECT_TRUE(empty.is_square());
    }

    TEST_F(MatrixUtilityFunctionsTest, SwapRowsChangesRowOrder) {
        Matrix<double> m(2, 2);
        m(0, 0) = 1.0; m(0, 1) = 2.0;
        m(1, 0) = 3.0; m(1, 1) = 4.0;

        m.swap_rows(0, 1);

        EXPECT_NEAR(m(0, 0), 3.0, epsilon);
        EXPECT_NEAR(m(0, 1), 4.0, epsilon);
        EXPECT_NEAR(m(1, 0), 1.0, epsilon);
        EXPECT_NEAR(m(1, 1), 2.0, epsilon);
    }

    TEST_F(MatrixUtilityFunctionsTest, SwapRowsSameRowNoChange) {
        Matrix<double> original = m_filled;
        m_filled.swap_rows(0, 0);

        for (size_t i = 0; i < m_filled.get_rows(); ++i) {
            for (size_t j = 0; j < m_filled.get_columns(); ++j) {
                EXPECT_NEAR(m_filled(i, j), original(i, j), epsilon);
            }
        }
    }

    TEST_F(MatrixUtilityFunctionsTest, SwapRowsThrowsForInvalidIndices) {
        EXPECT_THROW(m3x3.swap_rows(0, 3), std::out_of_range);
        EXPECT_THROW(m3x3.swap_rows(3, 0), std::out_of_range);
        EXPECT_THROW(m3x3.swap_rows(3, 3), std::out_of_range);
    }
}