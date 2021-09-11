#ifndef IMPROC_CORECV_THRESHOLD_TYPE_HPP
#define IMPROC_CORECV_THRESHOLD_TYPE_HPP

#include <improc/improc_defs.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <servproc/infrastructure/string.hpp>

#include <opencv2/imgproc.hpp>

namespace improc {
    class ThresholdType 
    {
        public:
            enum Value : IMPROC_ENUM_KEY_TYPE
            {
                    kOtsu   = 0
                ,   kBinary = 1
            };

        private:
            Value                           value_;

        public:
            ThresholdType();                              
            ThresholdType(const std::string& threshold_type_str);
            constexpr                       ThresholdType(Value threshold_type_value): value_(threshold_type_value) {}
            constexpr operator              Value()     const {return this->value_;}

            constexpr std::string_view      ToString()  const
            {
                switch (this->value_)
                {
                    case ThresholdType::Value::kOtsu  : return "Otsu";    break;
                    case ThresholdType::Value::kBinary: return "Binary";  break;
                }
            }

            constexpr cv::ThresholdTypes    ToOpenCV()  const
            {
                switch (this->value_)
                {
                    case ThresholdType::Value::kOtsu  : return cv::THRESH_OTSU;    break;
                    case ThresholdType::Value::kBinary: return cv::THRESH_BINARY;  break;
                }
            }
    };
}

#endif
