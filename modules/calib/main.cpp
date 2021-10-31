#include <improc/calib/vector_matrix.hpp>
#include <iostream>

int main()
{
    Eigen::Matrix<int,3,2> matrix;
    matrix(0,0) = 1;
    matrix(0,1) = 2;
    matrix(1,0) = 3;
    matrix(1,1) = 4;
    matrix(2,0) = 5;
    matrix(2,1) = 6;
    std::cout << typeid(matrix).name() << std::endl;
    std::cout << typeid(matrix.colwise().homogeneous()).name() << std::endl;
    std::cout << typeid(matrix.colwise().homogeneous().colwise().hnormalized()).name() << std::endl;
    std::cout << matrix << std::endl;
    std::cout << matrix.colwise().homogeneous() << std::endl;
    std::cout << matrix.colwise().homogeneous().colwise().hnormalized() << std::endl;
    Eigen::Homogeneous<Eigen::Matrix<int,3,2>,0> mh = matrix.colwise().homogeneous();
    matrix = mh.colwise().hnormalized();

    improc::VectorMatrix<int,3,2> m1 {};
    m1.set_data(matrix);
    std::cout << "-- Dimensions --" << std::endl;
    std::cout << m1.get_number_components() << std::endl;
    std::cout << m1.get_number_vectors() << std::endl;

    std::cout << "-- Get Components --" << std::endl;
    std::cout << m1.GetComponents({0,2}) << std::endl;

    std::cout << "-- Get Vectors --" << std::endl;
    std::cout << m1.GetVectors({0,1}) << std::endl;

    std::cout << "-- Get Homogeneous --" << std::endl;
    std::cout << m1.Homogeneous() << std::endl;
    // std::cout << m1.HomogeneousNormalized() << std::endl;

    improc::VectorMatrix<int,3,2> m2 {matrix};
    std::cout << "-- Accessors --" << std::endl;
    std::cout << m2.get_number_components() << std::endl;
    std::cout << m2.get_number_vectors() << std::endl;
    std::cout << m2.get_data() << std::endl;
    std::cout << m2.GetComponent(0) << std::endl;
    std::cout << m2.GetVector(0) << std::endl;

    improc::VectorMatrix<int,3,2>::ColumnVector c2 = m2.GetVector(0);
    improc::VectorMatrix<int,3,2>::RowVector    r2 = m2.GetComponent(0);
    c2(1) = 2.0;
    r2(0) = 10.0;
    std::cout << "-- Setters with Assignment --" << std::endl;
    std::cout << c2 << std::endl;
    std::cout << r2 << std::endl;
    std::cout << m2.get_data() << std::endl;

    std::cout << "-- Setters without Assignment --" << std::endl;
    m2.GetVector(0)     = c2;
    m2.GetComponent(0)  = r2;
    std::cout << m2.get_data() << std::endl;

    std::cout << "-- Vector Norms --" << std::endl;
    std::cout << m2.GetVectorNorms() << std::endl;

    return 0;
}