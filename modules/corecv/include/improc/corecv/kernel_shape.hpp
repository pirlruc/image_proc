#ifndef IMPROC_CORECV_KERNEL_SHAPE_HPP
#define IMPROC_CORECV_KERNEL_SHAPE_HPP

#include <improc/improc_defs.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <improc/infrastructure/string.hpp>

#include <opencv2/imgproc.hpp>

namespace improc {
    class KernelShape
    {
        public:
            enum Value : IMPROC_ENUM_KEY_TYPE
            {
                    kRectangle = 0
                ,   kEllipse   = 1
            };

        private:
            Value                       value_;

        public:
            KernelShape();                              
            KernelShape(const std::string& kernel_shape_str);
            constexpr                   KernelShape(Value kernel_shape_value): value_(kernel_shape_value) {}
            constexpr operator          Value()     const {return this->value_;}

            constexpr std::string_view  ToString()  const
            {
                switch (this->value_)
                {
                    case KernelShape::Value::kRectangle: return "Rectangle";  break;
                    case KernelShape::Value::kEllipse  : return "Ellipse";  break;
                }
            }

            constexpr cv::MorphShapes   ToOpenCV()  const
            {
                switch (this->value_)
                {
                    case KernelShape::Value::kRectangle: return cv::MORPH_RECT;     break;
                    case KernelShape::Value::kEllipse  : return cv::MORPH_ELLIPSE;  break;
                }
            }
    };
}

#endif
