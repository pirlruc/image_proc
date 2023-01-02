#include <gtest/gtest.h>

#include <improc/calib/point_matrix.hpp>

TEST(PointMatrix,TestEmptyPointMatrixConstructor) {
    improc::PointMatrix<float,2> point_matrix {};
    EXPECT_EQ(point_matrix.rows(),3);
    EXPECT_EQ(point_matrix.cols(),2);
    EXPECT_EQ(point_matrix.Number(),2);
}

TEST(PointMatrix,TestConstructorFromEigenMatrix) {
    Eigen::Matrix<float,3,2> matrix {};
    matrix.setOnes();
    improc::PointMatrix<float,2> point_matrix {matrix};
    EXPECT_EQ(point_matrix,matrix);
    EXPECT_EQ(point_matrix(1,1),1.0);
}

TEST(PointMatrix,TestConstructorFromEigenMatrixExpression) {
    improc::PointMatrix<float,2> point_matrix {Eigen::Matrix<float,3,2>::Zero()};
    EXPECT_EQ(point_matrix(1,1),0.0);
}

TEST(PointMatrix,TestAssignmentFromEigenMatrix) {
    Eigen::Matrix<float,3,2> matrix {};
    matrix.setOnes();
    improc::PointMatrix<float,2> point_matrix {};
    point_matrix = matrix;
    EXPECT_EQ(point_matrix,matrix);
    EXPECT_EQ(point_matrix(1,1),1.0);
}

TEST(PointMatrix,TestAssignmentFromEigenMatrixExpression) {
    improc::PointMatrix<float,2> point_matrix {};
    point_matrix = Eigen::Matrix<float,3,2>::Zero();
    EXPECT_EQ(point_matrix(1,1),0.0);
}

TEST(PointMatrix,TestX) {
    improc::PointMatrix<float,2> point_matrix {};
    point_matrix << 1,2,3,4,5,6;
    EXPECT_EQ(point_matrix.x()(0),1.0);
    EXPECT_EQ(point_matrix.x()(1),2.0);
    point_matrix.x()(0) = 10.0;
    EXPECT_EQ(point_matrix.x()(0),10.0);
}

TEST(PointMatrix,TestY) {
    improc::PointMatrix<float,2> point_matrix {};
    point_matrix << 1,2,3,4,5,6;
    EXPECT_EQ(point_matrix.y()(0),3.0);
    EXPECT_EQ(point_matrix.y()(1),4.0);
    point_matrix.y()(0) = 10.0;
    EXPECT_EQ(point_matrix.y()(0),10.0);
}

TEST(PointMatrix,TestZ) {
    improc::PointMatrix<float,2> point_matrix {};
    point_matrix << 1,2,3,4,5,6;
    EXPECT_EQ(point_matrix.z()(0),5.0);
    EXPECT_EQ(point_matrix.z()(1),6.0);
    point_matrix.z()(0) = 10.0;
    EXPECT_EQ(point_matrix.z()(0),10.0);
}

TEST(PointMatrix,TestGetNormalizationMatrix) {
    improc::PointMatrix<float,4> point_matrix {};
    point_matrix << 1,2,3,4,5,6,7,8,9,10,11,12;
    auto norm_matrix = point_matrix.GetNormalizationMatrix();
    EXPECT_NEAR(norm_matrix(0,0),0.894427, 1e-5);
    EXPECT_NEAR(norm_matrix(1,1),0.894427, 1e-5);
    EXPECT_NEAR(norm_matrix(2,2),0.894427, 1e-5);
    EXPECT_NEAR(norm_matrix(0,3),-2.23607, 1e-5);
    EXPECT_NEAR(norm_matrix(1,3),-5.81378, 1e-5);
    EXPECT_NEAR(norm_matrix(2,3),-9.39149, 1e-5);
    EXPECT_EQ(norm_matrix(3,3),1.0);
}

TEST(PointMatrix,TestNormalize) {
    improc::PointMatrix<float,4> point_matrix {};
    point_matrix << 1,2,3,4,5,6,7,8,9,10,11,12;
    point_matrix.Normalize();
    EXPECT_NEAR(point_matrix.mean(),0.0,1e-5);
    EXPECT_NEAR(point_matrix.colwise().squaredNorm().mean(),3.0,1e-5);
}
