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

TEST(HomographyMatrix,TestHomographyMatrixEstimation) {
    Eigen::Matrix<float,3,3>  homography       = Eigen::Matrix<float,3,3>::Random();
    Eigen::Matrix<float,2,4> reference_matrix  = Eigen::Matrix<float,2,4>::Random();
    auto                      detected_matrix  = (homography * reference_matrix.colwise().homogeneous()).colwise().hnormalized();
    improc::PixelMatrix<float> reference_pixels {reference_matrix};
    improc::PixelMatrix<float> detected_pixels  {detected_matrix };
    improc::HomographyMatrix<float> homography_matrix {detected_pixels, reference_pixels};
    homography /= homography(2,2);
    homography_matrix /= homography_matrix(2,2);
    EXPECT_NEAR(homography(0,0),homography_matrix(0,0), 1e-5);
    EXPECT_NEAR(homography(0,1),homography_matrix(0,1), 1e-5);
    EXPECT_NEAR(homography(0,2),homography_matrix(0,2), 1e-5);
    EXPECT_NEAR(homography(1,0),homography_matrix(1,0), 1e-5);
    EXPECT_NEAR(homography(1,1),homography_matrix(1,1), 1e-5);
    EXPECT_NEAR(homography(1,2),homography_matrix(1,2), 1e-5);
    EXPECT_NEAR(homography(2,0),homography_matrix(2,0), 1e-5);
    EXPECT_NEAR(homography(2,1),homography_matrix(2,1), 1e-5);
    EXPECT_NEAR(homography(2,2),homography_matrix(2,2), 1e-5);
}

TEST(HomographyMatrix,TestInvalidNumberPoints) {
    Eigen::Matrix<float,3,3> homography       = Eigen::Matrix<float,3,3>::Random();
    Eigen::Matrix<float,2,3> reference_matrix = Eigen::Matrix<float,2,3>::Random();
    auto                     detected_matrix  = (homography * reference_matrix.colwise().homogeneous()).colwise().hnormalized();
    improc::PixelMatrix<float> reference_pixels {reference_matrix};
    improc::PixelMatrix<float> detected_pixels  {detected_matrix };
    EXPECT_THROW(improc::HomographyMatrix<float>(detected_pixels, reference_pixels),improc::invalid_homography_estimation);
}

TEST(HomographyMatrix,TestInconsistentNumberPoints) {
    Eigen::Matrix<float,3,3> homography       = Eigen::Matrix<float,3,3>::Random();
    Eigen::Matrix<float,2,4> reference_matrix = Eigen::Matrix<float,2,4>::Random();
    Eigen::Matrix<float,2,5> detected_matrix  = Eigen::Matrix<float,2,5>::Random();
    improc::PixelMatrix<float> reference_pixels {reference_matrix};
    improc::PixelMatrix<float> detected_pixels  {detected_matrix };
    EXPECT_THROW(improc::HomographyMatrix<float>(detected_pixels, reference_pixels),improc::inconsistent_size_detected_reference_pixels);
}

TEST(HomographyMatrix,TestCollinearPoints) {
    Eigen::Matrix<float,2,4> reference_matrix {};
    Eigen::Matrix<float,2,4> detected_matrix  {};
    reference_matrix.setOnes();
    detected_matrix.setOnes();
    improc::PixelMatrix<float> reference_pixels {reference_matrix};
    improc::PixelMatrix<float> detected_pixels  {detected_matrix };
    EXPECT_THROW(improc::HomographyMatrix<float>(detected_pixels, reference_pixels),improc::invalid_svd_decomposition);
}
