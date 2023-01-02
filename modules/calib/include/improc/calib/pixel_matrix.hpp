#ifndef IMPROC_CALIB_PIXEL_MATRIX_HPP
#define IMPROC_CALIB_PIXEL_MATRIX_HPP

#include <improc/calib/logger_calib.hpp>

#include <Eigen/Dense>

namespace improc
{
    /**
     * @brief Pixel matrix object and utilities
     * 
     * @tparam Scalar - data type of the pixel information
     * @tparam NumberVectors - number of vector to consider in matrix
     * @tparam StorageOrder - storage order of the pixel information
     * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
     */
    template    < typename Scalar
                , int NumberVectors
                , int StorageOrder      = Eigen::ColMajor
                , int MaxNumberVectors  = NumberVectors >
    class PixelMatrix : public Eigen::Matrix< Scalar
                                            , 2, NumberVectors
                                            , StorageOrder
                                            , 2, MaxNumberVectors >
    {
        private:
            typedef PixelMatrix         < Scalar
                                        , NumberVectors
                                        , StorageOrder
                                        , MaxNumberVectors
                                        > PixelMatrixType;
            typedef Eigen::Matrix       < Scalar
                                        , 2, NumberVectors
                                        , StorageOrder
                                        , 2, MaxNumberVectors
                                        > EigenMatrixType;
            typedef Eigen::Matrix       < Scalar
                                        , 3, 3
                                        , StorageOrder
                                        > NormalizationMatrixType;

            static constexpr size_t kComponentUIndex = 0;
            static constexpr size_t kComponentVIndex = 1;

        public:
            typedef typename Eigen::DenseBase<EigenMatrixType>::RowXpr      RowVectorXpr;
            typedef typename Eigen::DenseBase<EigenMatrixType>::ConstRowXpr ConstRowVectorXpr;

        public:
            PixelMatrix();

            template<typename OtherDerived>
            PixelMatrix(const Eigen::MatrixBase<OtherDerived>& other);
 
            template<typename OtherDerived>
            PixelMatrix& operator=(const Eigen::MatrixBase<OtherDerived>& other);

            ConstRowVectorXpr       u() const;
            ConstRowVectorXpr       v() const;
            RowVectorXpr            u();
            RowVectorXpr            v();

            PixelMatrix&            Normalize();

        private:
            NormalizationMatrixType GetNormalizationMatrix();
    };

    #include <improc/calib/pixel_matrix.tpp>
} 

#endif