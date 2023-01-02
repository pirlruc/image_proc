#ifndef IMPROC_CALIB_POINT_MATRIX_HPP
#define IMPROC_CALIB_POINT_MATRIX_HPP

#include <improc/calib/logger_calib.hpp>

#include <Eigen/Dense>

namespace improc
{
    /**
     * @brief Point matrix object and utilities
     * 
     * @tparam Scalar - data type of the point information
     * @tparam NumberVectors - number of vector to consider in matrix
     * @tparam StorageOrder - storage order of the point information
     * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
     */
    template    < typename Scalar
                , int NumberVectors
                , int StorageOrder      = Eigen::ColMajor
                , int MaxNumberVectors  = NumberVectors >
    class PointMatrix : public Eigen::Matrix< Scalar
                                            , 3, NumberVectors
                                            , StorageOrder
                                            , 3, MaxNumberVectors >
    {
        private:
            typedef PointMatrix         < Scalar
                                        , NumberVectors
                                        , StorageOrder
                                        , MaxNumberVectors
                                        > PointMatrixType;
            typedef Eigen::Matrix       < Scalar
                                        , 3, NumberVectors
                                        , StorageOrder
                                        , 3, MaxNumberVectors
                                        > EigenMatrixType;
            typedef Eigen::Matrix       < Scalar
                                        , 4, 4
                                        , StorageOrder
                                        > NormalizationMatrixType;

            static constexpr size_t kComponentXIndex = 0;
            static constexpr size_t kComponentYIndex = 1;
            static constexpr size_t kComponentZIndex = 2;

        public:
            typedef typename Eigen::DenseBase<EigenMatrixType>::RowXpr      RowVectorXpr;
            typedef typename Eigen::DenseBase<EigenMatrixType>::ConstRowXpr ConstRowVectorXpr;

        public:
            PointMatrix();

            template<typename OtherDerived>
            PointMatrix(const Eigen::MatrixBase<OtherDerived>& other);
 
            template<typename OtherDerived>
            PointMatrix& operator=(const Eigen::MatrixBase<OtherDerived>& other);

            ConstRowVectorXpr       x() const;
            ConstRowVectorXpr       y() const;
            ConstRowVectorXpr       z() const;
            RowVectorXpr            x();
            RowVectorXpr            y();
            RowVectorXpr            z();

            PointMatrix&            Normalize();

        private:
            NormalizationMatrixType GetNormalizationMatrix();
    };

    #include <improc/calib/point_matrix.tpp>
} 

#endif