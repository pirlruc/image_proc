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
 */
template< typename Scalar, int StorageOrder >
template<typename PixelMatrixDerived>
improc::HomographyMatrix<Scalar,StorageOrder>::HomographyMatrix 
        ( improc::PixelMatrix<PixelMatrixDerived> detected_pixels
        , improc::PixelMatrix<PixelMatrixDerived> reference_pixels ) 
: improc::HomographyMatrix<Scalar,StorageOrder>()
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining homography matrix from point correspondences...");
    typename improc::PixelMatrix<PixelMatrixDerived>::NormalizationMatrixType detected_norm_matrix  = detected_pixels.GetNormalizationMatrix();
    typename improc::PixelMatrix<PixelMatrixDerived>::NormalizationMatrixType reference_norm_matrix = reference_pixels.GetNormalizationMatrix();
    auto observation_matrix = improc::HomographyMatrix<Scalar,StorageOrder>::GetObservationMatrixFromPointCorrespondences   ( detected_pixels.Normalize()
                                                                                                                            , reference_pixels.Normalize() );
    return (*this);
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
auto improc::HomographyMatrix<Scalar,StorageOrder>::GetObservationMatrixFromPointCorrespondences
        ( const improc::PixelMatrix<PixelMatrixDerived>& detected_pixels
        , const improc::PixelMatrix<PixelMatrixDerived>& reference_pixels )
{
    IMPROC_CALIB_LOGGER_TRACE("Obtaining observation matrix from point correspondences considering cross-product...");
    static const int kNumberEquationsPerPointCorrespondence = 3;
    static const int kNumberHomographyParameters            = 9;
    static const int kNumberPixelDimensions                 = 3;
    if (detected_pixels.Number() != reference_pixels.Number())
    {
        // throw error that number should be the same
    }

    auto detected_u_matrix              = detected_pixels.u().replicate(kNumberPixelDimensions);    // N x 3 - [u,u,u]
    auto detected_v_matrix              = detected_pixels.v().replicate(kNumberPixelDimensions);    // N x 3 - [v,v,v]
    auto reference_pixels_homogeneous_t = reference_pixels.Homogeneous().transpose();               // N x 3 - [x y m]
    auto observation_matrix             = Eigen::Matrix<Scalar,kNumberEquationsPerPointCorrespondence * detected_pixels.Number(),kNumberHomographyParameters>::Zero();   

    // Consider the image pixels as p = [u v w]^T and the refence pixels as P = [x y m]^T
    // The observation matrix O for the point correspondences is defined as:
    // O = [  w*P^T  0     -u*P^T
    //        0     -w*P^T  v*P^T
    //       -v*P^T  u*P^T  0     ]
    //
    // Remember that for the homography case w = 1 and m = 1 since they correspond to the 
    // values in the homogeneous row of the matrices.

    // First row
    observation_matrix(Eigen::seq(0,reference_pixels.Number() - 1),Eigen::seq(0,2)) =  reference_pixels_homogeneous_t;
    observation_matrix(Eigen::seq(0,reference_pixels.Number() - 1),Eigen::seq(6,8)) = -reference_pixels_homogeneous_t.cwiseProduct(std::move(detected_u_matrix));
    // Second row
    observation_matrix(Eigen::seq(reference_pixels.Number(),2 * reference_pixels.Number() - 1),Eigen::seq(3,5)) = -reference_pixels_homogeneous_t;
    observation_matrix(Eigen::seq(reference_pixels.Number(),2 * reference_pixels.Number() - 1),Eigen::seq(6,8)) =  std::move(reference_pixels_homogeneous_t).cwiseProduct(std::move(detected_v_matrix));
    // Third row
    observation_matrix(Eigen::seq(2 * reference_pixels.Number(),Eigen::last),Eigen::seq(0,2)) = -observation_matrix(Eigen::seq(reference_pixels.Number(),2 * reference_pixels.Number() - 1),Eigen::seq(6,8));
    observation_matrix(Eigen::seq(2 * reference_pixels.Number(),Eigen::last),Eigen::seq(3,5)) = -observation_matrix(Eigen::seq(0,reference_pixels.Number() - 1),Eigen::seq(6,8));
    return observation_matrix;
}
