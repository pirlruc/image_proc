#include <improc/calib/pixel_matrix.hpp>
#include <iostream>

int main()
{
    improc::PixelMatrix<int,2> pixels {};
    pixels = Eigen::Matrix<int,2,2>::Zero();
    improc::PixelMatrix<int,2>::RowVectorXpr u = pixels.u();
    u(0) = 1;
    std::cout << u << std::endl;
    std::cout << pixels.u() << std::endl;
    pixels.u()(0) = 2;
    pixels.u()(1) = 3;
    std::cout << pixels.u() << std::endl;

    Eigen::Matrix<float,2,4> pixel_matrix {};
    pixel_matrix(0,0) = 1;
    pixel_matrix(0,1) = 2;
    pixel_matrix(0,2) = 3;
    pixel_matrix(0,3) = 4;
    pixel_matrix(1,0) = 5;
    pixel_matrix(1,1) = 6;
    pixel_matrix(1,2) = 7;
    pixel_matrix(1,3) = 8;
    std::cout << pixel_matrix << std::endl;
    std::cout << pixel_matrix.colwise().homogeneous() << std::endl;

    float scale = std::sqrt(2.0) 
                / std::sqrt((pixel_matrix.colwise() - pixel_matrix.rowwise().mean()).array().pow(2).colwise().sum().mean());

    Eigen::Matrix<float,3,3> normalization_matrix {};
    normalization_matrix.setZero();
    normalization_matrix.diagonal() << scale, scale, 1;
    normalization_matrix(Eigen::seq(0,1),Eigen::last) = -scale * pixel_matrix.rowwise().mean();
    std::cout << normalization_matrix << std::endl;
    std::cout << normalization_matrix * pixel_matrix.colwise().homogeneous() << std::endl;
    std::cout << (normalization_matrix * pixel_matrix.colwise().homogeneous()).colwise().hnormalized() << std::endl;

    improc::PixelMatrix<float,4> pixel_data {pixel_matrix};
    std::cout << pixel_data.Normalize() << std::endl;
    return 0;
}
