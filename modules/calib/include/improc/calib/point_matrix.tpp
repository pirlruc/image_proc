/**
 * @brief Construct a new improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors> object
 * 
 * @tparam Scalar - data type of the point information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the point information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::PointMatrix() : EigenMatrixType() {}

/**
 * @brief Construct a new improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors> object
 * 
 * @param other - eigen matrix or eigen expression with point information
 * @tparam Scalar - data type of the point information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the point information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
template<typename OtherDerived>
improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::PointMatrix(const Eigen::MatrixBase<OtherDerived>& other)  : EigenMatrixType(std::move(other)) {}

/**
 * @brief Assign a improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors> object
 * 
 * @param other - eigen matrix or eigen expression with point information
 * @tparam Scalar - data type of the point information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the point information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
template<typename OtherDerived>
improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>& 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::operator=(const Eigen::MatrixBase<OtherDerived>& other)
{
    IMPROC_CALIB_LOGGER_TRACE("Assigning other point matrix...");
    this->EigenMatrixType::operator=(std::move(other));
    return (*this);
}

/**
 * @brief Obtain x-coordinates of point matrix
 * 
 * @tparam Scalar - data type of the point information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the point information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::ConstRowVectorXpr 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::x() const
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining x-coordinates of point matrix...");
    return this->row(PointMatrixType::kComponentXIndex);
}

/**
 * @brief Obtain x-coordinates of point matrix
 * 
 * @tparam Scalar - data type of the point information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the point information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::RowVectorXpr 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::x()
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining x-coordinates of point matrix...");
    return this->row(PointMatrixType::kComponentXIndex);
}

/**
 * @brief Obtain y-coordinates of point matrix
 * 
 * @tparam Scalar - data type of the point information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the point information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::ConstRowVectorXpr 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::y() const
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining y-coordinates of point matrix...");
    return this->row(PointMatrixType::kComponentYIndex);
}

/**
 * @brief Obtain y-coordinates of point matrix
 * 
 * @tparam Scalar - data type of the point information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the point information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::RowVectorXpr 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::y()
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining y-coordinates of point matrix...");
    return this->row(PointMatrixType::kComponentYIndex);
}

/**
 * @brief Obtain z-coordinates of point matrix
 * 
 * @tparam Scalar - data type of the point information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the point information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::ConstRowVectorXpr 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::z() const
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining z-coordinates of point matrix...");
    return this->row(PointMatrixType::kComponentZIndex);
}

/**
 * @brief Obtain z-coordinates of point matrix
 * 
 * @tparam Scalar - data type of the point information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the point information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::RowVectorXpr 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::z()
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining z-coordinates of point matrix...");
    return this->row(PointMatrixType::kComponentZIndex);
}

/**
 * @brief Normalize point information
 * 
 * @tparam Scalar - data type of the point information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the point information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>& 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::Normalize()
{
    IMPROC_CALIB_LOGGER_TRACE("Normalizing point data...");
    this->operator=((this->GetNormalizationMatrix() * this->colwise().homogeneous()).colwise().hnormalized());
    return (*this);
}

/**
 * @brief Obtain normalization matrix from pixel information
 * 
 * @tparam Scalar - data type of the point information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the point information
 * @tparam MaxNumberVectors - maximum number of vector to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::NormalizationMatrixType 
    improc::PointMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::GetNormalizationMatrix()
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining normalization matrix...");
    auto rowwise_mean = this->rowwise().mean();
    Scalar scale      = std::sqrt(3.0) 
                      / std::sqrt((this->colwise() - rowwise_mean).array().pow(2).colwise().sum().mean());

    NormalizationMatrixType normalization_matrix {NormalizationMatrixType::Zero()};
    normalization_matrix.diagonal() << scale, scale, scale, 1;
    normalization_matrix(Eigen::seq(0,2),Eigen::last) = -std::move(scale) * std::move(rowwise_mean);
    return normalization_matrix;
}
