#include <improc/corecv/threshold_type.hpp>

improc::ThresholdType::ThresholdType() : value_(improc::ThresholdType::kOtsu) {};

improc::ThresholdType::ThresholdType(const std::string& threshold_type_str)
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Loading threshold type from string {}..."
                      , threshold_type_str );
    static const std::unordered_map<std::string,ThresholdType::Value> kToElemType = { {"otsu"  ,ThresholdType::Value::kOtsu  }
                                                                                    , {"binary",ThresholdType::Value::kBinary} 
                                                                                    };
    this->value_ = kToElemType.at(improc::String::ToLower(threshold_type_str));
}
