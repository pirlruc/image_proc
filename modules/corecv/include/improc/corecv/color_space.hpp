#ifndef IMPROC_CORECV_COLOR_SPACE_HPP
#define IMPROC_CORECV_COLOR_SPACE_HPP

#include <improc/improc_defs.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <servproc/infrastructure/string.hpp>

#include <opencv2/core.hpp>

namespace improc {
    class ColorSpace 
    {
        public:
            enum Value : IMPROC_ENUM_KEY_TYPE
            {
                    kRGBA = 0
                ,   kBGRA = 1
                ,   kRGB  = 2
                ,   kBGR  = 3
                ,   kGray = 4
            };

        private:
            Value                       value_;

        public:
            ColorSpace();                              
            ColorSpace(const std::string& color_space_str);
            constexpr                   ColorSpace(Value color_space_value): value_(color_space_value) {}
            constexpr operator          Value()     const {return this->value_;}

            constexpr std::string_view  ToString()  const
            {
                switch (this->value_)
                {
                    case ColorSpace::Value::kBGR : return "BGR";  break;
                    case ColorSpace::Value::kRGB : return "RGB";  break;
                    case ColorSpace::Value::kBGRA: return "BGRA"; break;
                    case ColorSpace::Value::kRGBA: return "RGBA"; break;
                    case ColorSpace::Value::kGray: return "Gray"; break;
                }
            }
    };
}

#endif