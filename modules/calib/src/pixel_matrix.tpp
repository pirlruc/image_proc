template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::PixelMatrix() : EigenMatrixType() {}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
template<typename OtherDerived>
improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::PixelMatrix(const Eigen::MatrixBase<OtherDerived>& other)  : EigenMatrixType(other) {}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
template<typename OtherDerived>
improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>& 
    improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::operator=(const Eigen::MatrixBase<OtherDerived>& other)
{
    this->EigenMatrixType::operator=(other);
    return (*this);
}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::ConstRowVectorXpr 
    improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::u() const
{
    return this->row(PixelMatrixType::kComponentUIndex);
}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::RowVectorXpr 
    improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::u()
{
    return this->row(PixelMatrixType::kComponentUIndex);
}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::ConstRowVectorXpr 
    improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::v() const
{
    return this->row(PixelMatrixType::kComponentVIndex);
}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::RowVectorXpr 
    improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::v()
{
    return this->row(PixelMatrixType::kComponentVIndex);
}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>& 
    improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::Normalize()
{
    this->operator=((this->GetNormalizationMatrix() * this->colwise().homogeneous()).colwise().hnormalized());
    return (*this);
}

template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::NormalizationMatrixType 
    improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::GetNormalizationMatrix()
{
    Scalar scale    = std::sqrt(2.0) 
                    / std::sqrt((this->colwise() - this->rowwise().mean()).array().pow(2).colwise().sum().mean());

    NormalizationMatrixType normalization_matrix {NormalizationMatrixType::Zero()};
    normalization_matrix.diagonal() << scale, scale, 1;
    normalization_matrix(Eigen::seq(0,1),Eigen::last) = -scale * this->rowwise().mean();
    return normalization_matrix;
}
