#include <gtest/gtest.h>

#include <improc/calib/line_matrix.hpp>

TEST(LineMatrix,TestEmptyLineMatrixConstructor) {
    improc::LineMatrix<float,2> line_matrix {};
    EXPECT_EQ(line_matrix.rows(),3);
    EXPECT_EQ(line_matrix.cols(),2);
    EXPECT_EQ(line_matrix.Number(),2);
}

TEST(LineMatrix,TestConstructorFromEigenMatrix) {
    Eigen::Matrix<float,3,2> matrix {};
    matrix.setOnes();
    improc::LineMatrix<float,2> line_matrix {matrix};
    EXPECT_EQ(line_matrix,matrix);
    EXPECT_EQ(line_matrix(1,1),1.0);
}

TEST(LineMatrix,TestConstructorFromEigenMatrixExpression) {
    improc::LineMatrix<float,2> line_matrix {Eigen::Matrix<float,3,2>::Zero()};
    EXPECT_EQ(line_matrix(1,1),0.0);
}

TEST(LineMatrix,TestAssignmentFromEigenMatrix) {
    Eigen::Matrix<float,3,2> matrix {};
    matrix.setOnes();
    improc::LineMatrix<float,2> line_matrix {};
    line_matrix = matrix;
    EXPECT_EQ(line_matrix,matrix);
    EXPECT_EQ(line_matrix(1,1),1.0);
}

TEST(LineMatrix,TestAssignmentFromEigenMatrixExpression) {
    improc::LineMatrix<float,2> line_matrix {};
    line_matrix = Eigen::Matrix<float,3,2>::Zero();
    EXPECT_EQ(line_matrix(1,1),0.0);
}

TEST(LineMatrix,TestA) {
    improc::LineMatrix<float,2> line_matrix {};
    line_matrix << 1,2,3,4,5,6;
    EXPECT_EQ(line_matrix.a()(0),1.0);
    EXPECT_EQ(line_matrix.a()(1),2.0);
    line_matrix.a()(0) = 10.0;
    EXPECT_EQ(line_matrix.a()(0),10.0);
}

TEST(LineMatrix,TestB) {
    improc::LineMatrix<float,2> line_matrix {};
    line_matrix << 1,2,3,4,5,6;
    EXPECT_EQ(line_matrix.b()(0),3.0);
    EXPECT_EQ(line_matrix.b()(1),4.0);
    line_matrix.b()(0) = 10.0;
    EXPECT_EQ(line_matrix.b()(0),10.0);
}

TEST(LineMatrix,TestC) {
    improc::LineMatrix<float,2> line_matrix {};
    line_matrix << 1,2,3,4,5,6;
    EXPECT_EQ(line_matrix.c()(0),5.0);
    EXPECT_EQ(line_matrix.c()(1),6.0);
    line_matrix.c()(0) = 10.0;
    EXPECT_EQ(line_matrix.c()(0),10.0);
}
