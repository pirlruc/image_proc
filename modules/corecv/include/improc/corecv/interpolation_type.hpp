#ifndef IMPROC_CORECV_INTERPOLATION_TYPE_HPP
#define IMPROC_CORECV_INTERPOLATION_TYPE_HPP

#include <improc/improc_defs.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <servproc/infrastructure/string.hpp>

#include <opencv2/imgproc.hpp>

namespace improc {
    class InterpolationType 
    {
        public:
            enum Value : IMPROC_ENUM_KEY_TYPE
            {
                    kLinear  = 0
                ,   kCubic   = 1
                ,   kNearest = 2
            };

        private:
            Value                               value_;

        public:
            InterpolationType();                              
            InterpolationType(const std::string& interpolation_type_str);
            constexpr                           InterpolationType(Value interpolation_type_value): value_(interpolation_type_value) {}
            constexpr operator                  Value()     const {return this->value_;}

            constexpr std::string_view          ToString()  const
            {
                switch (this->value_)
                {
                    case InterpolationType::Value::kLinear : return "Linear";   break;
                    case InterpolationType::Value::kCubic  : return "Cubic";    break;
                    case InterpolationType::Value::kNearest: return "Nearest";  break;
                }
            }

            constexpr cv::InterpolationFlags    ToOpenCV()  const
            {
                switch (this->value_)
                {
                    case InterpolationType::Value::kLinear : return cv::INTER_LINEAR;   break;
                    case InterpolationType::Value::kCubic  : return cv::INTER_CUBIC;    break;
                    case InterpolationType::Value::kNearest: return cv::INTER_NEAREST;  break;
                }
            }
    };
}

#endif