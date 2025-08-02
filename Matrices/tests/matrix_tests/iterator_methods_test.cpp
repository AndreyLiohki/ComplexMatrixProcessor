#include <gtest/gtest.h>

#include"../include/matrixlib/core/matrix.h"

namespace {

	using namespace Core;

    class MatrixIteratorTest : public ::testing::Test {
    protected:
        void SetUp() override {
            m = Matrix<double>(2, 2);
            m(0, 0) = 1; m(0, 1) = 2;
            m(1, 0) = 3; m(1, 1) = 4;
        }

        Matrix<double> m;
    };

    TEST_F(MatrixIteratorTest, BeginPointsToFirstElement) {
        auto it = m.begin();
        EXPECT_EQ(*it, std::vector<double>({ 1, 2 }));
    }

    TEST_F(MatrixIteratorTest, EndPointsOnePastLast) {
        auto it = m.end();
        auto begin_it = m.begin();
        EXPECT_EQ(std::distance(begin_it, it), 2);
    }

    TEST_F(MatrixIteratorTest, IterationWorksCorrectly) {
        std::vector<std::vector<double>> expected = { {1, 2}, {3, 4} };
        size_t i = 0;

        for (auto it = m.begin(); it != m.end(); ++it, ++i) {
            EXPECT_EQ(*it, expected[i]);
        }
    }

    TEST_F(MatrixIteratorTest, RangeBasedForWorks) {
        std::vector<std::vector<double>> expected = { {1, 2}, {3, 4} };
        size_t i = 0;

        for (const auto& row : m) {
            EXPECT_EQ(row, expected[i++]);
        }
    }

    TEST_F(MatrixIteratorTest, CanModifyThroughIterator) {
        for (auto& row : m) {
            for (auto& elem : row) {
                elem += 10;
            }
        }

        EXPECT_EQ(m(0, 0), 11);
        EXPECT_EQ(m(1, 1), 14);
    }

    TEST_F(MatrixIteratorTest, CBeginPointsToFirstElement) {
        const auto& cm = m;
        auto it = cm.cbegin();
        EXPECT_EQ(*it, std::vector<double>({ 1, 2 }));
    }

    TEST_F(MatrixIteratorTest, CEndPointsOnePastLast) {
        const auto& cm = m;
        auto it = cm.cend();
        auto begin_it = cm.cbegin();
        EXPECT_EQ(std::distance(begin_it, it), 2);
    }

    TEST_F(MatrixIteratorTest, ConstIterationWorks) {
        const auto& cm = m;
        std::vector<std::vector<double>> expected = { {1, 2}, {3, 4} };
        size_t i = 0;

        for (auto it = cm.begin(); it != cm.end(); ++it, ++i) {
            EXPECT_EQ(*it, expected[i]);
        }
    }

    TEST_F(MatrixIteratorTest, WorksWithSTLFind) {
        std::vector<double> target_row = { 3, 4 };
        auto it = std::find(m.begin(), m.end(), target_row);
        ASSERT_NE(it, m.end());
        EXPECT_EQ(*it, target_row);
    }

    TEST_F(MatrixIteratorTest, WorksWithSTLTransform) {
        std::vector<std::vector<double>> expected = { {2, 3}, {4, 5} };

        std::transform(m.begin(), m.end(), m.begin(),
            [](std::vector<double> row) {
                for (auto& x : row) x += 1;
                return row;
            });

        for (size_t i = 0; i < m.get_rows(); ++i) {
            for (size_t j = 0; j < m.get_columns(); ++j) {
                EXPECT_EQ(m(i, j), expected[i][j]);
            }
        }
    }

    TEST_F(MatrixIteratorTest, EmptyMatrixBeginEqualsEnd) {
        Matrix<double> empty;
        EXPECT_EQ(empty.begin(), empty.end());
        EXPECT_EQ(empty.cbegin(), empty.cend());
    }
}