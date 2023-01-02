#ifndef IMPROC_CALIB_HOMOGRAPHY_MATRIX_HPP
#define IMPROC_CALIB_HOMOGRAPHY_MATRIX_HPP

#include <improc/calib/pixel_matrix.hpp>
#include <improc/calib/logger_calib.hpp>

#include <Eigen/Dense>

namespace improc
{
    /**
     * @brief Homography matrix object and utilities
     * 
     * @tparam Scalar - data type of the homography and pixel matrix
     * @tparam StorageOrder - storage order of the homography and pixel matrix
     */
    template    < typename Scalar
                , int StorageOrder = Eigen::ColMajor >
    class HomographyMatrix : public Eigen::Matrix   < Scalar
                                                    , 3, 3
                                                    , StorageOrder
                                                    , 3, 3 >
    {
        private:
            typedef HomographyMatrix< Scalar
                                    , StorageOrder
                                    > HomographyMatrixType;
            typedef Eigen::Matrix   < Scalar
                                    , 3, 3
                                    , StorageOrder
                                    , 3, 3
                                    > EigenMatrixType;

        public:
            HomographyMatrix();

            template<typename PixelMatrixDerived>
            HomographyMatrix( improc::PixelMatrix<PixelMatrixDerived> detected_pixels
                            , improc::PixelMatrix<PixelMatrixDerived> reference_pixels );

            template<typename OtherDerived>
            HomographyMatrix(const Eigen::MatrixBase<OtherDerived>& other);
 
            template<typename OtherDerived>
            HomographyMatrix& operator=(const Eigen::MatrixBase<OtherDerived>& other);

        private:
            template<typename PixelMatrixDerived>
            static auto             GetObservationMatrixFromPointCorrespondences( const improc::PixelMatrix<PixelMatrixDerived>& detected_pixels
                                                                                , const improc::PixelMatrix<PixelMatrixDerived>& reference_pixels );

    };

    #include <improc/calib/homography_matrix.tpp>
} 

#endif