#include <improc/corecv/kernel_shape.hpp>

improc::KernelShape::KernelShape() : value_(improc::KernelShape::kRectangle) {};

improc::KernelShape::KernelShape(const std::string& kernel_shape_str)
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Loading kernel shape from string {}..."
                      , kernel_shape_str );
    static const std::unordered_map<std::string,KernelShape::Value> kToElemType = { {"rectangle",KernelShape::Value::kRectangle}
                                                                                  , {"ellipse"  ,KernelShape::Value::kEllipse  } 
                                                                                  };
    this->value_ = kToElemType.at(servproc::String::ToLower(kernel_shape_str));
}
