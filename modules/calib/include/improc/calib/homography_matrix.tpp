/**
 * @brief Construct a new improc::HomographyMatrix<Scalar,StorageOrder> object
 * 
 * @tparam Scalar - data type of the homography and pixel matrix
 * @tparam StorageOrder - storage order of the homography and pixel matrix
 */
template< typename Scalar, int StorageOrder >
improc::HomographyMatrix<Scalar,StorageOrder>::HomographyMatrix() : EigenMatrixType() {}

/**
 * @brief Obtain homography matrix from point correspondences
 * 
 * @param detected_pixels - detected pixels in image
 * @param reference_pixels - detected pixels in reference image or in ground truth image
 * @tparam Scalar - data type of the homography and pixel matrix
 * @tparam StorageOrder - storage order of the homography and pixel matrix
 * @tparam PixelMatrixDerived - pixel matrix class derivation
 * @tparam AxbSolver - solver to remove normalization from homography matrix estimation
 * @tparam QRPreConditioner - pixel matrix class derivation
 */
template< typename Scalar, int StorageOrder >
template<typename PixelMatrixDerived, template <typename> class AxbSolver, int QRPreConditioner>
improc::HomographyMatrix<Scalar,StorageOrder>::HomographyMatrix 
        ( improc::PixelMatrix<PixelMatrixDerived> detected_pixels
        , improc::PixelMatrix<PixelMatrixDerived> reference_pixels ) 
: improc::HomographyMatrix<Scalar,StorageOrder>()
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining homography matrix from point correspondences...");
    if (detected_pixels.Number() < improc::HomographyMatrix<Scalar,StorageOrder>::kMinimumPointCorrespondences)
    {
        IMPROC_CALIB_LOGGER_ERROR( "ERROR_01: Homography estimation cannot be estimated. Minimum number of point correspondences is 4, {} correspondences given."
                                 , detected_pixels.Number() );
        throw improc::invalid_homography_estimation();
    }

    typename improc::PixelMatrix<PixelMatrixDerived>::NormalizationMatrixType detected_norm_matrix  = detected_pixels.GetNormalizationMatrix();
    typename improc::PixelMatrix<PixelMatrixDerived>::NormalizationMatrixType reference_norm_matrix = reference_pixels.GetNormalizationMatrix();

    improc::HomographyMatrix<Scalar,StorageOrder>::ObservationMatrixType      observation_matrix    = 
        improc::HomographyMatrix<Scalar,StorageOrder>::GetObservationMatrixFromPointCorrespondences ( detected_pixels.Normalize()
                                                                                                    , reference_pixels.Normalize() );

    // The homography matrix corresponds to the null space of the observation matrix. Use dynamic columns to allow computation of matrix V.
    auto svd_decomposer = Eigen::JacobiSVD<Eigen::Matrix<Scalar,Eigen::Dynamic,Eigen::Dynamic,StorageOrder>,QRPreConditioner>(std::move(observation_matrix),Eigen::ComputeThinV);
    svd_decomposer.setThreshold(Eigen::Default);
    if (svd_decomposer.info() != Eigen::Success)
    {
        int error_code = svd_decomposer.info();
        IMPROC_CALIB_LOGGER_ERROR   ( "ERROR_02: Could not perform the SVD decomposition. Error code = {}."
                                    , std::move(error_code) );
        throw improc::invalid_svd_decomposition();
    }
    auto normalized_matrix = std::move(svd_decomposer).matrixV()(Eigen::all,Eigen::last).reshaped(3,3).transpose();

    // Remove normalization from the matrix estimated
    AxbSolver<typename improc::PixelMatrix<PixelMatrixDerived>::NormalizationMatrixType> axb_solver(std::move(detected_norm_matrix));
    this->operator=(std::move(axb_solver).solve(std::move(normalized_matrix) * std::move(reference_norm_matrix)));
}

/**
 * @brief Construct a new improc::HomographyMatrix<Scalar,StorageOrder> object
 * 
 * @param other - eigen matrix or eigen expression with homography matrix
 * @tparam Scalar - data type of the homography and pixel matrix
 * @tparam StorageOrder - storage order of the homography and pixel matrix
 */
template< typename Scalar, int StorageOrder >
template<typename OtherDerived>
improc::HomographyMatrix<Scalar,StorageOrder>::HomographyMatrix(const Eigen::MatrixBase<OtherDerived>& other)  : EigenMatrixType(std::move(other)) {}

/**
 * @brief Assign a improc::HomographyMatrix<Scalar,StorageOrder> object
 * 
 * @param other - eigen matrix or eigen expression with homography matrix
 * @tparam Scalar - data type of the homography and pixel matrix
 * @tparam StorageOrder - storage order of the homography and pixel matrix
 */
template< typename Scalar, int StorageOrder >
template<typename OtherDerived>
improc::HomographyMatrix<Scalar,StorageOrder>& 
    improc::HomographyMatrix<Scalar,StorageOrder>::operator=(const Eigen::MatrixBase<OtherDerived>& other)
{
    IMPROC_CALIB_LOGGER_TRACE("Assigning other homography matrix...");
    this->EigenMatrixType::operator=(std::move(other));
    return (*this);
}

/**
 * @brief Obtain observation matrix from point correspondences
 * 
 * @param detected_pixels - detected pixels in image
 * @param reference_pixels - detected pixels in reference image or in ground truth image
 * @tparam Scalar - data type of the homography and pixel matrix
 * @tparam StorageOrder - storage order of the homography and pixel matrix
 * @tparam PixelMatrixDerived - pixel matrix class derivation
 */
template< typename Scalar, int StorageOrder >
template<typename PixelMatrixDerived>
typename improc::HomographyMatrix<Scalar,StorageOrder>::ObservationMatrixType 
    improc::HomographyMatrix<Scalar,StorageOrder>::GetObservationMatrixFromPointCorrespondences
        ( const improc::PixelMatrix<PixelMatrixDerived>& detected_pixels
        , const improc::PixelMatrix<PixelMatrixDerived>& reference_pixels )
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining observation matrix from point correspondences considering cross-product...");
    static constexpr unsigned int kNumberEquationsPerPointCorrespondence = 3;
    static constexpr unsigned int kNumberPixelDimensions                 = 3;
    if (detected_pixels.Number() != reference_pixels.Number())
    {
        IMPROC_CALIB_LOGGER_ERROR( "ERROR_01: Detected and reference pixels should have the same size. {} detected pixels and {} reference pixels."
                                 , detected_pixels.Number(), reference_pixels.Number() );
        throw improc::inconsistent_size_detected_reference_pixels();
    }

    // Consider the image pixels as p = [u v w]^T and the refence pixels as P = [x y m]^T
    // The observation matrix O for the point correspondences is defined as:
    // O = [  w*P^T  0     -u*P^T
    //        0     -w*P^T  v*P^T
    //       -v*P^T  u*P^T  0     ]
    //
    // Remember that for the homography case w = 1 and m = 1 since they correspond to the 
    // values in the homogeneous row of the matrices.
    auto first_row_indices              = Eigen::seq(                            0,     reference_pixels.Number() - 1);
    auto second_row_indices             = Eigen::seq(    reference_pixels.Number(), 2 * reference_pixels.Number() - 1);
    auto third_row_indices              = Eigen::seq(2 * reference_pixels.Number(), Eigen::last);

    auto detected_u_matrix              = detected_pixels.u().replicate(kNumberPixelDimensions,1).transpose();  // N x 3 - [u,u,u]
    auto detected_v_matrix              = detected_pixels.v().replicate(kNumberPixelDimensions,1).transpose();  // N x 3 - [v,v,v]
    auto reference_pixels_homogeneous_t = reference_pixels.Homogeneous().transpose();                           // N x 3 - [x y m]

    improc::HomographyMatrix<Scalar,StorageOrder>::ObservationMatrixType observation_matrix 
        { improc::HomographyMatrix<Scalar,StorageOrder>::ObservationMatrixType::Zero( kNumberEquationsPerPointCorrespondence * detected_pixels.Number()
                                                                                    , improc::HomographyMatrix<Scalar,StorageOrder>::kNumberHomographyParameters ) };

    // First row
    observation_matrix(first_row_indices,Eigen::seq(0,2)) =  reference_pixels_homogeneous_t;
    observation_matrix(first_row_indices,Eigen::seq(6,8)) = -reference_pixels_homogeneous_t.cwiseProduct(std::move(detected_u_matrix));
    // Second row
    observation_matrix(second_row_indices,Eigen::seq(3,5)) = -reference_pixels_homogeneous_t;
    observation_matrix(second_row_indices,Eigen::seq(6,8)) =  std::move(reference_pixels_homogeneous_t).cwiseProduct(std::move(detected_v_matrix));
    // Third row
    observation_matrix(third_row_indices           ,Eigen::seq(0,2)) = -observation_matrix(std::move(second_row_indices),Eigen::seq(6,8));
    observation_matrix(std::move(third_row_indices),Eigen::seq(3,5)) = -observation_matrix(std::move(first_row_indices) ,Eigen::seq(6,8));
    return observation_matrix;
}
