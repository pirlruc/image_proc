template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::PointMatrix() : EigenMatrixType() {}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
template<typename OtherDerived>
improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::PointMatrix(const Eigen::MatrixBase<OtherDerived>& other)  : EigenMatrixType(other) {}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
template<typename OtherDerived>
improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>& 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::operator=(const Eigen::MatrixBase<OtherDerived>& other)
{
    this->EigenMatrixType::operator=(other);
    return (*this);
}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::ConstRowVectorXpr 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::x() const
{
    return this->row(PointMatrixType::kComponentXIndex);
}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::RowVectorXpr 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::x()
{
    return this->row(PointMatrixType::kComponentXIndex);
}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::ConstRowVectorXpr 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::y() const
{
    return this->row(PointMatrixType::kComponentYIndex);
}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::RowVectorXpr 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::y()
{
    return this->row(PointMatrixType::kComponentYIndex);
}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::ConstRowVectorXpr 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::z() const
{
    return this->row(PointMatrixType::kComponentZIndex);
}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::RowVectorXpr 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::z()
{
    return this->row(PointMatrixType::kComponentZIndex);
}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>& 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::Normalize()
{
    this->operator=((this->GetNormalizationMatrix() * this->colwise().homogeneous()).colwise().hnormalized());
    return (*this);
}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::NormalizationMatrixType 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::GetNormalizationMatrix()
{
    Scalar scale    = std::sqrt(3.0) 
                    / std::sqrt((this->colwise() - this->rowwise().mean()).array().pow(2).colwise().sum().mean());

    NormalizationMatrixType normalization_matrix {NormalizationMatrixType::Zero()};
    normalization_matrix.diagonal() << scale, scale, scale, 1;
    normalization_matrix(Eigen::seq(0,2),Eigen::last) = -scale * this->rowwise().mean();
    return normalization_matrix;
}
