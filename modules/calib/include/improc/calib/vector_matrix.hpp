#ifndef IMPROC_CALIB_VECTOR_MATRIX_HPP
#define IMPROC_CALIB_VECTOR_MATRIX_HPP

#include <Eigen/Dense>
#include <vector>

namespace improc
{
    template    <   typename Scalar
                ,   int NumberComponents
                ,   int NumberVectors
                ,   int StorageOrder        = Eigen::ColMajor
                ,   int MaxNumberComponents = NumberComponents
                ,   int MaxNumberVectors    = NumberVectors
                >
    class VectorMatrix
    {
        public:
            typedef Eigen::Matrix   <   Scalar
                                    ,   NumberComponents
                                    ,   NumberVectors
                                    ,   StorageOrder
                                    ,   MaxNumberComponents
                                    ,   MaxNumberVectors
                                    >   VectorMatrixData;

            typedef typename Eigen::DenseBase   <  Eigen::Matrix    <   Scalar
                                                                    ,   NumberComponents
                                                                    ,   NumberVectors
                                                                    ,   StorageOrder
                                                                    ,   MaxNumberComponents
                                                                    ,   MaxNumberVectors
                                                                    >
                                                >::ColXpr ColumnVectorXpr;

            typedef typename Eigen::DenseBase   <  Eigen::Matrix    <   Scalar
                                                                    ,   NumberComponents
                                                                    ,   NumberVectors
                                                                    ,   StorageOrder
                                                                    ,   MaxNumberComponents
                                                                    ,   MaxNumberVectors
                                                                    >
                                                >::RowXpr RowVectorXpr;

            typedef Eigen::Matrix   <   Scalar
                                    ,   NumberComponents
                                    ,   1
                                    ,   Eigen::ColMajor
                                    ,   MaxNumberComponents
                                    ,   1
                                    >   ColumnVector;

            typedef Eigen::Matrix   <   Scalar
                                    ,   NumberComponents
                                    ,   Eigen::Dynamic
                                    ,   StorageOrder
                                    ,   MaxNumberComponents
                                    ,   MaxNumberVectors
                                    >   MultipleVectors;

            typedef Eigen::Matrix   <   Scalar
                                    ,   1
                                    ,   NumberVectors
                                    ,   Eigen::RowMajor
                                    ,   1
                                    ,   MaxNumberVectors
                                    >   RowVector;

            typedef Eigen::Matrix   <   Scalar
                                    ,   Eigen::Dynamic
                                    ,   NumberVectors
                                    ,   StorageOrder
                                    ,   MaxNumberComponents
                                    ,   MaxNumberVectors
                                    >   MultipleComponents;

        private:
            VectorMatrixData        data_;
            bool                    homogeneous_;

        public:
            VectorMatrix();
            VectorMatrix(const VectorMatrixData& vector_matrix_data);

            void                    set_data(const VectorMatrixData& vector_matrix_data)
            {
                this->data_ = vector_matrix_data;
            }

            inline size_t           get_number_components()  const
            {
                size_t number_components = this->data_.rows();
                if (this->homogeneous_ == true)
                    number_components -= 1;
                return number_components;
            }

            inline size_t           get_number_vectors()     const
            {
                return this->data_.cols();
            }

            VectorMatrixData        get_data()
            {
                return this->data_;
            }
            
            ColumnVectorXpr         GetVector      (size_t vector_idx)
            {
                return this->data_.col(vector_idx);
            }

            MultipleVectors        GetVectors     (std::vector<size_t> vector_idxs)    const
            {
                return this->data_(Eigen::all,vector_idxs);
            }

            RowVectorXpr            GetComponent    (size_t component_idx)
            {
                return this->data_.row(component_idx);
            }

            MultipleComponents      GetComponents (std::vector<size_t> component_idxs)  const
            {
                return this->data_(component_idxs,Eigen::all);
            }

            RowVector               GetVectorNorms()    const
            {
                return this->data_.colwise().squaredNorm();
            }

            // void SetHomogeneousCoordinates();
            // void RemoveHomogeneousCoordinates();
    };

    typedef VectorMatrix<double,Eigen::Dynamic,Eigen::Dynamic> VectorMatrixXd;
    typedef VectorMatrix<float ,Eigen::Dynamic,Eigen::Dynamic> VectorMatrixXf;
    typedef VectorMatrix<int   ,Eigen::Dynamic,Eigen::Dynamic> VectorMatrixXi;
}

#include <vector_matrix.tpp>

#endif