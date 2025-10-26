#include "matrix.h"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(MatrixTest, DefaultConstructor) {
    Matrix m;
    EXPECT_EQ(m.getRows(), 0);
    EXPECT_EQ(m.getCols(), 0);
}

TEST(MatrixTest, ParameterizedConstructor) {
    Matrix m(3, 4);
    EXPECT_EQ(m.getRows(), 3);
    EXPECT_EQ(m.getCols(), 4);
    
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            EXPECT_EQ(m[i][j], 0);
        }
    }
}

TEST(MatrixTest, ElementAccess) {
    Matrix m(2, 3);
    
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][2] = 5;
    
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[1][2], 5);
    
    const Matrix& cm = m;
    EXPECT_EQ(cm[0][0], 1);
    EXPECT_EQ(cm[1][2], 5);
}

TEST(MatrixTest, OutOfBoundsAccess) {
    Matrix m(2, 3);
    
    EXPECT_THROW(m[5][0], std::out_of_range);
    EXPECT_THROW(m[2][0], std::out_of_range);
    
    EXPECT_THROW(m[0][5], std::out_of_range);
    EXPECT_THROW(m[0][3], std::out_of_range);
    
    const Matrix& cm = m;
    EXPECT_THROW(cm[5][0], std::out_of_range);
    EXPECT_THROW(cm[0][5], std::out_of_range);
}

TEST(MatrixTest, CopyConstructor) {
    Matrix m1(2, 3);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][2] = 3;
    
    Matrix m2 = m1;
    
    EXPECT_EQ(m2.getRows(), 2);
    EXPECT_EQ(m2.getCols(), 3);
    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[0][1], 2);
    EXPECT_EQ(m2[1][2], 3);
    
    m2[0][0] = 10;
    EXPECT_EQ(m1[0][0], 1);
    EXPECT_EQ(m2[0][0], 10);
}

TEST(MatrixTest, MoveConstructor) {
    Matrix m1(2, 3);
    m1[0][0] = 1;
    m1[1][1] = 2;
    
    Matrix m2 = std::move(m1);
    
    EXPECT_EQ(m2.getRows(), 2);
    EXPECT_EQ(m2.getCols(), 3);
    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[1][1], 2);
    
    EXPECT_EQ(m1.getRows(), 0);
    EXPECT_EQ(m1.getCols(), 0);
}

TEST(MatrixTest, CopyAssignment) {
    Matrix m1(2, 3);
    m1[0][0] = 1;
    m1[1][2] = 5;
    
    Matrix m2(1, 1);
    m2 = m1;
    
    EXPECT_EQ(m2.getRows(), 2);
    EXPECT_EQ(m2.getCols(), 3);
    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[1][2], 5);
    
    m2[0][0] = 10;
    EXPECT_EQ(m1[0][0], 1);
}

TEST(MatrixTest, MoveAssignment) {
    Matrix m1(2, 3);
    m1[0][0] = 1;
    m1[1][1] = 2;
    
    Matrix m2;
    m2 = std::move(m1);
    
    EXPECT_EQ(m2.getRows(), 2);
    EXPECT_EQ(m2.getCols(), 3);
    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[1][1], 2);
    
    EXPECT_EQ(m1.getRows(), 0);
    EXPECT_EQ(m1.getCols(), 0);
}

TEST(MatrixTest, SelfAssignment) {
    Matrix m(2, 3);
    m[0][0] = 1;
    m[1][1] = 2;
    
    m = m;
    
    EXPECT_EQ(m.getRows(), 2);
    EXPECT_EQ(m.getCols(), 3);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][1], 2);
    
    m = std::move(m);
    
    EXPECT_EQ(m.getRows(), 2);
    EXPECT_EQ(m.getCols(), 3);
    EXPECT_EQ(m[0][0], 1);
}

TEST(MatrixTest, ScalarMultiplication) {
    Matrix m(2, 2);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;
    
    m *= 3;
    
    EXPECT_EQ(m[0][0], 3);
    EXPECT_EQ(m[0][1], 6);
    EXPECT_EQ(m[1][0], 9);
    EXPECT_EQ(m[1][1], 12);
}

TEST(MatrixTest, MatrixAddition) {
    Matrix m1(2, 2);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;
    
    Matrix m2(2, 2);
    m2[0][0] = 5;
    m2[0][1] = 6;
    m2[1][0] = 7;
    m2[1][1] = 8;
    
    Matrix result = m1 + m2;
    
    EXPECT_EQ(result.getRows(), 2);
    EXPECT_EQ(result.getCols(), 2);
    EXPECT_EQ(result[0][0], 6);
    EXPECT_EQ(result[0][1], 8);
    EXPECT_EQ(result[1][0], 10);
    EXPECT_EQ(result[1][1], 12);
}

TEST(MatrixTest, AdditionWithDifferentDimensions) {
    Matrix m1(2, 3);
    Matrix m2(3, 2);
    
    EXPECT_THROW(m1 + m2, std::invalid_argument);
}

TEST(MatrixTest, EqualityOperator) {
    Matrix m1(2, 2);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;
    
    Matrix m2(2, 2);
    m2[0][0] = 1;
    m2[0][1] = 2;
    m2[1][0] = 3;
    m2[1][1] = 4;
    
    Matrix m3(2, 2);
    m3[0][0] = 1;
    m3[0][1] = 2;
    m3[1][0] = 3;
    m3[1][1] = 5;
    
    Matrix m4(3, 2);
    
    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 == m3);
    EXPECT_FALSE(m1 == m4);
}

TEST(MatrixTest, InequalityOperator) {
    Matrix m1(2, 2);
    Matrix m2(2, 2);
    Matrix m3(3, 2);
    
    EXPECT_FALSE(m1 != m2);
    EXPECT_TRUE(m1 != m3);
}

TEST(MatrixTest, OutputStream) {
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    
    std::ostringstream oss;
    oss << m;
    
    std::string expected = "1 2 3 \n4 5 6 \n";
    EXPECT_EQ(oss.str(), expected);
}

TEST(MatrixTest, ZeroSizeMatrix) {
    Matrix m(0, 0);
    EXPECT_EQ(m.getRows(), 0);
    EXPECT_EQ(m.getCols(), 0);
    
    EXPECT_NO_THROW(Matrix(0, 0));
}

TEST(MatrixTest, LargeMatrix) {
    const size_t rows = 100;
    const size_t cols = 100;
    Matrix m(rows, cols);
    
    EXPECT_EQ(m.getRows(), rows);
    EXPECT_EQ(m.getCols(), cols);
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            m[i][j] = static_cast<int32_t>(i * cols + j);
        }
    }
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            EXPECT_EQ(m[i][j], static_cast<int32_t>(i * cols + j));
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}