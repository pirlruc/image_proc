/**
 * @brief Construct a new improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors> object
 * 
 * @tparam Scalar - data type of the pixel information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the pixel information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::PixelMatrix() : EigenMatrixType() {}

/**
 * @brief Construct a new improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors> object
 * 
 * @param other - eigen matrix or eigen expression with pixel information
 * @tparam Scalar - data type of the pixel information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the pixel information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
template<typename OtherDerived>
improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::PixelMatrix(const Eigen::MatrixBase<OtherDerived>& other)  : EigenMatrixType(std::move(other)) {}

/**
 * @brief Assign a improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors> object
 * 
 * @param other - eigen matrix or eigen expression with pixel information
 * @tparam Scalar - data type of the pixel information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the pixel information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
template<typename OtherDerived>
improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>& 
    improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::operator=(const Eigen::MatrixBase<OtherDerived>& other)
{
    IMPROC_CALIB_LOGGER_TRACE("Assigning other pixel matrix...");
    this->EigenMatrixType::operator=(std::move(other));
    return (*this);
}

/**
 * @brief Obtain u-coordinates of pixel matrix
 * 
 * @tparam Scalar - data type of the pixel information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the pixel information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::ConstRowVectorXpr 
    improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::u() const
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining u-coordinates of pixel matrix...");
    return this->row(PixelMatrixType::kComponentUIndex);
}

/**
 * @brief Obtain u-coordinates of pixel matrix
 * 
 * @tparam Scalar - data type of the pixel information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the pixel information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::RowVectorXpr 
    improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::u()
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining u-coordinates of pixel matrix...");
    return this->row(PixelMatrixType::kComponentUIndex);
}

/**
 * @brief Obtain v-coordinates of pixel matrix
 * 
 * @tparam Scalar - data type of the pixel information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the pixel information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::ConstRowVectorXpr 
    improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::v() const
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining v-coordinates of pixel matrix...");
    return this->row(PixelMatrixType::kComponentVIndex);
}

/**
 * @brief Obtain v-coordinates of pixel matrix
 * 
 * @tparam Scalar - data type of the pixel information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the pixel information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::RowVectorXpr 
    improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::v()
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining v-coordinates of pixel matrix...");
    return this->row(PixelMatrixType::kComponentVIndex);
}

/**
 * @brief Normalize pixel information
 * 
 * @tparam Scalar - data type of the pixel information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the pixel information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>& 
    improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::Normalize()
{
    IMPROC_CALIB_LOGGER_TRACE("Normalizing pixel data...");
    this->operator=((this->GetNormalizationMatrix() * this->colwise().homogeneous()).colwise().hnormalized());
    return (*this);
}

/**
 * @brief Obtain normalization matrix from pixel information
 * 
 * @tparam Scalar - data type of the pixel information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the pixel information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::NormalizationMatrixType 
    improc::PixelMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::GetNormalizationMatrix()
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining normalization matrix...");
    auto rowwise_mean = this->rowwise().mean();
    Scalar scale      = std::sqrt(2.0) 
                      / std::sqrt((this->colwise() - rowwise_mean).array().pow(2).colwise().sum().mean());

    NormalizationMatrixType normalization_matrix {NormalizationMatrixType::Zero()};
    normalization_matrix.diagonal() << scale, scale, 1;
    normalization_matrix(Eigen::seq(0,1),Eigen::last) = -std::move(scale) * std::move(rowwise_mean);
    return normalization_matrix;
}
