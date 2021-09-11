#include <improc/corecv/color_space.hpp>

improc::ColorSpace::ColorSpace() : value_(improc::ColorSpace::kRGB) {};

improc::ColorSpace::ColorSpace(const std::string& color_space_str)
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Loading color space from string {}..."
                      , color_space_str );
    static const std::unordered_map<std::string,ColorSpace::Value> kToElemType = { {"rgb" ,ColorSpace::Value::kRGB }
                                                                                 , {"bgr" ,ColorSpace::Value::kBGR }
                                                                                 , {"rgba",ColorSpace::Value::kRGBA}
                                                                                 , {"bgra",ColorSpace::Value::kBGRA}
                                                                                 , {"gray",ColorSpace::Value::kGray}
                                                                                 };
    this->value_ = kToElemType.at(servproc::String::ToLower(color_space_str));
}
