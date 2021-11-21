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
            PixelMatrix() : EigenMatrixType() {}

            template<typename OtherDerived>
            PixelMatrix(const Eigen::MatrixBase<OtherDerived>& other) : EigenMatrixType(other) {}
 
            template<typename OtherDerived>
            PixelMatrix& operator=(const Eigen::MatrixBase<OtherDerived>& other)
            {
                this->EigenMatrixType::operator=(other);
                return (*this);
            }

            ConstRowVectorXpr       u() const
            {
                return this->row(PixelMatrixType::kComponentUIndex);
            }

            RowVectorXpr            u()
            {
                return this->row(PixelMatrixType::kComponentUIndex);
            }

            ConstRowVectorXpr       v() const
            {
                return this->row(PixelMatrixType::kComponentVIndex);
            }

            RowVectorXpr            v()
            {
                return this->row(PixelMatrixType::kComponentVIndex);
            }

            PixelMatrix&            Normalize()
            {
                this->operator=((this->GetNormalizationMatrix() * this->colwise().homogeneous()).colwise().hnormalized());
                return (*this);
            }

        private:
            NormalizationMatrixType GetNormalizationMatrix()
            {
                Scalar scale    = std::sqrt(2.0) 
                                / std::sqrt((this->colwise() - this->rowwise().mean()).array().pow(2).colwise().sum().mean());

                NormalizationMatrixType normalization_matrix {NormalizationMatrixType::Zero()};
                normalization_matrix.diagonal() << scale, scale, 1;
                normalization_matrix(Eigen::seq(0,1),Eigen::last) = -scale * this->rowwise().mean();
                return normalization_matrix;
            }
    };
} 

#endif