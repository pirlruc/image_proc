#include <gtest/gtest.h>

#include <improc/calib/homography_matrix.hpp>

TEST(HomographyMatrix,TestEmptyPixelMatrixConstructor) {
    improc::HomographyMatrix<float> matrix {};
    EXPECT_EQ(matrix.rows(),3);
    EXPECT_EQ(matrix.cols(),3);
}

TEST(HomographyMatrix,TestConstructorFromEigenMatrix) {
    Eigen::Matrix<float,3,3> matrix {};
    matrix.setOnes();
    improc::HomographyMatrix<float> homography_matrix {matrix};
    EXPECT_EQ(homography_matrix,matrix);
    EXPECT_EQ(homography_matrix(1,1),1.0);
}

TEST(HomographyMatrix,TestConstructorFromEigenMatrixExpression) {
    improc::HomographyMatrix<float> matrix {Eigen::Matrix<float,3,3>::Zero()};
    EXPECT_EQ(matrix(1,1),0.0);
}

TEST(HomographyMatrix,TestAssignmentFromEigenMatrix) {
    Eigen::Matrix<float,3,3> matrix {};
    matrix.setOnes();
    improc::HomographyMatrix<float> homography_matrix {};
    homography_matrix = matrix;
    EXPECT_EQ(homography_matrix,matrix);
    EXPECT_EQ(homography_matrix(1,1),1.0);
}

TEST(HomographyMatrix,TestAssignmentFromEigenMatrixExpression) {
    improc::HomographyMatrix<float> matrix {};
    matrix = Eigen::Matrix<float,3,3>::Zero();
    EXPECT_EQ(matrix(1,1),0.0);
}
