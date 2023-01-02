#include <improc/corecv/image_format.hpp>

improc::ImageFormat::ImageFormat() : value_(improc::ImageFormat::kPNG) {};

improc::ImageFormat::ImageFormat(const std::string& image_format_str)
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Loading image format from string {}..."
                      , image_format_str );
    static const std::unordered_map<std::string,ImageFormat::Value> kToElemType = { {"png"     ,ImageFormat::Value::kPNG     }
                                                                                  , {"jpeg"    ,ImageFormat::Value::kJPEG    }
                                                                                  , {"jpeg2000",ImageFormat::Value::kJPEG2000}
                                                                                  };
    this->value_ = kToElemType.at(improc::String::ToLower(image_format_str));
}
