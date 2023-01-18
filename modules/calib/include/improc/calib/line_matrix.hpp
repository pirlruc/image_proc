#ifndef IMPROC_CALIB_LINE_MATRIX_HPP
#define IMPROC_CALIB_LINE_MATRIX_HPP

#include <improc/improc_defs.hpp>
#include <improc/calib/logger_calib.hpp>

#include <Eigen/Dense>

namespace improc
{
    /**
     * @brief Line matrix object and utilities
     * Consider that a line is defined by the parameters (a,b,c):
     *          a * x + b * y + c = 0
     * 
     * @tparam Scalar - data type of the line information
     * @tparam NumberVectors - number of vector to consider in matrix
     * @tparam StorageOrder - storage order of the line information
     * @tparam MaxNumberVectors - maximum number of vectors to consider in matrix
     */
    template    < typename Scalar
                , int NumberVectors     = Eigen::Dynamic
                , int StorageOrder      = Eigen::ColMajor
                , int MaxNumberVectors  = NumberVectors >
    class IMPROC_API LineMatrix : public Eigen::Matrix  < Scalar
                                                        , 3, NumberVectors
                                                        , StorageOrder
                                                        , 3, MaxNumberVectors >
    {
        private:
            typedef LineMatrix          < Scalar
                                        , NumberVectors
                                        , StorageOrder
                                        , MaxNumberVectors
                                        > LineMatrixType;
            typedef Eigen::Matrix       < Scalar
                                        , 3, NumberVectors
                                        , StorageOrder
                                        , 3, MaxNumberVectors
                                        > EigenMatrixType;

            static constexpr size_t kComponentAIndex = 0;
            static constexpr size_t kComponentBIndex = 1;
            static constexpr size_t kComponentCIndex = 2;

        public:
            typedef typename Eigen::DenseBase<EigenMatrixType>::RowXpr      RowVectorXpr;
            typedef typename Eigen::DenseBase<EigenMatrixType>::ConstRowXpr ConstRowVectorXpr;

        public:
            LineMatrix();

            template<typename OtherDerived>
            LineMatrix(const Eigen::MatrixBase<OtherDerived>& other);
 
            template<typename OtherDerived>
            LineMatrix& operator=(const Eigen::MatrixBase<OtherDerived>& other);

            ConstRowVectorXpr                   a() const;
            ConstRowVectorXpr                   b() const;
            ConstRowVectorXpr                   c() const;
            RowVectorXpr                        a();
            RowVectorXpr                        b();
            RowVectorXpr                        c();

            inline size_t                       Number() const
            {
                return this->cols();
            }
    };

    #include <improc/calib/line_matrix.tpp>
} 

#endif