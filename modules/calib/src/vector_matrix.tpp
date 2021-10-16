template    <   typename Scalar
            ,   int NumberComponents
            ,   int NumberVectors
            ,   int StorageOrder        
            ,   int MaxNumberComponents 
            ,   int MaxNumberVectors    
            >
improc::VectorMatrix    <   Scalar
                        ,   NumberComponents
                        ,   NumberVectors
                        ,   StorageOrder
                        ,   MaxNumberComponents
                        ,   MaxNumberVectors
                        >::VectorMatrix()   :   data_       (Eigen::Matrix  <   Scalar
                                                                            ,   NumberComponents
                                                                            ,   NumberVectors
                                                                            ,   StorageOrder
                                                                            ,   MaxNumberComponents
                                                                            ,   MaxNumberVectors
                                                                            >() ) 
                                            ,   homogeneous_(false)
{}

template    <   typename Scalar
            ,   int NumberComponents
            ,   int NumberVectors
            ,   int StorageOrder        
            ,   int MaxNumberComponents 
            ,   int MaxNumberVectors    
            >
improc::VectorMatrix    <   Scalar
                        ,   NumberComponents
                        ,   NumberVectors
                        ,   StorageOrder
                        ,   MaxNumberComponents
                        ,   MaxNumberVectors
                        >::VectorMatrix(const VectorMatrixData& data)   :   data_(data) 
                                                                        ,   homogeneous_(false)
{}
