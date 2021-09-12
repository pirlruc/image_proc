#ifndef IMPROC_CORECV_IMAGE_FORMAT_HPP
#define IMPROC_CORECV_IMAGE_FORMAT_HPP

#include <improc/improc_defs.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <servproc/infrastructure/string.hpp>

#include <opencv2/core.hpp>

namespace improc {
    class ImageFormat
    {
        public:
            enum Value : IMPROC_ENUM_KEY_TYPE
            {
                    kPNG      = 0
                ,   kJPEG     = 1
                ,   kJPEG2000 = 2
            };

        private:
            Value                       value_;

        public:
            ImageFormat();                              
            ImageFormat(const std::string& image_format_str);
            constexpr                   ImageFormat(Value image_format_value): value_(image_format_value) {}
            constexpr operator          Value()     const {return this->value_;}

            constexpr std::string_view  ToString()  const
            {
                switch (this->value_)
                {
                    case ImageFormat::Value::kPNG     : return "PNG";       break;
                    case ImageFormat::Value::kJPEG    : return "JPEG";      break;
                    case ImageFormat::Value::kJPEG2000: return "JPEG2000";  break;
                }
            }

            constexpr std::string_view  ToOpenCV()  const
            {
                switch (this->value_)
                {
                    case ImageFormat::Value::kPNG     : return ".png";  break;
                    case ImageFormat::Value::kJPEG    : return ".jpg";  break;
                    case ImageFormat::Value::kJPEG2000: return ".jp2";  break;
                }
            }
    };
}

#endif
