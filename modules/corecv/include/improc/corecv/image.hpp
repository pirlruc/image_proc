#ifndef IMPROC_CORECV_IMAGE_HPP
#define IMPROC_CORECV_IMAGE_HPP

#include <improc/improc_defs.hpp>
#include <improc/exception.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <improc/corecv/color_space.hpp>
#include <improc/corecv/interpolation_type.hpp>

#include <opencv2/core.hpp>

namespace improc {
    class Image
    {
        protected:
            cv::Mat                     data_;

        public:
            Image();
            Image(const cv::Mat& image_data);

            void                        set_data(const cv::Mat& image_data);
            cv::Mat                     get_data()  const;

            Image                       Clone()     const;

            // void                        Resize(const cv::Size&   to_image_size, const InterpolationType& interpolation);
            // void                        Resize(const cv::Size2d& scaling,       const InterpolationType& interpolation);
    };


    class ColorSpaceImage : public Image
    {
        private:
            ColorSpace                  color_space_;

        public:
            ColorSpaceImage();
            ColorSpaceImage(const cv::Mat& image_data, const ColorSpace& color_space);

            void                        set_color_space(const ColorSpace& color_space);
            ColorSpace                  get_color_space()   const;

            ColorSpaceImage             Clone()             const;

            void                        ConvertToColorSpace(const ColorSpace& to_color_space);
    };
}

#endif