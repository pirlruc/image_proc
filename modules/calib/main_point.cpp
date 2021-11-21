// #include <improc/calib/vector_matrix.hpp>
#include <improc/calib/point_matrix.hpp>
#include <iostream>

int main()
{
    improc::PointMatrix<int,2> points {};
    points = Eigen::Matrix<int,3,2>::Zero();
    improc::PointMatrix<int,2>::RowVectorXpr x = points.x();
    x(0) = 1;
    std::cout << x << std::endl;
    std::cout << points.x() << std::endl;
    points.x()(0) = 2;
    points.x()(1) = 3;
    std::cout << points.x() << std::endl;

    Eigen::Matrix<float,3,4> point_matrix {};
    point_matrix(0,0) = 1;
    point_matrix(0,1) = 2;
    point_matrix(0,2) = 3;
    point_matrix(0,3) = 4;
    point_matrix(1,0) = 5;
    point_matrix(1,1) = 6;
    point_matrix(1,2) = 7;
    point_matrix(1,3) = 8;
    point_matrix(2,0) = 9;
    point_matrix(2,1) = 10;
    point_matrix(2,2) = 11;
    point_matrix(2,3) = 12;
    std::cout << point_matrix << std::endl;
    std::cout << point_matrix.colwise().homogeneous() << std::endl;

    float scale = std::sqrt(3.0) 
                / std::sqrt((point_matrix.colwise() - point_matrix.rowwise().mean()).array().pow(2).colwise().sum().mean());

    Eigen::Matrix<float,4,4> normalization_matrix {};
    normalization_matrix.setZero();
    normalization_matrix.diagonal() << scale, scale, scale, 1;
    normalization_matrix(Eigen::seq(0,2),Eigen::last) = -scale * point_matrix.rowwise().mean();
    std::cout << normalization_matrix << std::endl;
    std::cout << normalization_matrix * point_matrix.colwise().homogeneous() << std::endl;
    std::cout << (normalization_matrix * point_matrix.colwise().homogeneous()).colwise().hnormalized() << std::endl;

    improc::PointMatrix<float,4> points_data {point_matrix};
    std::cout << points_data.Normalize() << std::endl;
    return 0;
}
