#ifndef IMPROC_CALIB_PIXEL_MATRIX_HPP
#define IMPROC_CALIB_PIXEL_MATRIX_HPP

#include <Eigen/Dense>

namespace improc
{

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

    #include <pixel_matrix.tpp>
} 

#endif