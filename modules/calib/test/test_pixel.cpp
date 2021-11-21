#include <gtest/gtest.h>

#include <improc/calib/pixel_matrix.hpp>

TEST(PixelMatrix,TestEmptyPixelMatrixConstructor) {
    improc::PixelMatrix<float,3> pixel_matrix {};
    EXPECT_EQ(pixel_matrix.rows(),2);
    EXPECT_EQ(pixel_matrix.cols(),3);
}

TEST(PixelMatrix,TestConstructorFromEigenMatrix) {
    Eigen::Matrix<float,2,3> matrix {};
    matrix.setOnes();
    improc::PixelMatrix<float,3> pixel_matrix {matrix};
    EXPECT_EQ(pixel_matrix,matrix);
    EXPECT_EQ(pixel_matrix(1,1),1.0);
}

TEST(PixelMatrix,TestConstructorFromEigenMatrixExpression) {
    improc::PixelMatrix<float,3> pixel_matrix {Eigen::Matrix<float,2,3>::Zero()};
    EXPECT_EQ(pixel_matrix(1,1),0.0);
}

TEST(PixelMatrix,TestAssignmentFromEigenMatrix) {
    Eigen::Matrix<float,2,3> matrix {};
    matrix.setOnes();
    improc::PixelMatrix<float,3> pixel_matrix {};
    pixel_matrix = matrix;
    EXPECT_EQ(pixel_matrix,matrix);
    EXPECT_EQ(pixel_matrix(1,1),1.0);
}

TEST(PixelMatrix,TestAssignmentFromEigenMatrixExpression) {
    improc::PixelMatrix<float,3> pixel_matrix {};
    pixel_matrix = Eigen::Matrix<float,2,3>::Zero();
    EXPECT_EQ(pixel_matrix(1,1),0.0);
}

TEST(PixelMatrix,TestU) {
    improc::PixelMatrix<float,3> pixel_matrix {};
    pixel_matrix << 1,2,3,4,5,6;
    EXPECT_EQ(pixel_matrix.u()(0),1.0);
    EXPECT_EQ(pixel_matrix.u()(1),2.0);
    EXPECT_EQ(pixel_matrix.u()(2),3.0);
    pixel_matrix.u()(0) = 10.0;
    EXPECT_EQ(pixel_matrix.u()(0),10.0);
}

TEST(PixelMatrix,TestV) {
    improc::PixelMatrix<float,3> pixel_matrix {};
    pixel_matrix << 1,2,3,4,5,6;
    EXPECT_EQ(pixel_matrix.v()(0),4.0);
    EXPECT_EQ(pixel_matrix.v()(1),5.0);
    EXPECT_EQ(pixel_matrix.v()(2),6.0);
    pixel_matrix.v()(0) = 10.0;
    EXPECT_EQ(pixel_matrix.v()(0),10.0);
}

TEST(PixelMatrix,TestNormalize) {
    improc::PixelMatrix<float,4> pixel_matrix {};
    pixel_matrix << 1,2,3,4,5,6,7,8;
    pixel_matrix.Normalize();
    EXPECT_NEAR(pixel_matrix.mean(),0.0,1e-5);
    EXPECT_NEAR(pixel_matrix.colwise().squaredNorm().mean(),2.0,1e-5);
}
