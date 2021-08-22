#include <improc/corecv/image.h>

improc::Image::Image() : data_(cv::UMat()) {}

improc::Image::Image(const cv::UMat& image_data) : Image()
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Creating image object..." );    
    this->set_data(image_data);
}

void improc::Image::set_data(const cv::UMat& image_data)
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Setting image data..." );
    if (image_data.depth() != CV_8U) 
    {
        SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                          , spdlog::level::error
                          , "ERROR_01: Not supported data type for image. Expected {} received {}."
                          , CV_8U, image_data.depth() );
        throw improc::not_supported_data_type();
    }
    this->data_ = image_data;
}

cv::UMat improc::Image::get_data()
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Obtaining image data..." );    
    return this->data_;
}

improc::Image improc::Image::clone()
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Cloning image object..." );    
    return Image(this->get_data().clone());
}
