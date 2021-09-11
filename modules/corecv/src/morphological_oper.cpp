#include <improc/corecv/morphological_oper.hpp>

improc::MorphologicalOper::MorphologicalOper() : value_(improc::MorphologicalOper::kDilate) {};

improc::MorphologicalOper::MorphologicalOper(const std::string& morphological_oper_str)
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Loading morphological operation from string {}..."
                      , morphological_oper_str );
    static const std::unordered_map<std::string,MorphologicalOper::Value> kToElemType = { {"dilate",MorphologicalOper::Value::kDilate}
                                                                                        , {"erode" ,MorphologicalOper::Value::kErode }
                                                                                        , {"open"  ,MorphologicalOper::Value::kOpen  }
                                                                                        , {"close" ,MorphologicalOper::Value::kClose } 
                                                                                        };
    this->value_ = kToElemType.at(servproc::String::ToLower(morphological_oper_str));
}
