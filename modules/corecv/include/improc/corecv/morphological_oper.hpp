#ifndef IMPROC_CORECV_MORPHOLOGICAL_OPER_HPP
#define IMPROC_CORECV_MORPHOLOGICAL_OPER_HPP

#include <improc/improc_defs.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <servproc/infrastructure/string.hpp>

#include <opencv2/imgproc.hpp>

namespace improc {
    class MorphologicalOper
    {
        public:
            enum Value : IMPROC_ENUM_KEY_TYPE
            {
                    kDilate = 0
                ,   kErode  = 1
                ,   kOpen   = 2
                ,   kClose  = 3
            };

        private:
            Value                       value_;

        public:
            MorphologicalOper();                              
            MorphologicalOper(const std::string& morphological_oper_str);
            constexpr                   MorphologicalOper(Value morphological_oper_value): value_(morphological_oper_value) {}
            constexpr operator          Value()     const {return this->value_;}

            constexpr std::string_view  ToString()  const
            {
                switch (this->value_)
                {
                    case MorphologicalOper::Value::kDilate: return "Dilate";    break;
                    case MorphologicalOper::Value::kErode : return "Erode";     break;
                    case MorphologicalOper::Value::kOpen  : return "Open";      break;
                    case MorphologicalOper::Value::kClose : return "Close";     break;
                }
            }

            constexpr cv::MorphTypes    ToOpenCV()  const
            {
                switch (this->value_)
                {
                    case MorphologicalOper::Value::kDilate: return cv::MORPH_DILATE;    break;
                    case MorphologicalOper::Value::kErode : return cv::MORPH_ERODE;     break;
                    case MorphologicalOper::Value::kOpen  : return cv::MORPH_OPEN;      break;
                    case MorphologicalOper::Value::kClose : return cv::MORPH_CLOSE;     break;
                }
            }
    };
}

#endif
