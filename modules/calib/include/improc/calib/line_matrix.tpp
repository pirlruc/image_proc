/**
 * @brief Construct a new improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors> object
 * 
 * @tparam Scalar - data type of the line information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the line information
 * @tparam MaxNumberVectors - maximum number of vectors to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::LineMatrix() 
: EigenMatrixType() {}

/**
 * @brief Construct a new improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors> object
 * 
 * @param other - eigen matrix or eigen expression with line information
 * @tparam Scalar - data type of the line information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the line information
 * @tparam MaxNumberVectors - maximum number of vectors to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
template<typename OtherDerived>
improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::LineMatrix(const Eigen::MatrixBase<OtherDerived>& other)
: EigenMatrixType(std::move(other)) {}

/**
 * @brief Assign a improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors> object
 * 
 * @param other - eigen matrix or eigen expression with line information
 * @tparam Scalar - data type of the line information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the line information
 * @tparam MaxNumberVectors - maximum number of vectors to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
template<typename OtherDerived>
improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>& 
    improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::operator=(const Eigen::MatrixBase<OtherDerived>& other)
{
    IMPROC_CALIB_LOGGER_TRACE("Assigning other point matrix...");
    this->EigenMatrixType::operator=(std::move(other));
    return (*this);
}

/**
 * @brief Obtain a-coordinates of line matrix
 * 
 * @tparam Scalar - data type of the line information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the line information
 * @tparam MaxNumberVectors - maximum number of vectors to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::ConstRowVectorXpr 
    improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::a() const
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining a-coordinates of line matrix...");
    return this->row(LineMatrixType::kComponentAIndex);
}

/**
 * @brief Obtain a-coordinates of line matrix
 * 
 * @tparam Scalar - data type of the line information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the line information
 * @tparam MaxNumberVectors - maximum number of vectors to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::RowVectorXpr 
    improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::a()
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining a-coordinates of point matrix...");
    return this->row(LineMatrixType::kComponentAIndex);
}

/**
 * @brief Obtain b-coordinates of line matrix
 * 
 * @tparam Scalar - data type of the line information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the line information
 * @tparam MaxNumberVectors - maximum number of vectors to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::ConstRowVectorXpr 
    improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::b() const
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining b-coordinates of line matrix...");
    return this->row(LineMatrixType::kComponentBIndex);
}

/**
 * @brief Obtain b-coordinates of line matrix
 * 
 * @tparam Scalar - data type of the line information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the line information
 * @tparam MaxNumberVectors - maximum number of vectors to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::RowVectorXpr 
    improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::b()
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining b-coordinates of point matrix...");
    return this->row(LineMatrixType::kComponentBIndex);
}

/**
 * @brief Obtain c-coordinates of line matrix
 * 
 * @tparam Scalar - data type of the line information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the line information
 * @tparam MaxNumberVectors - maximum number of vectors to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::ConstRowVectorXpr 
    improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::c() const
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining c-coordinates of point matrix...");
    return this->row(LineMatrixType::kComponentCIndex);
}

/**
 * @brief Obtain c-coordinates of line matrix
 * 
 * @tparam Scalar - data type of the line information
 * @tparam NumberVectors - number of vector to consider in matrix
 * @tparam StorageOrder - storage order of the line information
 * @tparam MaxNumberVectors - maximum number of vectors to consider in matrix
 */
template< typename Scalar
        , int NumberVectors
        , int StorageOrder
        , int MaxNumberVectors >
typename improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::RowVectorXpr 
    improc::LineMatrix<Scalar,NumberVectors,StorageOrder,MaxNumberVectors>::c()
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining c-coordinates of point matrix...");
    return this->row(LineMatrixType::kComponentCIndex);
}
