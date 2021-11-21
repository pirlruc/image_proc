#ifndef IMPROC_CALIB_POINT_MATRIX_HPP
#define IMPROC_CALIB_POINT_MATRIX_HPP

#include <Eigen/Dense>

namespace improc
{

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
            PointMatrix() : EigenMatrixType() {}

            template<typename OtherDerived>
            PointMatrix(const Eigen::MatrixBase<OtherDerived>& other) : EigenMatrixType(other) {}
 
            template<typename OtherDerived>
            PointMatrix& operator=(const Eigen::MatrixBase<OtherDerived>& other)
            {
                this->EigenMatrixType::operator=(other);
                return (*this);
            }

            ConstRowVectorXpr       x() const
            {
                return this->row(PointMatrixType::kComponentXIndex);
            }

            RowVectorXpr            x()
            {
                return this->row(PointMatrixType::kComponentXIndex);
            }

            ConstRowVectorXpr       y() const
            {
                return this->row(PointMatrixType::kComponentYIndex);
            }

            RowVectorXpr            y()
            {
                return this->row(PointMatrixType::kComponentYIndex);
            }

            ConstRowVectorXpr       z() const
            {
                return this->row(PointMatrixType::kComponentZIndex);
            }

            RowVectorXpr            z()
            {
                return this->row(PointMatrixType::kComponentZIndex);
            }

            PointMatrix&            Normalize()
            {
                this->operator=((this->GetNormalizationMatrix() * this->colwise().homogeneous()).colwise().hnormalized());
                return (*this);
            }

        private:
            NormalizationMatrixType GetNormalizationMatrix()
            {
                Scalar scale    = std::sqrt(3.0) 
                                / std::sqrt((this->colwise() - this->rowwise().mean()).array().pow(2).colwise().sum().mean());

                NormalizationMatrixType normalization_matrix {NormalizationMatrixType::Zero()};
                normalization_matrix.diagonal() << scale, scale, scale, 1;
                normalization_matrix(Eigen::seq(0,2),Eigen::last) = -scale * this->rowwise().mean();
                return normalization_matrix;
            }
    };
} 

#endif