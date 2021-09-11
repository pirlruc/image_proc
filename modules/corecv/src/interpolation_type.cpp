#include <improc/corecv/interpolation_type.hpp>

improc::InterpolationType::InterpolationType() : value_(improc::InterpolationType::kLinear) {};

improc::InterpolationType::InterpolationType(const std::string& interpolation_type_str)
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Loading interpolation type from string {}..."
                      , interpolation_type_str );
    static const std::unordered_map<std::string,InterpolationType::Value> kToElemType = { {"linear" ,InterpolationType::Value::kLinear }
                                                                                        , {"cubic"  ,InterpolationType::Value::kCubic  }
                                                                                        , {"nearest",InterpolationType::Value::kNearest}
                                                                                        };
    this->value_ = kToElemType.at(servproc::String::ToLower(interpolation_type_str));
}
