#ifndef IMPROC_CORECV_COLOR_SPACE_HPP
#define IMPROC_CORECV_COLOR_SPACE_HPP

#include <improc/improc_defs.hpp>
#include <improc/exceptions.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <servproc/infrastructure/string.hpp>

#include <opencv2/imgproc.hpp>

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

            constexpr unsigned int      GetNumberChannels() const
            {
                switch (this->value_)
                {
                    case ColorSpace::Value::kBGR : return 3;    break;
                    case ColorSpace::Value::kRGB : return 3;    break;
                    case ColorSpace::Value::kBGRA: return 4;    break;
                    case ColorSpace::Value::kRGBA: return 4;    break;
                    case ColorSpace::Value::kGray: return 1;    break;
                }
            }

            constexpr cv::ColorConversionCodes GetColorConversionCode(const ColorSpace& to_color_space) const
            {
                switch (this->value_)
                {
                    case ColorSpace::Value::kBGR : 
                        switch (to_color_space)
                        {
                            case ColorSpace::Value::kBGR : throw improc::not_supported_color_conversion();  break;
                            case ColorSpace::Value::kRGB : return cv::COLOR_BGR2RGB;                        break;
                            case ColorSpace::Value::kBGRA: return cv::COLOR_BGR2BGRA;                       break;
                            case ColorSpace::Value::kRGBA: return cv::COLOR_BGR2RGBA;                       break;
                            case ColorSpace::Value::kGray: return cv::COLOR_BGR2GRAY;                       break;
                        }
                        break;

                    case ColorSpace::Value::kRGB :
                        switch (to_color_space)
                        {
                            case ColorSpace::Value::kBGR : return cv::COLOR_RGB2BGR;                        break;
                            case ColorSpace::Value::kRGB : throw improc::not_supported_color_conversion();  break;
                            case ColorSpace::Value::kBGRA: return cv::COLOR_RGB2BGRA;                       break;
                            case ColorSpace::Value::kRGBA: return cv::COLOR_RGB2RGBA;                       break;
                            case ColorSpace::Value::kGray: return cv::COLOR_RGB2GRAY;                       break;
                        }
                        break;

                    case ColorSpace::Value::kBGRA:
                        switch (to_color_space)
                        {
                            case ColorSpace::Value::kBGR : return cv::COLOR_BGRA2BGR;                       break;
                            case ColorSpace::Value::kRGB : return cv::COLOR_BGRA2RGB;                       break;
                            case ColorSpace::Value::kBGRA: throw improc::not_supported_color_conversion();  break;
                            case ColorSpace::Value::kRGBA: return cv::COLOR_BGRA2RGBA;                      break;
                            case ColorSpace::Value::kGray: return cv::COLOR_BGRA2GRAY;                      break;
                        }
                        break;

                    case ColorSpace::Value::kRGBA:
                        switch (to_color_space)
                        {
                            case ColorSpace::Value::kBGR : return cv::COLOR_RGBA2BGR;                       break;
                            case ColorSpace::Value::kRGB : return cv::COLOR_RGBA2RGB;                       break;
                            case ColorSpace::Value::kBGRA: return cv::COLOR_RGBA2BGRA;                      break;
                            case ColorSpace::Value::kRGBA: throw improc::not_supported_color_conversion();  break;
                            case ColorSpace::Value::kGray: return cv::COLOR_RGBA2GRAY;                      break;
                        }
                        break;

                    case ColorSpace::Value::kGray:
                        switch (to_color_space)
                        {
                            case ColorSpace::Value::kBGR : return cv::COLOR_GRAY2BGR;                       break;
                            case ColorSpace::Value::kRGB : return cv::COLOR_GRAY2RGB;                       break;
                            case ColorSpace::Value::kBGRA: return cv::COLOR_GRAY2BGRA;                      break;
                            case ColorSpace::Value::kRGBA: return cv::COLOR_GRAY2RGBA;                      break;
                            case ColorSpace::Value::kGray: throw improc::not_supported_color_conversion();  break;
                        }
                        break;
                }
            }
    };
}

#endif